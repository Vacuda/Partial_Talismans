// Copyright 2020 Vacuda


#include "BinArbiter.h"

#include "Talismans/Talismans.h"								// for AHomeCheck
#include "Talismans/Admin/TheGameInstance.h"					// for TheGameInstance
#include "Talismans/Admin/Hub.h"								// for Hub
#include "Talismans/TableNavigation/PieceArbiter.h"				// for PieceArbiter
#include "Talismans/TableNavigation/RackArbiter.h"				// for RackArbiter
#include "Talismans/TableNavigation/Animator.h"					// for Animator
#include "Talismans/TableNavigation/TableNavigator.h"			// for Navigator
#include "Talismans/Structs/FLocationPackage.h"					// custom header file
#include "Talismans/Structs/FTable_Address.h"					// for FTable_Address
#include "Talismans/Structs/FJoinUnit.h"						// for FJoinUnit
#include "Talismans/Pieces/Cluster.h"							// for Cluster
#include "Talismans/Pieces/MeshCluster.h"						// for MeshCluster
#include "Talismans/Pieces/Piece.h"								// for Piece

// SETUP

void UBinArbiter::CatchTheHub(UHub* _Hub)
{
	Hub = _Hub;
}

// GATHER INFO

void UBinArbiter::FindAllMovableClusters(FTable_Address Table_Address, TArray<ACluster*>* AllMovableClusters)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	int32 col = Table_Address.Col;
	int32 row = Table_Address.Row;

	FRowHex& Hex = Puzzle.ColMapBin[col].RowMap[row];

	//loop through Hex, find clusters
	for (auto& Tri : Hex.TriMap) {
		if (Tri.Value.PiecePtr) {

			AllMovableClusters->AddUnique(Tri.Value.PiecePtr->ClusterPtr);
		}
	}
}

int32 UBinArbiter::GetCountOfTris(TEnumAsByte <E_PieceShape> Shape)
{
	if (Shape == TRI1) {
		return 1;
	}
	if (Shape == TRI2) {
		return 2;
	}
	if (Shape == TRI3) {
		return 3;
	}
	if (Shape == TRI4) {
		return 4;
	}
	if (Shape == TRI5) {
		return 5;
	}
	if (Shape == TRI6) {
		return 6;
	}
	//safety check
	return 1;
}

bool UBinArbiter::IsPlacementPossible(ACluster* Cluster)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Cluster->Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//loop pieces
	for (auto& Piece : Cluster->HeldPieces) {

		int32 col = Piece->Table_Address.Col;
		int32 row = Piece->Table_Address.Row;
		int32 tri = Piece->Table_Address.Tri;

		//get an iteration count for the amount of tris in shape
		int32 tricount = GetCountOfTris(Piece->Shape);

		//iterate tricount times
		for (int32 i = 1; i <= tricount; i++) {

			//key check
			if (Puzzle.ColMapBin.Contains(col)) {
				if (Puzzle.ColMapBin[col].RowMap.Contains(row)) {

					FTriangleUnit& TargetTri = Puzzle.ColMapBin[col].RowMap[row].TriMap[tri];
				
					if (TargetTri.PiecePtr) {
						//move is not possible
						return false;
					}
				}
				else {
					//move is not possible
					return false;
				}
			}
			else {
				//move is not possible
				return false;
			}

			//iterate tri
			tri++;

			//reset tri if over 6
			if (tri == 7) {
				tri = 1;
			}
		}
	}

	//move is possible
	return true;
}

ACluster* UBinArbiter::FindPossibleClusterToSelect(FTable_Address Table_Address, int32 TriPick)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	int32 col = Table_Address.Col;
	int32 row = Table_Address.Row;
	int32 tri = TriPick;

	UE_LOG(LogTemp, Warning, TEXT("TriPick: %i"), TriPick)

	//get Tri
	FTriangleUnit& Tri = Puzzle.ColMapBin[col].RowMap[row].TriMap[tri];

	//if MeshPiece in Tri
	if (Tri.PiecePtr) {
		return Tri.PiecePtr->ClusterPtr;
	}

	//if not found
	return nullptr;
}

