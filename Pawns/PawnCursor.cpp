// Copyright 2020 Vacuda


#include "PawnCursor.h"
#include "Kismet/GameplayStatics.h"							// for openworld
#include "EngineUtils.h" 									// for TActorRange
#include "Components/SceneComponent.h"						// maybe detach?

#include "Talismans/Talismans.h"							// for LogGrid
#include "Talismans/Pieces/MeshPiece.h"						// for MeshPiece
#include "Talismans/Pieces/Piece.h"							// for Piece
#include "Talismans/Pieces/Cluster.h"						// for Cluster
#include "Talismans/Pieces/MeshCluster.h"					// for MeshCluster
#include "Talismans/Structs/FLocationPackage.h"  			// custom header file
#include "Talismans/Structs/FPuzzleUnit.h"					// for PuzzleUnit
#include "Talismans/Enums/E_PieceState.h"					// for E_PieceState
#include "Talismans/Admin/Hub.h"							// for Hub
#include "Talismans/Controllers/ThePlayerController.h"   	// for The PlayerController
#include "Talismans/Admin/TheGameInstance.h"				// for GameInstance
#include "Talismans/TableNavigation/TableNavigator.h"		// for TableNavigator
#include "Talismans/TableNavigation/Animator.h"				// for Animator
#include "Talismans/TableNavigation/PieceArbiter.h"			// for PieceArbiter
#include "Talismans/TableNavigation/GridArbiter.h"			// for GridArbiter
#include "Talismans/TableNavigation/BinArbiter.h"			// for BinArbiter
#include "Talismans/TableNavigation/RackArbiter.h"			// for RackArbiter
#include "Talismans/Levels/PuzzleLevel.h"					// for PuzzleLevel



APawnCursor::APawnCursor()
{
	PrimaryActorTick.bCanEverTick = true;

	//@@@@ still go through blueprints to get to this StaticMesh

	CursorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cursor Mesh"));
	RootComponent = CursorMesh;
}

void APawnCursor::BeginPlay()
{
	Super::BeginPlay();
}

void APawnCursor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//build ProposedDirection
	ProposedDirection = CombineCardinalDirections();

	DeterminePerformMovement();

	if (bIsRadialChoiceMode) {
		RunRadialChoiceModeChecks();
		Hub->Animator->RunRadialChoiceMode();
	}

	Hub->Animator->TickFunctionFromPawnCursor(DeltaTime);

	Hub->Controller->TickFunctionFromPawnCursor();
}


// SETUP

void APawnCursor::SetStartPosition()
{
	UE_LOG(LogTemp, Warning, TEXT("AT setstartposition"))

	//set start variables
	Table_Address = Hub->Navigator->GetStartingTable_Address();
	CurrentLocation = Hub->Navigator->GetLocationFromTable_Address(Table_Address);
	CurrentLocation.Z += HoverAmount;

	//set location and rotation
	Hub->PawnCursor->CursorMesh->SetWorldLocation(CurrentLocation);
	Hub->PawnCursor->CursorMesh->SetWorldRotation({ 0.f,0.f,0.f });
}

void APawnCursor::CatchTheHub(UHub* _Hub)
{
	Hub = _Hub;
}


//CONTROL

void APawnCursor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APawnCursor::CalculateLeftRight);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &APawnCursor::CalculateUpDown);

	PlayerInputComponent->BindAction("Cursor:GrabRelease", IE_Pressed, this, &APawnCursor::GrabRelease);
	PlayerInputComponent->BindAction("Cursor:Rotate", IE_Pressed, this, &APawnCursor::Rotate);
	PlayerInputComponent->BindAction("Cursor:Flip", IE_Pressed, this, &APawnCursor::Flip);
}

void APawnCursor::CalculateLeftRight(float Value)
{
	
	if(Value > AxisThreshold){
		LeftRight = d_RIGHT;
		return;
	}

	if(Value < -(AxisThreshold)){
		LeftRight = d_LEFT;
		return;
	}

	LeftRight = d_NONE;
}

void APawnCursor::CalculateUpDown(float Value)
{
	UpDownValue = Value;

	if(Value < -(AxisThreshold)){
		UpDown = d_UP;
		return;
	}

	if(Value > AxisThreshold){
		UpDown = d_DOWN;
		return;
	}

	UpDown = d_NONE;
}

