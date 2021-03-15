// Copyright 2020 Vacuda


#include "PawnCursor.h"
#include "Kismet/GameplayStatics.h"							// for openworld
#include "EngineUtils.h" 									// for TActorRange
#include "Engine/EngineTypes.h"								// for EAttachmentRule
#include "Components/SceneComponent.h"						// maybe detach?
#include "PaperSpriteComponent.h"							// for papersprite

#include "Talismans/Talismans.h"							// for LogGrid
#include "Talismans/Pieces/ActorPiece.h"					// for ActorPiece
#include "Talismans/Pieces/Piece.h"						// for Piece
#include "Talismans/Pieces/Cluster.h"						// for Cluster
#include "Talismans/Pieces/ActorCluster.h"					// for ActorCluster
#include "Talismans/Structs/FLocationPackage.h"  			// custom header file
#include "Talismans/Structs/FPuzzleUnit.h"					// for PuzzleUnit
#include "Talismans/Enums/E_PieceState.h"					// for E_PieceState
#include "Talismans/Admin/Hub.h"							// for Hub
#include "Talismans/Controllers/ThePlayerController.h"   	// for The PlayerController
#include "Talismans/Admin/TheGameInstance.h"				// for GameInstance
#include "Talismans/TableNavigation/Animator.h"				// for Animator
#include "Talismans/TableNavigation/PieceArbiter.h"			// for PieceArbiter
#include "Talismans/TableNavigation/BoardArbiter.h"			// for BoardArbiter
#include "Talismans/TableNavigation/RackArbiter.h"			// for RackArbiter
#include "Talismans/Levels/PuzzleLevel.h"					// for PuzzleLevel



APawnCursor::APawnCursor()
{
	PrimaryActorTick.bCanEverTick = true;

	//@@@@ still go through blueprints to get to this StaticMesh

	SceneCursor = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Cursor"));
	RootComponent = SceneCursor;

	CursorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cursor Mesh"));
	CursorMesh->SetupAttachment(SceneCursor);


	TransferSack = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite"));
	TransferSack->SetupAttachment(SceneCursor);

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
	//set start variables
	Table_Address = Hub->StartingTable_Address;
	CurrentLocation = Hub->BoardArbiter->GetLocationFromTable_Address(Table_Address);
	CurrentLocation.Z += HoverAmount;

	//set location and rotation
	Hub->PawnCursor->SceneCursor->SetWorldLocation(CurrentLocation);
	Hub->PawnCursor->SceneCursor->SetWorldRotation({ 0.f,0.f,0.f });
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

	PlayerInputComponent->BindAction("D_Pad_Left", IE_Pressed, this, &APawnCursor::D_Pad_Left);
	PlayerInputComponent->BindAction("D_Pad_Right", IE_Pressed, this, &APawnCursor::D_Pad_Right);

	PlayerInputComponent->BindAction("Cursor:GrabReleaseConfirm", IE_Pressed, this, &APawnCursor::GrabReleaseConfirm);
	PlayerInputComponent->BindAction("Cursor:Rotate", IE_Pressed, this, &APawnCursor::Rotate);
	PlayerInputComponent->BindAction("Cursor:TransferSack", IE_Pressed, this, &APawnCursor::ToggleTransferSackMode);
}