TEnumAsByte <E_Segment> UBinArbiter::GetSegment(int32 SegmentCount)
{
	if (SegmentCount == 1) {
		return SEG1;
	}
	if (SegmentCount == 2) {
		return SEG2;
	}
	if (SegmentCount == 3) {
		return SEG3;
	}
	if (SegmentCount == 4) {
		return SEG4;
	}
	if (SegmentCount == 5) {
		return SEG5;
	}
	if (SegmentCount == 6) {
		return SEG6;
	}
	//safety
	return SEGNONE;
}

// DEBUG

int32 UBinArbiter::GetNum()
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	int32 AmountFilled = 0;

	//loop cols
	for (auto& Col : Puzzle.ColMapBin) {

		//loop rows
		for (auto& Row : Col.Value.RowMap) {

			//loop tri
			for (auto& Tri : Row.Value.TriMap) {

				if (Tri.Value.PiecePtr) {
					AmountFilled++;
				}
			}
		}
	}

	return AmountFilled;
}

// MAKE CHANGES

void UBinArbiter::ChangeLocationPackageToGetMovementDestination(FLocationPackage* Package)
{
	//set default with Current Col and Row
	int32 NewCol = Package->Table_Address.Col;
	int32 NewRow = Package->Table_Address.Row;

	//calculate new col and row
	CalculateNewPositionOnBin(&NewCol, &NewRow, Package->ProposedDirection);

	//set default change of board
	Package->NewTable_Address.Board = BIN;

	//if JUNCTION
	if (Package->Table_Address.PuzzleLetter == pJUNCTION) {

		//off the bin top
		if (NewRow < 1) {

			//if UP
			if (Package->ProposedDirection == d_UP) {
				//reset
				NewRow = Package->Table_Address.Row;
			}
			//if UPLEFT or UPRIGHT
			else {
				//hot fix to stay more on grid
				NewRow = Package->Table_Address.Row + 1;
			}
		}

		//off the bin bot
		if (NewRow > 24) {

			//if DOWN
			if (Package->ProposedDirection == d_DOWN) {

				//if in rack range
				if (NewCol <= 9) {
					//send to rack
					Package->NewTable_Address.Board = RACK;
					NewCol = Hub->RackArbiter->FindNewRackColumn(NewCol);
					NewRow = 1;

					UE_LOG(LogTemp, Warning, TEXT("NewCol:::should be 2::::: %i"), NewCol);

					//alter rackcolumn, if needed
					NewCol = Hub->RackArbiter->AlterRackColumnIfNeeded(NewCol);

					UE_LOG(LogTemp, Warning, TEXT("NewCol:::should be 1::::: %i"), NewCol);
				}
				else {
					//send to bag

					//reset, before having bag
					NewRow = Package->Table_Address.Row;
				}
			}
			//if DOWNLEFT or DOWNRIGHT
			else {
				//hot fix to stay more on grid
				NewRow = Package->Table_Address.Row - 1;
			}
		}

		//off the bin left
		if (NewCol < 2) { //bin starts at 2

			//moving onto rack, newcol of 1 is okay
			if (Package->NewTable_Address.Board != RACK) {
				NewCol = Package->Table_Address.Col;
				NewRow = Package->Table_Address.Row;
			}
		}

		//off the bin right
		if (NewCol > 25) {
			NewCol = Package->Table_Address.Col;
			NewRow = Package->Table_Address.Row;
		}
	}
	//if regular puzzle
	else {

		//off the bin top
		if (NewRow < 1) {

			//if UP
			if (Package->ProposedDirection == d_UP) {
				//reset
				NewRow = Package->Table_Address.Row;
			}
			//if UPLEFT or UPRIGHT
			else {
				//hot fix to stay more on grid
				NewRow = Package->Table_Address.Row + 1;
			}
		}

		//off the bin bot
		if (NewRow > 12) {

			//if DOWN
			if (Package->ProposedDirection == d_DOWN) {
				//reset
				NewRow = Package->Table_Address.Row;
			}
			//if DOWNLEFT or DOWNRIGHT
			else {
				//hot fix to stay more on grid
				NewRow = Package->Table_Address.Row - 1;
			}	
		}

		//@@@@ not dynamic for different grid sizes

		//off the bin left
		if (NewCol < 2) { //bin starts at 2

			//change to grid
			NewCol = Hub->PuzzleGridWidth;
			Package->NewTable_Address.Board = GRID;

			//if no cooresponding row
			if (NewRow > Hub->PuzzleGridHeight) {

				int32 OldRow = Package->Table_Address.Row;

				if (OldRow == 7) {
					NewRow = 6;
				}
				if (OldRow == 9) {
					if (Package->ProposedDirection == d_UPLEFT) {
						NewRow = 6;
					}
					if (Package->ProposedDirection == d_DOWNLEFT) {

						//send to rack
						Package->NewTable_Address.Board = RACK;
						NewCol = 4;
						NewRow = 1;

						//alter rackcolumn, if needed
						NewCol = Hub->RackArbiter->AlterRackColumnIfNeeded(NewCol);
					}
				}
				if (OldRow == 11) {

					//send to rack
					Package->NewTable_Address.Board = RACK;
					NewCol = 4;
					NewRow = 1;

					//alter rackcolumn, if needed
					NewCol = Hub->RackArbiter->AlterRackColumnIfNeeded(NewCol);
				}
			}
		}

		//off the bin right
		if (NewCol > 13) {
			NewCol = Package->Table_Address.Col;
			NewRow = Package->Table_Address.Row;
		}
	}


	//change address Col and Row
	Package->NewTable_Address.Col = NewCol;
	Package->NewTable_Address.Row = NewRow;

	//change colchange and rowchange
	Package->ColChange = NewCol - Package->Table_Address.Col;
	Package->RowChange = NewRow - Package->Table_Address.Row;

	//if going to grid or rack
	if (Package->NewTable_Address.Board != BIN) {
		/*Hub->Animator->ScrollToElement_Left();*/
	}

	//if moving off screen
	if (Package->NewTable_Address.Col >= 8) {
		//Hub->Animator->ScrollToElement_Right();
	}
}