void APawnCursor::GrabRelease()
{
	UE_LOG(LogTemp, Error, TEXT("Gamepad: GrabRelease"))

	//if in Radial Choice Mode
	if (bIsRadialChoiceMode) {
		//if there's a selected piece
		if (SelectedClusterPtr) {

			//reset Animator Radial Choice Mode
			Hub->Animator->ResetRadialChoiceMode();

			HandlePickingUpCluster(SelectedClusterPtr);

			//reset Radial Choice Mode
			ExitRadialChoiceMode();
		}
		else {
			//no nothing
		}
	}
	//if NOT in Radial Choice Mode
	else {
		//if nothing in hand
		if (InHand.Num() == 0) {

			//reset AllMovableClusters
			AllMovableClusters.Empty();

			//if on rack
			if (Table_Address.Board == RACK) {
				Hub->RackArbiter->TravelToDifferentPuzzle(Table_Address.Col);
				return;
			}

			//get all movable clusters
			Hub->Navigator->FindAllMovableClusters(Table_Address, &AllMovableClusters);

			//if AllMoveableClusters is 0
			if (AllMovableClusters.Num() == 0) {
				UE_LOG(LogTemp, Error, TEXT("Nothing To Pick Up"))
			}
			//if AllMoveableClusters is 1
			else if (AllMovableClusters.Num() == 1) {
			
				ACluster* GrabbedCluster = AllMovableClusters[0];

				HandlePickingUpCluster(GrabbedCluster);

			}
			//if AllMovableClusters is more than 1
			else {

				//set cursor to future transform
				Hub->Animator->SetCursorToFutureTransform();

				//start RadialChoiceMode;
				bHasPermissionToMove = false;
				bIsRadialChoiceMode = true;
				RunRadialChoiceModeChecks();
				Hub->Animator->RunRadialChoiceMode();
			}
		}
		//drop cluster in hand
		else {

			//on rack
			if (Table_Address.Board == RACK) {

				//get cooresponding puzzle letter
				TEnumAsByte<E_PuzzleLetter> NewLetter = Hub->RackArbiter->ReturnCurrentPortraitPuzzleLetter(Table_Address.Col);

				//same letter check
				if (NewLetter != Table_Address.PuzzleLetter) {

					//drop cluster in cooresponding bin
					bool bDidSucceed = Hub->BinArbiter->DropClusterSomewhereInTheBinOfThisPuzzle(InHand[0], NewLetter);

					if (bDidSucceed) {

						//condense
						ACluster* Cluster = InHand[0];

						//take piece out of hand
						InHand.Empty();

						//set cursor to future transform
						Hub->Animator->SetCursorToFutureTransform();

						//detach cluster from cursor
						Cluster->MeshClusterPtr->SceneComp->DetachFromComponent(FDetachmentTransformRules(
							EDetachmentRule::KeepWorld,
							EDetachmentRule::KeepWorld,
							EDetachmentRule::KeepWorld, true));

						//move mesh pieces
						Hub->Animator->SendClusterIntoPortrait(Cluster);
					}
					else {
						//indicate failure
						Hub->Animator->TableLightFlash();
					}
				}
				//indicate failure
				else {
					Hub->Animator->TableLightFlash();
				}

			}
			//on bin or grid
			else {
				//check if possible
				if (Hub->Navigator->IsPlacementPossible(InHand[0])) {

					HandleDroppingCluster(InHand[0]);
				}
				else {
					UE_LOG(LogTemp, Error, TEXT("Can't Drop Cluster"))

					Hub->Animator->TableLightFlash();



				}
			}
		}
	}
}