void APawnCursor::CalculateLeftRight(float Value)
{
	/* This early exit is a one time skip of setting the LeftRight direction.  This is triggered when
	the LeftRight direction is set with pressing the digital pad instead. */


	//exit early, once
	if (bSkipLeftRightTick == true) {
		bSkipLeftRightTick = false;
		return;
	}

	LeftRightValue = Value;

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

void APawnCursor::D_Pad_Left()
{
	//if on rack
	if (Table_Address.Board == RACK) {
		UE_LOG(LogTemp, Warning, TEXT("Pressed Left On Rack"))
		LeftRight = d_LEFT;

		//this will cause the left thumb stick to skip a tick
		bSkipLeftRightTick = true;
	}
}

void APawnCursor::D_Pad_Right()
{
	//if on rack
	if (Table_Address.Board == RACK) {
		UE_LOG(LogTemp, Warning, TEXT("Pressed Right On Rack"))
		LeftRight = d_RIGHT;

		//this will cause the left thumb stick to skip a tick
		bSkipLeftRightTick = true;
	}
}

void APawnCursor::GrabReleaseConfirm()
{
	UE_LOG(LogTemp, Error, TEXT("Gamepad: GrabReleaseConfirm"))

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
			Hub->BoardArbiter->FindAllMovableClusters(Table_Address, &AllMovableClusters);

			//if AllMoveableClusters is 0
			if (AllMovableClusters.Num() == 0) {

				Hub->Animator->TableLightFlash();

				UE_LOG(LogTemp, Error, TEXT("Nothing To Pick Up"))



			}
			//if AllMoveableClusters is 1
			else if (AllMovableClusters.Num() == 1) {

				//initial ItemPiece
				UPiece* ItemPiece = nullptr;

				//find ItemPiece
				if (AllMovableClusters[0]->HeldPieces[0]->bIsItemPiece == true) {
					if (AllMovableClusters[0]->HeldPieces[0]->bIsActivated == true) {
						ItemPiece = AllMovableClusters[0]->HeldPieces[0];
					}
				}

				//if ItemPiece found
				if (ItemPiece) {
					Hub->PieceArbiter->TriggerItemPiece(ItemPiece);
				}
				//if no ItemPiece
				else {
					//pick up piece
					HandlePickingUpCluster(AllMovableClusters[0]);
				}
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
					bool bDidSucceed = Hub->BoardArbiter->DropClusterSomewhereInTheBinOfThisPuzzle(InHand[0], NewLetter);

					if (bDidSucceed) {

						//condense
						UCluster* Cluster = InHand[0];

						//take piece out of hand
						InHand.Empty();

						//set cursor to future transform
						Hub->Animator->SetCursorToFutureTransform();

						//detach cluster from cursor
						Cluster->ActorClusterPtr->SceneComp->DetachFromComponent(FDetachmentTransformRules(
							EDetachmentRule::KeepWorld,
							EDetachmentRule::KeepWorld,
							EDetachmentRule::KeepWorld, true));

						//move actorpieces
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
				if (Hub->BoardArbiter->IsPlacementPossible(InHand[0])) {

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

			//if ItemPiece
			if (InHand[0]->HeldPieces[0]->bIsItemPiece) {

				//condense
				UPiece* ItemPiece = InHand[0]->HeldPieces[0];

				//increment rotations
				ItemPiece->ActivationRotations++;

				if (ItemPiece->ActivationRotations >= 6) {
					ArmDisarmItemPiece(ItemPiece);
				}
			}




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

void APawnCursor::ToggleTransferSackMode()
{
	//toggle
	TransferSack->ToggleVisibility();
	bIsTransferSackMode = !bIsTransferSackMode;

	//if pieces in sack
	if (InSack.Num() != 0) {

		//if on rack, send pieces to new puzzle
		if (Table_Address.Board == RACK) {

			//get new puzzle letter
			TEnumAsByte<E_PuzzleLetter> NewLetter = Hub->RackArbiter->ReturnCurrentPortraitPuzzleLetter(Table_Address.Col);

			//loop clusters
			for (auto& Cluster : InSack) {

				//send to new puzzle
				Hub->BoardArbiter->DropClusterSomewhereInTheBinOfThisPuzzle(Cluster, NewLetter);
			}

			//empty sack
			InSack.Empty();
		}
		//if on bin or grid, drop pieces
		if (Table_Address.Board == GRID || Table_Address.Board == BIN) {

			//drop clusters in sack
			TArray<UCluster*> ClustersNotPlacedArray = 
				Hub->BoardArbiter->DropAllTheseClustersNearThisAddress(InSack, Table_Address);

			//if resulting array not empty
			if (ClustersNotPlacedArray.Num() != 0) {
				//loop array
				for (auto& Cluster : ClustersNotPlacedArray) {
					bool bSuccess = Hub->BoardArbiter->DropClusterSomewhereInTheBinOfThisPuzzle(Cluster, Table_Address.PuzzleLetter);

					//if still not working
					if (!bSuccess) {
						bool bNowSuccess = Hub->BoardArbiter->DropClusterSomewhereInTheBinOfThisPuzzle(Cluster, pJUNCTION);

						//if still not
						//@@@@ send to bag, where there are no limits!
					}
					//@@@@ what happens if cluster still not placed here
				}
			}

			//empty sack
			InSack.Empty();
		}

	}
}




//CHANGE INFO

void APawnCursor::DeterminePerformMovement() 
{

	//if in Radial Choice Mode
	if (bIsRadialChoiceMode) {

		//if a valid TriPick is inputted
		if (TriPick != 0) {

			UCluster* PossibleSelectedClusterPtr;
			PossibleSelectedClusterPtr = Hub->BoardArbiter->FindPossibleClusterToSelect(Table_Address, TriPick);

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
		const TEnumAsByte<E_Direction> Direction = ProposedDirection;
		FString DirectionString = UEnum::GetValueAsString(Direction.GetValue());
		UE_LOG(AGridMovement, Warning, TEXT("MOVEMENT -> %s"), *DirectionString)
		UE_LOG(AGridMovement, Warning, TEXT("Cursor FROM: %s %i-%i,%i"),
				*FromBoardString,
				Table_Address.Col,
				Table_Address.Row,
				Table_Address.Tri)

	//make location package
	FLocationPackage Package = FLocationPackage();
	Package.Table_Address = Table_Address;
	Package.ProposedDirection = ProposedDirection;

/* ALTER PACKAGE */

	//if on RACK
	if (Table_Address.Board == RACK) {
		Hub->RackArbiter->ChangeLocationPackageToGetMovementDestination(&Package);
	}
	//if on GRID or BIN
	else {
		Hub->BoardArbiter->ChangeLocationPackageToGetMovementDestination(&Package);
	}

	//find new world location
	Package.NewLocation = Hub->BoardArbiter->GetLocationFromTable_Address(Package.NewTable_Address);

/* FINISHED ALTERING PACKAGE */

	//set new cursor location
	CurrentLocation = Package.NewLocation;
	CurrentLocation.Z += HoverAmount;

	//set new cursor address
	Table_Address.Board = Package.NewTable_Address.Board;
	Table_Address.Col = Package.NewTable_Address.Col;
	Table_Address.Row = Package.NewTable_Address.Row;

	//start movement sequence of cursor
	Hub->Animator->MoveCursorToNewLocation(CurrentLocation);

		//DEBUG
		const TEnumAsByte<E_Board> Board = Table_Address.Board;
		FString BoardString = UEnum::GetValueAsString(Board.GetValue());
		UE_LOG(AGridMovement, Warning, TEXT("Cursor To: %s %i-%i,%i"),
			*BoardString,
			Table_Address.Col,
			Table_Address.Row,
			Table_Address.Tri)

	//change address on any held pieces
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

void APawnCursor::HandlePickingUpCluster(UCluster* GrabbedCluster)
{
	//set pickedupaddress on cluster
	GrabbedCluster->PickedUpAddress = GrabbedCluster->Table_Address;

	//take cluster out of grid
	Hub->BoardArbiter->PickClusterOffBoard(GrabbedCluster);

	//set cursor to future transform
	Hub->Animator->SetCursorToFutureTransform();

	//TransferSack Mode
	if (bIsTransferSackMode) {

		//change cluster and piece status
		Hub->PieceArbiter->SetNewStateForClusterAndItsPieces(GrabbedCluster, INSACK);

		//put cluster into Sack
		InSack.Emplace(GrabbedCluster);

		Hub->PieceArbiter->PutActorClusterIntoSack(GrabbedCluster);

		UE_LOG(LogTemp, Warning, TEXT("AMOUNT IN SACK: %i"), InSack.Num())
	}
	//Standard Mode
	else {
		//change cluster and piece status
		Hub->PieceArbiter->SetNewStateForClusterAndItsPieces(GrabbedCluster, INHAND);

		//put cluster into Hand
		InHand.Emplace(GrabbedCluster);

		//lift cluster
		FVector NewLocation = GrabbedCluster->ActorClusterPtr->SceneComp->GetComponentLocation();
		NewLocation.Z += HoverAmount;
		GrabbedCluster->ActorClusterPtr->SceneComp->SetWorldLocation(NewLocation);

		//attach Cluster to Cursor
		GrabbedCluster->ActorClusterPtr->SceneComp->AttachToComponent(CursorMesh, FAttachmentTransformRules(
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepWorld, true));

	}
}

void APawnCursor::HandleDroppingCluster(UCluster* DroppedCluster)
{
	//put cluster onto board
	Hub->BoardArbiter->PlaceClusterOntoBoard(DroppedCluster);

	//change cluster and piece status
	if (DroppedCluster->Table_Address.Board == GRID) {
		Hub->PieceArbiter->SetNewStateForClusterAndItsPieces(DroppedCluster, ONGRID);
	}
	if (DroppedCluster->Table_Address.Board == BIN) {
		Hub->PieceArbiter->SetNewStateForClusterAndItsPieces(DroppedCluster, INBIN);
	}

	//take piece out of hand
	InHand.Empty();

	//set cursor to future transform
	Hub->Animator->SetCursorToFutureTransform();

	//if settings, cement
	if (Hub->GameInstance->GameplaySettings.bIsAHomePieceCementedOnDrop) {
		Hub->PieceArbiter->ClusterCementCheck(DroppedCluster);
	}

	//detach cluster from cursor
	DroppedCluster->ActorClusterPtr->SceneComp->DetachFromComponent(FDetachmentTransformRules(
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld, true));

	//move actorpieces
	Hub->PieceArbiter->MoveClusterMeshToBoard(DroppedCluster);

	//handle joining pieces
	if (Hub->GameInstance->GameplaySettings.bDoPiecesJoin) {
		Hub->BoardArbiter->HandleJoiningPieces(DroppedCluster);
	}
}

void APawnCursor::ExitChecks()
{
	if (bIsRadialChoiceMode) {

		//reset visuals of Cursor and Cluster/Pieces
		Hub->Animator->ResetRadialChoiceMode();

		ExitRadialChoiceMode();
	}

	//if cluster in hand
	if (InHand.Num() != 0) {

		if (InHand[0]->Table_Address.Board == BIN) {

			//check if possible
			if (Hub->BoardArbiter->IsPlacementPossible(InHand[0])) {
				HandleDroppingCluster(InHand[0]);
			}
			else {
				Hub->BoardArbiter->DropClusterWhereItWasPickedUp(InHand[0], Table_Address);
			}
		}
		else {
			Hub->BoardArbiter->DropClusterWhereItWasPickedUp(InHand[0], Table_Address);
		}
	}

	//if clusters in sack
	if (InSack.Num() != 0) {

		//loop sack clusters
		for (auto& Cluster : InSack) {
			//place cluster back into bin
			Hub->BoardArbiter->DropClusterSomewhereInTheBinOfThisPuzzle(Cluster, Cluster->Table_Address.PuzzleLetter);
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
	//if standard puzzle
	else {
		//if on rack
		if (Table_Address.Board == RACK) {

			//int32 col = FMath::RoundHalfFromZero(Hub->PuzzleGridWidth);

			int32 col = (Hub->PuzzleGridWidth) / 2;
			int32 row;

			//if even
			if (col % 2 == 0) {
				row = 3;
			}
			//if odd
			else {
				row = 4;
			}

			SendCursorToThisCoordinate(col, row, GRID);
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
	//if standard puzzle
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

void APawnCursor::ArmDisarmItemPiece(UPiece* ItemPiece)
{
	
	//if not activated
	if (ItemPiece->bIsActivated == false) {
		ItemPiece->bIsActivated = true;

		UE_LOG(LogTemp, Warning, TEXT("ItemPiece activated"))

		Hub->PieceArbiter->ArmItemPiece(ItemPiece);
	}



	////if activated
	//if (ItemPiece->bIsActivated == true) {
	//	ItemPiece->bIsActivated = false;

	//		Hub->PieceArbiter->DisarmItemPiece(ItemPiece);
	//}
	////if not activated
	//else {
	//	ItemPiece->bIsActivated = true;

	//	// Arm Animation
	//	Hub->PieceArbiter->ArmItemPiece(ItemPiece);
	//}

}