void UBinArbiter::CalculateNewPositionOnBin(int32* NewCol, int32* NewRow, TEnumAsByte<E_Direction> ProposedDirection)
{
	if (ProposedDirection == d_UP) {
		*NewRow = *NewRow - 2;
	}
	if (ProposedDirection == d_UPRIGHT) {
		*NewCol = *NewCol + 1;
		*NewRow = *NewRow - 1;
	}
	if (ProposedDirection == d_DOWNRIGHT) {
		*NewCol = *NewCol + 1;
		*NewRow = *NewRow + 1;
	}
	if (ProposedDirection == d_DOWN) {
		*NewRow = *NewRow + 2;
	}
	if (ProposedDirection == d_DOWNLEFT) {
		*NewCol = *NewCol - 1;
		*NewRow = *NewRow + 1;
	}
	if (ProposedDirection == d_UPLEFT) {
		*NewCol = *NewCol - 1;
		*NewRow = *NewRow - 1;
	}
	//if (ProposedDirection == d_LEFT) {
	//	*NewCol = *NewCol - 1;
	//}
	//if (ProposedDirection == d_RIGHT) {
	//	*NewCol = *NewCol + 1;
	//}
}

//TEnumAsByte<E_Direction> UBinArbiter::SetRowChangeDirection(TEnumAsByte<E_Direction> ProposedDirection)
//{
//
//	if (ProposedDirection == d_UP) {
//		return d_UP;
//	}
//	if (ProposedDirection == d_UPRIGHT) {
//		return d_UPRIGHT;
//	}
//	if (ProposedDirection == d_RIGHT) {
//		return d_NONE;
//	}
//	if (ProposedDirection == d_DOWNRIGHT) {
//		return d_DOWNRIGHT;
//	}
//	if (ProposedDirection == d_DOWN) {
//		return d_DOWN;
//	}
//	if (ProposedDirection == d_DOWNLEFT) {
//		return d_DOWNLEFT;
//	}
//	if (ProposedDirection == d_LEFT) {
//		return d_NONE;
//	}
//	if (ProposedDirection == d_UPLEFT) {
//		return d_UPLEFT;
//	}
//	//shouldn't happen
//	return d_NONE;
//}