void APawnCursor::Rotate() 
{
	UE_LOG(LogTemp, Error, TEXT("Gamepad: Rotate"))

	if (!bIsRadialChoiceMode) {

		//rotate cursor
		Hub->Animator->RotateCursorBySixtyDegrees();

		//change Cursor Tri
		Table_Address.Tri += 1;
		if (Table_Address.Tri == 7) {
			Table_Address.Tri = 1;
		}

		//if something in Hand
		if (InHand.Num() != 0) {

			//rotate cluster and pieces
			Hub->PieceArbiter->RotateClusterAndPieceInfo(InHand[0], Table_Address);
		}
	}

	//DEBUG
	//const TEnumAsByte<E_Board> Board = Table_Address.Board;
	//	FString BoardString = UEnum::GetValueAsString(Board.GetValue());
	//	UE_LOG(AGridRotation, Display, TEXT("ROTATION"))
	//	UE_LOG(AGridRotation, Display, TEXT("Cursor Board: %s"), *BoardString)
	//	UE_LOG(AGridRotation, Display, TEXT("Cursor Col: %i"), Table_Address.Col)
	//	UE_LOG(AGridRotation, Display, TEXT("Cursor Row: %i"), Table_Address.Row)
	//	UE_LOG(AGridRotation, Error, TEXT("Cursor Tri: %i"), Table_Address.Tri)

			if (InHand.Num() != 0) {
				//cluster
				const TEnumAsByte<E_Board> ClusterBoard = InHand[0]->Table_Address.Board;
				FString ClusterBoardString = UEnum::GetValueAsString(ClusterBoard.GetValue());
				UE_LOG(AGridRotation, Error, TEXT("++++++++++++++++++++++"));
				UE_LOG(AGridRotation, Display, TEXT("Cluster Board: %s"), *ClusterBoardString)
				UE_LOG(AGridRotation, Display, TEXT("Cluster Col: %i"), InHand[0]->Table_Address.Col)
				UE_LOG(AGridRotation, Display, TEXT("Cluster Row: %i"), InHand[0]->Table_Address.Row)
				UE_LOG(AGridRotation, Error, TEXT("Cluster Tri: %i"), InHand[0]->Table_Address.Tri)
				UE_LOG(AGridRotation, Error, TEXT("++++++++++++++++++++++"));

				//pieces
				for (auto& Piece : InHand[0]->HeldPieces) {
					const TEnumAsByte<E_Board> PieceBoard = Piece->Table_Address.Board;
					FString PieceBoardString = UEnum::GetValueAsString(PieceBoard.GetValue());
					const TEnumAsByte<E_PieceShape> Shape = Piece->Shape;
					FString ShapeString = UEnum::GetValueAsString(Shape.GetValue());
					UE_LOG(AGridRotation, Error, TEXT("<<<<<<<"));
					UE_LOG(AGridRotation, Display, TEXT("Piece Board: %s"), *PieceBoardString)
					UE_LOG(AGridRotation, Display, TEXT("Piece Shape: %s"), *ShapeString)
					UE_LOG(AGridRotation, Display, TEXT("Piece Col: %i"), Piece->Table_Address.Col)
					UE_LOG(AGridRotation, Display, TEXT("Piece Row: %i"), Piece->Table_Address.Row)
					UE_LOG(AGridRotation, Error, TEXT("Piece Tri: %i"), Piece->Table_Address.Tri)
				}
			}

		UE_LOG(AGridRotation, Warning, TEXT("---------------------------------------"));
}

void APawnCursor::Flip()
{
	UE_LOG(LogTemp, Error, TEXT("Gamepad: Flip"))
	UE_LOG(LogTemp, Error, TEXT("In Grid, PiecePtr: %i"), Hub->GridArbiter->GetPtrNum())
	UE_LOG(LogTemp, Error, TEXT("BIN, bIsFilled: %i"), Hub->BinArbiter->GetNum())

	UE_LOG(LogTemp, Error, TEXT("# of MeshClusters: %i"), Hub->GridArbiter->GetMeshClustersNum())
	UE_LOG(LogTemp, Error, TEXT("# of Clusters: %i"), Hub->GridArbiter->GetClustersNum())

	for (auto& Cluster : InHand) {
		for (auto& Piece : Cluster->HeldPieces) {

			UE_LOG(LogTemp, Error, TEXT("PIECE HELD"))

			for (auto& Join : Piece->JoinMap) {

				if (Join.Value.bIsConnected == false) {
					const TEnumAsByte<E_JoinSite> JoinSite = Join.Key;
					FString JoinSiteString = UEnum::GetValueAsString(JoinSite.GetValue());

					UE_LOG(LogTemp, Error, TEXT("Unconnected Join Site: %s"), *JoinSiteString)
				}
			}
		}
	}
	UE_LOG(LogTemp, Error, TEXT("-----"))
}


//CHANGE INFO