// MOVE PIECE

void UBinArbiter::PickClusterOffBin(ACluster* Cluster)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Cluster->Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//loop pieces
	for (auto& Piece : Cluster->HeldPieces) {

		int32 col = Piece->Table_Address.Col;
		int32 row = Piece->Table_Address.Row;
		int32 tri = Piece->Table_Address.Tri;

		UE_LOG(AGridMovement, Warning, TEXT("Piece picked up: %i-%i,%i"),
			Piece->Table_Address.Col,
			Piece->Table_Address.Row,
			Piece->Table_Address.Tri)

		//get an iteration count for the amount of tris in shape
		int32 tricount = GetCountOfTris(Piece->Shape);

		//iterate tricount times
		for (int32 i = 1; i <= tricount; i++) {

			FTriangleUnit& TargetTri = Puzzle.ColMapBin[col].RowMap[row].TriMap[tri];

			const TEnumAsByte<E_Segment> Seg = TargetTri.Segment;
			FString SegString = UEnum::GetValueAsString(Seg.GetValue());
			UE_LOG(AHomeCheck, Warning, TEXT("Segment picked up: %s"), *SegString)

			//take out of grid
			TargetTri.bIsFilled = false;
			TargetTri.bIsOrigin = false;
			TargetTri.PiecePtr = nullptr;
			TargetTri.Segment = SEGNONE;

			//iterate tri
			tri++;

			//reset TriIndex if over 6
			if (tri == 7) {
				tri = 1;
			}
		}
	}
} 

void UBinArbiter::PlaceClusterIntoBin(ACluster* Cluster)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Cluster->Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//loop pieces
	for (auto& Piece : Cluster->HeldPieces) {

		int32 col = Piece->Table_Address.Col;
		int32 row = Piece->Table_Address.Row;
		int32 tri = Piece->Table_Address.Tri;

		UE_LOG(AGridMovement, Warning, TEXT("Piece placed on board: %i-%i,%i"),
			Piece->Table_Address.Col,
			Piece->Table_Address.Row,
			Piece->Table_Address.Tri)

		//get an iteration count for the amount of tris in shape
		int32 tricount = GetCountOfTris(Piece->Shape);

		//iterate tricount times
		for (int32 i = 1; i <= tricount; i++) {
			FTriangleUnit& TargetTri = Puzzle.ColMapBin[col].RowMap[row].TriMap[tri];

			//if first, make origin
			if (i == 1) {
				TargetTri.bIsOrigin = true;
			}

			TargetTri.bIsFilled = true;
			TargetTri.PiecePtr = Piece;
			TargetTri.Segment = GetSegment(i);

			const TEnumAsByte<E_Segment> Seg = TargetTri.Segment;
			FString SegString = UEnum::GetValueAsString(Seg.GetValue());
			UE_LOG(AHomeCheck, Warning, TEXT("Segment placed: %s"), *SegString)

			//iterate tri
			tri++;

			//reset tri if over 5
			if (tri == 7) {
				tri = 1;
			}
		}
	}
}

void UBinArbiter::DropClusterWhereItWasPickedUp(ACluster* Cluster, FTable_Address PivotAddress)
{
	//rotate to match picked up tri
	while (Cluster->Table_Address.Tri != Cluster->PickedUpAddress.Tri) {
		UE_LOG(LogTemp, Warning, TEXT("......rotate to match"))
		Hub->PieceArbiter->RotateClusterAndPieceInfo(Cluster, PivotAddress);
	}

	//gather info
	int32 ColChange = Cluster->PickedUpAddress.Col - Cluster->Table_Address.Col;
	int32 RowChange = Cluster->PickedUpAddress.Row - Cluster->Table_Address.Row;
	TEnumAsByte<E_Board> NewBoard = Cluster->PickedUpAddress.Board;
	TEnumAsByte<E_PuzzleLetter> NewPuzzleLetter = Cluster->PickedUpAddress.PuzzleLetter;

	//set new address
	Hub->PieceArbiter->SetNewTable_Address(Cluster, NewPuzzleLetter, NewBoard, ColChange, RowChange);

	//place onto board
	Hub->Navigator->PlaceClusterOntoBoard(Cluster);

	//detach cluster from cursor
	Cluster->MeshClusterPtr->SceneComp->DetachFromComponent(FDetachmentTransformRules(
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld, true));

	//move mesh pieces
	Hub->Navigator->MoveClusterMeshToBoard(Cluster);
}

bool UBinArbiter::DropClusterSomewhereInTheBinOfThisPuzzle(ACluster* Cluster, TEnumAsByte<E_PuzzleLetter> PuzzleLetter)
{

	/* This will find a home for a piece that we are transferring to a new puzzle*/

	//store current cluster address
	FTable_Address OldAddress = Cluster->Table_Address;

	//condense
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

//SPACED OUT CHECK

	//loop cols
	for (auto& Col : Puzzle.ColMapBin) {
		//loop rows
		for (auto& Row : Col.Value.RowMap) {

			//check if Hex is open
			bool bIsOpenHex = true;

				//loop tris
				for (auto& Tri : Row.Value.TriMap) {
					if (Tri.Value.bIsFilled) {
						bIsOpenHex = false;
						break;
					}
				}

			//if whole hex is open
			if (bIsOpenHex == true) {

				//change cluster and pieces to possible new address
				int32 ColChange = Col.Key - Cluster->Table_Address.Col;
				int32 RowChange = Row.Key - Cluster->Table_Address.Row;
				Hub->PieceArbiter->SetNewTable_Address(Cluster, PuzzleLetter, BIN, ColChange, RowChange);

				//try to place cluster
				if (IsPlacementPossible(Cluster)) {

					UE_LOG(LogTemp, Warning, TEXT("SUCCESS in moving piece*******************"))
					UE_LOG(LogTemp, Warning, TEXT("Col.Key: %i  Row.Key: %i"), Col.Key, Row.Key)

					PlaceClusterIntoBin(Cluster);

					//can return since cluster was placed
					return true;
				}
			}
		}
	}

//PRECISE CHECK

	//this checks every tri at this rotation
	//if that doesn't work, rotate
	//if rotating 5 times still doesn't work, there's no place for it
	
	int32 RotationCheck = 1;

	//check 6 times for each rotation
	while (RotationCheck < 7) {

		//condense
		int32 TriToCheck = Cluster->Table_Address.Tri;

		//loop cols
		for (auto& Col : Puzzle.ColMapBin) {
			//loop rows
			for (auto& Row : Col.Value.RowMap) {

				//if not filled
				if (!Row.Value.TriMap[Cluster->Table_Address.Tri].bIsFilled) {

					//change cluster and pieces to possible new address
					int32 ColChange = Col.Key - Cluster->Table_Address.Col;
					int32 RowChange = Row.Key - Cluster->Table_Address.Row;
					Hub->PieceArbiter->SetNewTable_Address(Cluster, PuzzleLetter, BIN, ColChange, RowChange);
				
					//try to place cluster
					if (IsPlacementPossible(Cluster)) {

						PlaceClusterIntoBin(Cluster);

						//can return since cluster was placed
						return true;
					}
				}
			}
		}

		//cluster was not placed, rotate once
		Hub->PieceArbiter->RotateClusterAndPieceInfo(Cluster, Cluster->Table_Address);

		//iterate RotationsChecked
		RotationCheck++;
	}

	//cluster can't find a home
	//set address back to original
	//it will have rotated back to its original tri
	int32 ColChange = OldAddress.Col - Cluster->Table_Address.Col;
	int32 RowChange = OldAddress.Row - Cluster->Table_Address.Row;
	Hub->PieceArbiter->SetNewTable_Address(Cluster, OldAddress.PuzzleLetter, OldAddress.Board, ColChange, RowChange);

	//action failed
	return false;
}