void APawnCursor::DeterminePerformMovement() 
{

	//if in Radial Choice Mode
	if (bIsRadialChoiceMode) {

		//if a valid TriPick is inputted
		if (TriPick != 0) {

			ACluster* PossibleSelectedClusterPtr;
			PossibleSelectedClusterPtr = Hub->Navigator->FindPossibleClusterToSelect(Table_Address, TriPick);

			if (PossibleSelectedClusterPtr) {
				//this is here to trigger visual changes later, upon selecting different pieces

				//first time at getting a SelectedCluster
				if (!SelectedClusterPtr) {

					SelectedClusterPtr = PossibleSelectedClusterPtr;
				}
				//change in SelectedCluster
				else if(SelectedClusterPtr != PossibleSelectedClusterPtr){
					SelectedClusterPtr = PossibleSelectedClusterPtr;
				}
				//no change, so do nothing
				else {
					UE_LOG(LogTemp, Warning, TEXT("do nothing"))
				}
			}
		}
	}
	//if NOT in Radial Choice Mode
	else {
		//valid direction inputted
		if(ProposedDirection!= d_NONE){
		
			//permission check
			if(bHasPermissionToMove){

				PerformMovement();
				bHasPermissionToMove = false;
				//start fuze that will end with giving permission to move
				GetWorld()->GetTimerManager().SetTimer(MoveDelayTimerHandle, this, &APawnCursor::GivePermissionToMove, MoveDelay, false);
				bIsMoveDelayFuzeActive = true;

			}
			else {
				//do nothing
			}
		}
		//trigger to reset movement before being able to move again
		else if (bEndingRadialChoiceModeTrigger) {
			//reset trigger
			bEndingRadialChoiceModeTrigger = false;

			//give permission to move again
			bHasPermissionToMove = true;
		}
	}
}

void APawnCursor::PerformMovement()
{
	//DEBUG
	const TEnumAsByte<E_Board> FromBoard = Table_Address.Board;
	FString FromBoardString = UEnum::GetValueAsString(FromBoard.GetValue());
	UE_LOG(AGridMovement, Warning, TEXT("MOVEMENT"))
	UE_LOG(AGridMovement, Warning, TEXT("Cursor FROM: %s %i-%i,%i"),
			*FromBoardString,
			Table_Address.Col,
			Table_Address.Row,
			Table_Address.Tri)

	//make package
	FLocationPackage Package = FLocationPackage();
	Package.Table_Address = Table_Address;
	Package.ProposedDirection = ProposedDirection;

	//package is altered
	Hub->Navigator->ChangeLocationPackageToGetMovementDestination(&Package);

	//set new location
	CurrentLocation = Package.NewLocation;
	CurrentLocation.Z += HoverAmount;

	//set new address, Board, Col, and Row
	Table_Address.Board = Package.NewTable_Address.Board;
	Table_Address.Col = Package.NewTable_Address.Col;
	Table_Address.Row = Package.NewTable_Address.Row;

	//start movement sequence
	Hub->Animator->MoveCursorToNewLocation(CurrentLocation);

	//DEBUG
	const TEnumAsByte<E_Board> Board = Table_Address.Board;
	FString BoardString = UEnum::GetValueAsString(Board.GetValue());
	UE_LOG(AGridMovement, Warning, TEXT("Cursor To: %s %i-%i,%i"),
		*BoardString,
		Table_Address.Col,
		Table_Address.Row,
		Table_Address.Tri)

	//change held piece address, if one in hand
	if (InHand.Num() != 0) {

		Hub->PieceArbiter->SetNewTable_Address(InHand[0], Table_Address.PuzzleLetter, Table_Address.Board, Package.ColChange, Package.RowChange);
	}

	UE_LOG(AGridMovement, Error, TEXT("---------------------------------------"));
}

void APawnCursor::GivePermissionToMove()
{
	//give permission and reset timer
	bHasPermissionToMove = true;
	GetWorld()->GetTimerManager().ClearTimer(MoveDelayTimerHandle);
	bIsMoveDelayFuzeActive = false;
}

void APawnCursor::RunRadialChoiceModeChecks()
{
	if (ProposedDirection == d_DOWN) {
		TriPick = 1;
	}
	if (ProposedDirection == d_DOWNRIGHT) {
		TriPick = 2;
	}
	if (ProposedDirection == d_UPRIGHT) {
		TriPick = 3;
	}
	if (ProposedDirection == d_UP) {
		TriPick = 4;
	}
	if (ProposedDirection == d_UPLEFT) {
		TriPick = 5;
	}
	if (ProposedDirection == d_DOWNLEFT) {
		TriPick = 6;
	}

	//handle Left
	if (ProposedDirection == d_LEFT) {
		if (UpDownValue < 0) {
			TriPick = 5;
		}
		if (UpDownValue >= 0) {
			TriPick = 6;
		}
	}

	//handle Right
	if (ProposedDirection == d_RIGHT) {
		if (UpDownValue < 0) {
			TriPick = 3;
		}
		if (UpDownValue >= 0) {
			TriPick = 2;
		}
	}

	//if no ProposedDirection, reset to 0
	if (ProposedDirection == d_NONE) {
		TriPick = 0;
	}
}