// JOIN PIECES

void UBinArbiter::HandleJoiningPieces(ACluster* Cluster)
{
	UE_LOG(AHomeCheck, Error, TEXT("+++++CLUSTER DROPPED+++++"))

	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//make array here because heldpieces will change during iteration
	TArray<APiece*> PiecesToCheck;

	//loop pieces
	for (auto& Piece : Cluster->HeldPieces) {
		PiecesToCheck.Emplace(Piece);
	}

	//loop piecestocheck
	for (auto& Piece : PiecesToCheck) {

		UE_LOG(LogTemp, Warning, TEXT("JoinCheck"))
		UE_LOG(LogTemp, Warning, TEXT("&&&&&&& Piece Col: %i"), Piece->Table_Address.Col)
		UE_LOG(LogTemp, Warning, TEXT("&&&&&&& Piece Row: %i"), Piece->Table_Address.Row)
		UE_LOG(LogTemp, Warning, TEXT("&&&&&&& Piece Tri: %i"), Piece->Table_Address.Tri)

		//condense
		int32 col = Piece->Table_Address.Col;
		int32 row = Piece->Table_Address.Row;
		int32 tri = Piece->Table_Address.Tri;

		//loop joinmap
		for (auto& Join : Piece->JoinMap) {

			//skip if already connected
			if (Join.Value.bIsConnected) {
				continue;
			}

			//if jLOW
			if (Join.Key == jLOW) {

				UE_LOG(AHomeCheck, Display, TEXT("jLOW check"))

				int32 TriToCheck = tri - 1;

				//reset TriToCheck, if needed
				if (TriToCheck == 0) {
					TriToCheck = 6;
				}

				APiece* MatchingHomePiece = DetermineIfThereIsAHomePieceMatch(col, row, TriToCheck, Join.Value);

				if (MatchingHomePiece) {
					Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
				}
			}

			//if jHIGH
			if (Join.Key == jHIGH) {

				UE_LOG(AHomeCheck, Display, TEXT("jHIGH check"))

				int32 TriToCheck = tri + GetCountOfTris(Piece->Shape);

				//reset TriToCheck, if needed
				if (TriToCheck > 6) {
					TriToCheck = TriToCheck - 6;
				}

				APiece* MatchingHomePiece = DetermineIfThereIsAHomePieceMatch(col, row, TriToCheck, Join.Value);

				if (MatchingHomePiece) {
					Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
				}
			}

			// if jTRI1
			if (Join.Key == jTRI1) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI1 check"))

				if (tri == 1) {
					APiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					APiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					APiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					APiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					APiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					APiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI2
			if (Join.Key == jTRI2) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI2 check"))

					int32 tri_offset = 1;

				if (tri == 1) {
					APiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					APiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					APiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					APiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					APiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					APiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI3
			if (Join.Key == jTRI3) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI3 check"))

					int32 tri_offset = 2;

				if (tri == 1) {
					APiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					APiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					APiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					APiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					APiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					APiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI4
			if (Join.Key == jTRI4) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI4 check"))

					int32 tri_offset = 3;

				if (tri == 1) {
					APiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					APiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					APiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					APiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					APiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					APiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI5
			if (Join.Key == jTRI5) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI5 check"))

					int32 tri_offset = 4;

				if (tri == 1) {
					APiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					APiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					APiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					APiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					APiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					APiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI6
			if (Join.Key == jTRI6) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI6 check"))

					int32 tri_offset = 5;

				if (tri == 1) {
					APiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					APiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					APiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					APiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					APiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					APiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			UE_LOG(AHomeCheck, Error, TEXT("---------------"))
		}
		
	}
}

APiece* UBinArbiter::CheckInDirection_Up(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit)
{
	int32 NewCol = col;
	int32 NewRow = row - 2;
	int32 NewTri = tri + 3; //opposite tri

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit);
}

APiece* UBinArbiter::CheckInDirection_UpLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit)
{
	int32 NewCol = col - 1;
	int32 NewRow = row - 1;
	int32 NewTri = tri + 3; //opposite tri

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit);
}

APiece* UBinArbiter::CheckInDirection_UpRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit)
{
	int32 NewCol = col + 1;
	int32 NewRow = row - 1;
	int32 NewTri = tri + 3; //opposite tri

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit);
}

APiece* UBinArbiter::CheckInDirection_Down(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit)
{
	int32 NewCol = col;
	int32 NewRow = row + 2;
	int32 NewTri = tri + 3; //opposite tri

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit);
}

APiece* UBinArbiter::CheckInDirection_DownLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit)
{
	int32 NewCol = col - 1;
	int32 NewRow = row + 1;
	int32 NewTri = tri + 3; //opposite tri

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit);
}

APiece* UBinArbiter::CheckInDirection_DownRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit)
{
	int32 NewCol = col + 1;
	int32 NewRow = row + 1;
	int32 NewTri = tri + 3; //opposite tri

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit);
}

APiece* UBinArbiter::DetermineIfThereIsAHomePieceMatch(int32 NewCol, int32 NewRow, int32 NewTri, FJoinUnit JoinUnit)
{
	//reset tri, if needed
	if (NewTri > 6) {
		NewTri = NewTri - 6;
	}

	//reset tri again, if needed.  possible to cycle past 12 tri
	if (NewTri > 6) {
		NewTri = NewTri - 6;
	}

	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	UE_LOG(LogTemp, Warning, TEXT("Col: %i"), NewCol)
	UE_LOG(LogTemp, Warning, TEXT("Row: %i"), NewRow)
	UE_LOG(LogTemp, Warning, TEXT("Tri: %i"), NewTri)

	//safety check
	if (Puzzle.ColMapBin.Contains(NewCol)) {
		if (Puzzle.ColMapBin[NewCol].RowMap.Contains(NewRow)) {
		}
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}

	//find TriUnit in question
	FTriangleUnit& TriUnit = Puzzle.ColMapBin[NewCol].RowMap[NewRow].TriMap[NewTri];

	//if filled
	if (TriUnit.PiecePtr) {

		UE_LOG(AHomeCheck, Display, TEXT("Piece Found"))

			//if a match
			if (TriUnit.PiecePtr == JoinUnit.PiecePtr) {

				UE_LOG(AHomeCheck, Display, TEXT("Piece Match"))

					if (TriUnit.Segment == JoinUnit.Segment) {
						UE_LOG(AHomeCheckSuccess, Warning, TEXT("JOIN!!!!!!!!!!!!!!!"))

							return TriUnit.PiecePtr;



					}
					else {
						UE_LOG(AHomeCheck, Display, TEXT("Segment  NO  Match"))

					}
				const TEnumAsByte<E_Segment> LookSeg = JoinUnit.Segment;
				FString LookSegString = UEnum::GetValueAsString(LookSeg.GetValue());
				UE_LOG(AHomeCheck, Display, TEXT("Looking for : %s"), *LookSegString)

					const TEnumAsByte<E_Segment> FindSeg = TriUnit.Segment;
				FString FindSegString = UEnum::GetValueAsString(FindSeg.GetValue());
				UE_LOG(AHomeCheck, Display, TEXT("Finding : %s"), *FindSegString)

					UE_LOG(AHomeCheck, Display, TEXT("Other Piece Tri Where Im Looking: %i"), NewTri)
					UE_LOG(AHomeCheck, Display, TEXT("Other Piece Actual Tri: %i"), TriUnit.PiecePtr->Table_Address.Tri)
			}
	}
	else {
		UE_LOG(AHomeCheck, Display, TEXT("--Not Filled"))
	}
	UE_LOG(AHomeCheck, Display, TEXT("---"))

		//no match found
		return nullptr;
}