void APawnCursor::ExitRadialChoiceMode() 
{
	bEndingRadialChoiceModeTrigger = true;
	bIsRadialChoiceMode = false;
	SelectedClusterPtr = nullptr;
	AllMovableClusters.Empty();
	TriPick = 0;
}

TEnumAsByte<E_Direction> APawnCursor::CombineCardinalDirections()
{
	if (UpDown == d_NONE) {
		if (LeftRight == d_NONE) {
			return d_NONE;
		}
		if (LeftRight == d_LEFT) {

			//favor up
			if (UpDownValue < 0) {
				return d_UPLEFT;
			}
			//favor down
			else {
				return d_DOWNLEFT;
			}
		}
		if (LeftRight == d_RIGHT) {

			//favor up
			if (UpDownValue < 0) {
				return d_UPRIGHT;
			}
			//favor down
			else {
				return d_DOWNRIGHT;
			}
		}
	}
	if (UpDown == d_UP) {
		if (LeftRight == d_NONE) {
			return d_UP;
		}
		if (LeftRight == d_LEFT) {
			return d_UPLEFT;
		}
		if (LeftRight == d_RIGHT) {
			return d_UPRIGHT;
		}
	}
	if (UpDown == d_DOWN) {
		if (LeftRight == d_NONE) {
			return d_DOWN;
		}
		if (LeftRight == d_LEFT) {
			return d_DOWNLEFT;
		}
		if (LeftRight == d_RIGHT) {
			return d_DOWNRIGHT;
		}
	}
	//safety
	return d_NONE;
}

void APawnCursor::HandlePickingUpCluster(ACluster* GrabbedCluster)
{
	//set pickedupaddress on cluster
	GrabbedCluster->PickedUpAddress = GrabbedCluster->Table_Address;

	//take cluster out of grid
	Hub->Navigator->PickClusterOffBoard(GrabbedCluster);

	//put cluster into Hand
	InHand.Emplace(GrabbedCluster);

	//set cursor to future transform
	Hub->Animator->SetCursorToFutureTransform();

	//lift cluster
	FVector NewLocation = GrabbedCluster->MeshClusterPtr->SceneComp->GetComponentLocation();
	NewLocation.Z += HoverAmount;
	GrabbedCluster->MeshClusterPtr->SceneComp->SetWorldLocation(NewLocation);

	//attach Cluster to Cursor
	GrabbedCluster->MeshClusterPtr->SceneComp->AttachToComponent(CursorMesh, FAttachmentTransformRules(
		EAttachmentRule::KeepWorld,
		EAttachmentRule::KeepWorld,
		EAttachmentRule::KeepWorld, true));
}

void APawnCursor::HandleDroppingCluster(ACluster* DroppedCluster)
{
	//put cluster onto board
	Hub->Navigator->PlaceClusterOntoBoard(DroppedCluster);

	//take piece out of hand
	InHand.Empty();

	//set cursor to future transform
	Hub->Animator->SetCursorToFutureTransform();

	//if settings, cement
	if (Hub->GameInstance->GameplaySettings.bIsAHomePieceCementedOnDrop) {
		Hub->PieceArbiter->ClusterCementCheck(DroppedCluster);
	}

	//detach cluster from cursor
	DroppedCluster->MeshClusterPtr->SceneComp->DetachFromComponent(FDetachmentTransformRules(
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld, true));

	//move mesh pieces
	Hub->Navigator->MoveClusterMeshToBoard(DroppedCluster);

	//handle joining pieces
	if (Hub->GameInstance->GameplaySettings.bDoPiecesJoin) {
		Hub->Navigator->HandleJoiningPieces(DroppedCluster);
	}
}

void APawnCursor::ExitChecks()
{
	if (bIsRadialChoiceMode) {

		//reset visuals of Cursor and Cluster/Pieces
		Hub->Animator->ResetRadialChoiceMode();

		ExitRadialChoiceMode();
	}

	if (InHand.Num() != 0) {

		if (InHand[0]->Table_Address.Board == BIN) {

			//check if possible
			if (Hub->Navigator->IsPlacementPossible(InHand[0])) {
				HandleDroppingCluster(InHand[0]);
			}
			else {
				Hub->BinArbiter->DropClusterWhereItWasPickedUp(InHand[0], Table_Address);
			}
		}
		else {
			Hub->BinArbiter->DropClusterWhereItWasPickedUp(InHand[0], Table_Address);
		}
	}

	//reset table address tri
	Table_Address.Tri = 1;

	//condense	
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//set exit address
	Puzzle.ExitTable_Address = Table_Address;
}

void APawnCursor::MoveToElement_Right()
{
	//if junction
	if (Hub->GameInstance->CurrentPuzzleLetter == pJUNCTION) {
		//if on rack
		if (Table_Address.Board == RACK) {
			SendCursorToThisCoordinate(8, 19, BIN);
		}
		//if in bin
		else if (Table_Address.Board == BIN) {
			//send to BAG
		}
	}
	//if regular puzzle
	else {
		//if on rack
		if (Table_Address.Board == RACK) {
			SendCursorToThisCoordinate(3, 4, GRID);
		}
		//if on grid
		else if (Table_Address.Board == GRID) {
			SendCursorToThisCoordinate(2, 5, BIN);
		}
	}
}

void APawnCursor::MoveToElement_Left()
{
	//if junction
	if (Hub->GameInstance->CurrentPuzzleLetter == pJUNCTION) {
		//if on bag
		if (Table_Address.Board == BAG) {
			SendCursorToThisCoordinate(8, 19, BIN);
		}
		//if on BIN
		else if (Table_Address.Board == BIN) {
			SendCursorToThisCoordinate(1, 1, RACK);
		}
	}
	//if regular puzzle
	else {
		//if on bin
		if (Table_Address.Board == BIN) {

			//get NewRow and NewCol
			int32 NewCol = Hub->PuzzleGridWidth;
			int32 NewRow;

			//if odd column
			if (NewCol % 2 == 1) {
				NewRow = 4;
			}
			//if even column
			else {
				NewRow = 3;
			}

			SendCursorToThisCoordinate(NewCol, NewRow, GRID);
		}
		//if on grid
		else if (Table_Address.Board == GRID) {
			SendCursorToThisCoordinate(1, 1, RACK);
		}
	}
}

void APawnCursor::SendCursorToThisCoordinate(int32 col, int32 row, TEnumAsByte<E_Board> Board)
{
	//DEBUG
	const TEnumAsByte<E_Board> FromBoard = Table_Address.Board;
	FString FromBoardString = UEnum::GetValueAsString(FromBoard.GetValue());
	UE_LOG(AGridMovement, Warning, TEXT("MOVEMENT"))
	UE_LOG(AGridMovement, Warning, TEXT("Cursor FROM: %s %i-%i, tri:%i"),
		*FromBoardString,
		Table_Address.Col,
		Table_Address.Row,
		Table_Address.Tri)


	//get ColChange, to point col-row
	int32 ColChange = col - Table_Address.Col;
	int32 RowChange = row - Table_Address.Row;

	//set Table_Address, to point col-row
	Table_Address.Board = Board;
	Table_Address.Col = col;
	Table_Address.Row = row;

	//set new location
	if (Board == BIN) {
		CurrentLocation = Hub->BinMesh->GetSocketLocation(Table_Address.ReturnTheSocketCode());
	}
	if (Board == GRID) {
		CurrentLocation = Hub->GridMesh->GetSocketLocation(Table_Address.ReturnTheSocketCode());
	}
	if (Board == RACK) {
		CurrentLocation = Hub->RackArbiter->ReturnNewCursorLocationOnRack(col);
	}
	CurrentLocation.Z += HoverAmount;

	//start movement sequence
	Hub->Animator->MoveCursorToNewLocation(CurrentLocation);

	//DEBUG
	FString BoardString = UEnum::GetValueAsString(Board.GetValue());
	UE_LOG(AGridMovement, Warning, TEXT("Cursor To: %s %i-%i, tri:%i"),
		*BoardString,
		Table_Address.Col,
		Table_Address.Row,
		Table_Address.Tri)

	//change held piece address, if one in hand
	if (InHand.Num() != 0) {

		Hub->PieceArbiter->SetNewTable_Address(InHand[0], Table_Address.PuzzleLetter, Table_Address.Board, ColChange, RowChange);
	}

	UE_LOG(AGridMovement, Error, TEXT("---------------------------------------"));
}



