// Copyright 2020 Vacuda


#include "BoardArbiter.h"

#include "Talismans/Talismans.h"								// for AHomeCheck
#include "Talismans/Admin/TheGameInstance.h"					// for TheGameInstance
#include "Talismans/Admin/Hub.h"								// for Hub
#include "Talismans/Pawns/PawnCursor.h"							// for PawnCursor
#include "Talismans/TableNavigation/PieceArbiter.h"				// for PieceArbiter
#include "Talismans/TableNavigation/RackArbiter.h"				// for RackArbiter
#include "Talismans/TableNavigation/Animator.h"					// for Animator
#include "Talismans/Structs/FLocationPackage.h"					// custom header file
#include "Talismans/Structs/FTable_Address.h"					// for FTable_Address
#include "Talismans/Structs/FJoinUnit.h"						// for FJoinUnit
#include "Talismans/Structs/FColHex.h"							// for ColHex
#include "Talismans/Structs/FRowHex.h"							// for RowHex
#include "Talismans/Pieces/Cluster.h"							// for Cluster
#include "Talismans/Pieces/ActorCluster.h"						// for ActorCluster
#include "Talismans/Pieces/Piece.h"								// for Piece
#include "Talismans/Pieces/MeshPieceMaker.h"					// for MeshPieceMaker


UBoardArbiter::UBoardArbiter()
{

}


// SETUP

void UBoardArbiter::CatchTheHub(UHub* _Hub)
{
	Hub = _Hub;
}


// GATHER INFO

FVector UBoardArbiter::GetLocationFromTable_Address(FTable_Address Table_Address)
{
	//send to relevant place
	if (Table_Address.Board == BIN) {
		return Hub->BinMesh->GetSocketLocation(Table_Address.ReturnTheSocketCode());
	}
	if (Table_Address.Board == GRID) {
		return Hub->GridMesh->GetSocketLocation(Table_Address.ReturnTheSocketCode());
	}
	if (Table_Address.Board == RACK) {
		return Hub->RackArbiter->ReturnNewCursorLocationOnRack(Table_Address.Col);
	}
	else {
		return { 0.f, 0.f, 0.f };
	}
}

void UBoardArbiter::FindAllMovableClusters(FTable_Address Table_Address, TArray<UCluster*>* AllMovableClusters)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;
	int32 col = Table_Address.Col;
	int32 row = Table_Address.Row;
	FRowHex& Hex = ColMap[col].RowMap[row];

	//loop through Hex, find clusters
	for (auto& Tri : Hex.TriMap) {
		if (Tri.Value.PiecePtr) {
			//avoid CEMENTED pieces
			if (Tri.Value.PiecePtr->State != CEMENTED) {
				AllMovableClusters->AddUnique(Tri.Value.PiecePtr->ClusterPtr);
			}
		}
	}
}

int32 UBoardArbiter::GetCountOfTris(TEnumAsByte <E_PieceShape> Shape)
{
	//standard pieces
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
	//itempieces
	else {
		return 6;
	}
}

bool UBoardArbiter::IsPlacementPossible(UCluster* Cluster)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Cluster->Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Cluster->Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;

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
			if (ColMap.Contains(col)) {
				if (ColMap[col].RowMap.Contains(row)) {

					FTriangleUnit& TargetTri = ColMap[col].RowMap[row].TriMap[tri];

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

UCluster* UBoardArbiter::FindPossibleClusterToSelect(FTable_Address Table_Address, int32 TriPick)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;
	int32 col = Table_Address.Col;
	int32 row = Table_Address.Row;
	int32 tri = TriPick;

	//get Tri
	FTriangleUnit& Tri = ColMap[col].RowMap[row].TriMap[tri];

	//if ActorPiece in Tri
	if (Tri.PiecePtr) {
		return Tri.PiecePtr->ClusterPtr;
	}

	//if not found
	return nullptr;
}

TEnumAsByte <E_Segment> UBoardArbiter::GetSegment(int32 SegmentCount)
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

UPiece* UBoardArbiter::GetItemPieceOnTheBoardHere(FTable_Address Table_Address)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;
	int32 col = Table_Address.Col;
	int32 row = Table_Address.Row;
	int32 tri = Table_Address.Tri;

	//get Tri
	FTriangleUnit& Tri = ColMap[col].RowMap[row].TriMap[tri];

	//if piece present
	if (Tri.PiecePtr) {
		//if itempiece
		if (Tri.PiecePtr->bIsItemPiece == true) {
			return Tri.PiecePtr;
		}
	}

	return nullptr;
}

UCluster* UBoardArbiter::FindClusterInThisDirectionFromThisAddress(TEnumAsByte<E_Direction> Direction, FTable_Address Table_Address)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;
	int32 col = Table_Address.Col;
	int32 row = Table_Address.Row;
	int32 tri = 1;

	/* Depending on direction, change col, row, or tri */

	if (Direction == d_DOWN) {
		row = row + 2;
		tri = 4;
	}
	if (Direction == d_DOWNRIGHT) {
		col = col + 1;
		row = row + 1;
		tri = 5;
	}
	if (Direction == d_UPRIGHT) {
		col = col + 1;
		row = row - 1;
		tri = 6;
	}
	if (Direction == d_UP) {
		row = row - 2;
		tri = 1;
	}
	if (Direction == d_UPLEFT) {
		col = col - 1;
		row = row - 1;
		tri = 2;
	}
	if (Direction == d_DOWNLEFT) {
		col = col - 1;
		row = row + 1;
		tri = 3;
	}

	//safety
	if (ColMap.Contains(col)) {
		if (ColMap[col].RowMap.Contains(row)) {

			//condense
			FTriangleUnit& TriUnit = ColMap[col].RowMap[row].TriMap[tri];

			//if filled
			if (TriUnit.bIsFilled == true) {
				//if not an item piece
				if (TriUnit.PiecePtr->bIsItemPiece == false) {
					//return cluster
					return TriUnit.PiecePtr->ClusterPtr;
				}
			}
		}
	}

	//nothing found
	return nullptr;
}


// MAKE CHANGES

void UBoardArbiter::ChangeLocationPackageToGetMovementDestination(FLocationPackage* Package)
{
	//condense
	TEnumAsByte<E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	int32 PuzzleGridWidth = Hub->PuzzleGridWidth;
	int32 PuzzleGridHeight = Hub->PuzzleGridHeight;
	TEnumAsByte<E_Board> OldBoard = Package->Table_Address.Board;
	TEnumAsByte<E_Direction> ProposedDirection = Package->ProposedDirection;
	float LeftRightValue = Hub->PawnCursor->LeftRightValue;
	int32 OldCol = Package->Table_Address.Col;
	int32 OldRow = Package->Table_Address.Row;

	//set default with Current Col and Row
	int32 NewCol = OldCol;
	int32 NewRow = OldRow;

	//calculate new col and row
	CalculateNewPositionOnBoard(&NewCol, &NewRow, ProposedDirection);

	//set default to no change of board
	Package->NewTable_Address.Board = OldBoard;

/*Now that we've calculated where the inputed direction would take the cursor, we have to 
determine whether it hits any limitations.  Below, I'm only possibly making changes to three variables.
NewRow, NewCol, and NewTable_Address.Board*/


	//off the Board TOP
		if (NewRow < 1) {

			//if UP
			if (ProposedDirection == d_UP) {

				//if odd col, move upleft or upright instead of stalling
				if (NewCol % 2 == 1) {

					//move upright
					if (LeftRightValue >= 0.f) {
						//col moves right
						NewCol++;
						//row set at 1
						NewRow = 1;
					}
					//move upleft
					else {
						//col moves left
						NewCol--;
						NewRow = 1;
					}
				}
				else {
					//reset, no change on row
					NewRow = OldRow;
				}
			}
			//if UPLEFT or UPRIGHT
			else {
				//hot fix to stay more on grid
				NewRow = OldRow + 1;
			}
		}

//GRID
	if (OldBoard == GRID) {

		//off the GRID LEFT
		if (NewCol < 1) {
			NewCol = OldCol;
			NewRow = OldRow;
		}

		//off the GRID RIGHT
		if (NewCol > PuzzleGridWidth) {
			NewCol = 2; /* bin starts at 2 */
			Package->NewTable_Address.Board = BIN;

			//if oldcol is even, correction needed
			if (OldCol % 2 == 0) {
				NewRow = NewRow - 1;
			}

			//constrain from top
			if (NewRow < 1) {
				NewRow = NewRow + 2;
			}
		}

		//if at the GRID BOT - EVEN OR ODD COL
		if (OldRow >= (PuzzleGridHeight * 2) - 1) {
			//if DOWN
			if (ProposedDirection == d_DOWN) {
				Package->NewTable_Address.Board = RACK;
				NewRow = 1;
				NewCol = Hub->RackArbiter->FindNewRackColumn_FromGrid(OldCol);
			}
		}

		//if at the GRID BOT - ODD COL
		if (OldRow >= PuzzleGridHeight * 2) {
			// if DOWNLEFT or DOWNRIGHT
			if (ProposedDirection == d_DOWNLEFT || ProposedDirection == d_DOWNRIGHT) {
				//hot fix to stay more on grid
				NewRow = OldRow - 1;
			}
		}
	}

//BIN
	if (OldBoard == BIN) {

		//JUNCTION
		if (PuzzleLetter == pJUNCTION) {

			//off the BIN BOT
			if (NewRow > 24) {

				//if DOWN
				if (ProposedDirection == d_DOWN) {

					//if in rack range
					if (NewCol <= 9) {
						//send to rack
						Package->NewTable_Address.Board = RACK;
						NewCol = Hub->RackArbiter->FindNewRackColumn_FromJunction(NewCol);
						NewRow = 1;
					}
					else {
						//send to bag

						//reset, no change on row, before having bag
						NewRow = OldRow;
					}
				}
				//if DOWNLEFT or DOWNRIGHT
				else {
					//hot fix to stay more on grid
					NewRow = OldRow - 1;
				}
			}

			//off the BIN LEFT
			if (NewCol < 2) { /* bin starts at 2 */

				//if move has taken cursor to rack already on this move
				if (Package->NewTable_Address.Board == RACK) {
					//then a newcol of 1 is okay
				}
				else {
					//reset, no change on col or row
					NewCol = OldCol;
					NewRow = OldRow;
				}
			}

			//off the BIN RIGHT
			if (NewCol > 25) {
				//reset, no change on col or row
				NewCol = OldCol;
				NewRow = OldRow;

				//@@@@ may need to change this here when bag is in game
			}
		}
		//STANDARD PUZZLE
		else {

			//off the BIN BOT
			if (NewRow > 12) {

				//if DOWN
				if (ProposedDirection == d_DOWN) {

					//if even col, move down left or downright instead of stalling
					if (NewCol % 2 == 0) {

						//move downright
						if (LeftRightValue >= 0.f) {
							//col moves right
							NewCol++;
							//row set at 12
							NewRow = 12;
						}
						//move downleft
						else {
							//col moves left
							NewCol--;
							//row set at 12
							NewRow = 12;
						}
					}
					else {
						//reset, no change on row
						NewRow = OldRow;
					}
				}
				//if DOWNLEFT or DOWNRIGHT
				else {
					//hot fix to stay more on grid
					NewRow = OldRow - 1;
				}
			}

			//off the BIN LEFT
			if (NewCol < 2) { /* bin starts at 2 */

				GetNewInfoBasedOnDynamicGridSize_BinToLeft(&NewCol, &NewRow, Package);
			}

			//off the BIN RIGHT
			if (NewCol > 15) {
				//reset, no change on col or row
				NewCol = OldCol;
				NewRow = OldRow;
			}
		}
	}

//SPECIAL FIXES

	//bin top right corner
	if (OldBoard == BIN) {
		//junction bin
		if (PuzzleLetter == pJUNCTION) {
			//last col
			if (OldCol == 25) {
				//top row
				if (OldRow == 2) {
					//if UP
					if (ProposedDirection == d_UP) {
						//move up left
						NewCol--;
						//row set at 1
						NewRow = 1;
					}

				}
			}
		}
		//standard bin
		else{
			//last col
			if (OldCol == 15) {
				//top row
				if (OldRow == 2) {
					//if UP
					if (ProposedDirection == d_UP) {
						//move up left
						NewCol--;
						//row set at 1
						NewRow = 1;
					}

				}
			}
		}
	}

	//standard bin bot left corner
	if (OldBoard == BIN) {
		//standard bin
		if (PuzzleLetter != pJUNCTION) {
			//first col
			if (OldCol == 2) {
				//bot corner row
				if (OldRow == 11) {
					//if DOWN
					if (ProposedDirection == d_DOWN) {
						//if leaned left
						if (LeftRightValue < 0.f) {

							//send to rack
							NewCol = 4;
							NewRow = 1;
							Package->NewTable_Address.Board = RACK;
						}
					}
				}
			}
		}
	}

	//grid corners
	if (OldBoard == GRID) {
		//first col
		if (OldCol == 1) {
			//first row
			if (OldRow == 2) {
				//if up
				if (ProposedDirection == d_UP) {
					NewCol = 2;
					NewRow = 1;
				}
			}
			//last row
			if (OldRow == PuzzleGridHeight * 2) {
				//if downleft
				if (ProposedDirection == d_DOWNLEFT) {

					//leans bot
					if (LeftRightValue > -0.8f) {
						//send to rack
						Package->NewTable_Address.Board = RACK;
						NewCol = 1;
						NewRow = 1;
					}
					else {
						//reset, no changeon col and row
						NewRow = OldRow;
						NewCol = OldCol;
					}
				}
			}
		}
		//last col
		if (OldCol == PuzzleGridWidth) {
			//first row, odd
			if (OldRow == 2) {
				//if up
				if (ProposedDirection == d_UP) {
					Package->NewTable_Address.Board = GRID;
					NewRow = 1;
					NewCol = OldCol - 1;
				}

			}
			//last row
			if (OldRow >= (PuzzleGridHeight * 2) - 1) {
				//if downright
				if (ProposedDirection == d_DOWNRIGHT) {
					Package->NewTable_Address.Board = BIN;
					NewCol = 2;
					NewRow = 9;
				}
			}
		}
	}

	//alter rackcolumn, if needed
	if (Package->NewTable_Address.Board == RACK) {
		NewCol = Hub->RackArbiter->AlterRackColumnIfNeededDueToPortraits(NewCol);
	}

	//no move was found
	if (NewCol == OldCol && NewRow == OldRow && OldBoard == Package->NewTable_Address.Board) {
		Hub->Animator->TableLightFlash();
	}

	/* NewCol, NewRow, and NewTable_Address.Board have been altered as needed and the cursor 
	knows where it is going. Now, we further set the information needed based on this new location,
	so we can send the LocationPackage back to the cursor */

	//change new address col and row
	Package->NewTable_Address.Col = NewCol;
	Package->NewTable_Address.Row = NewRow;

	//change colchange and rowchange
	Package->ColChange = NewCol - OldCol;
	Package->RowChange = NewRow - OldRow;

	//@@@@ This controls the scrolling.  This needs attention

	//if going to grid or rack
	if (Package->NewTable_Address.Board != BIN) {
		/*Hub->Animator->ScrollToElement_Left();*/
	}

	//if moving off screen
	if (Package->NewTable_Address.Col >= 8) {
		//Hub->Animator->ScrollToElement_Right();
	}
}

void UBoardArbiter::CalculateNewPositionOnBoard(int32* NewCol, int32* NewRow, TEnumAsByte<E_Direction> ProposedDirection)
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
}

void UBoardArbiter::GetNewInfoBasedOnDynamicGridSize_BinToLeft(int32* NewCol, int32* NewRow, FLocationPackage* Package)
{
	/* Need to change NewCol, NewRow, and the NewTable_Address.Board to either GRID or RACK  */

	int32 OldRow = Package->Table_Address.Row;

	//if less than 9, send to grid
	if (OldRow < 9) {
		Package->NewTable_Address.Board = GRID;
		*NewCol = Hub->PuzzleGridWidth;

		//if newcol is even, correction needed
		if (*NewCol % 2 == 0) {
			*NewRow = *NewRow - 1;
		}

		//constrain from top
		if (*NewRow < 1) {
			*NewRow = *NewRow + 2;
		}

		//constrain from bot
		if (*NewRow > Hub->PuzzleGridHeight * 2) {

			//if newcol is even
			if (*NewCol % 2 == 0) {
				*NewRow = (Hub->PuzzleGridHeight * 2) - 1;
			}
			//if newcol is odd
			if (*NewCol % 2 == 1) {
				*NewRow = Hub->PuzzleGridHeight * 2;
			}
		}

	}
	//if at 9
	if (OldRow == 9) {
		//if UPLEFT, send to grid
		if (Package->ProposedDirection == d_UPLEFT) {
			Package->NewTable_Address.Board = GRID;
			*NewCol = Hub->PuzzleGridWidth;

			//if newcol is even
			if (*NewCol % 2 == 0) {
				*NewRow = (Hub->PuzzleGridHeight * 2) - 1;
			}
			//if newcol is odd
			if (*NewCol % 2 == 1) {
				*NewRow = Hub->PuzzleGridHeight * 2;
			}
		}
		//if DOWNLEFT, send to rack
		if (Package->ProposedDirection == d_DOWNLEFT) {
			Package->NewTable_Address.Board = RACK;
			*NewCol = 4;
			*NewRow = 1;
		}
	}
	//if greater than 9, send to rack
	if (OldRow > 9) {
		Package->NewTable_Address.Board = RACK;
		*NewCol = 4;
		*NewRow = 1;
	}

}



void UBoardArbiter::PickClusterOffBoard(UCluster* Cluster)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Cluster->Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Cluster->Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;

	//loop pieces
	for (auto& Piece : Cluster->HeldPieces) {

		//condense
		int32 col = Piece->Table_Address.Col;
		int32 row = Piece->Table_Address.Row;
		int32 tri = Piece->Table_Address.Tri;

			//debug
			UE_LOG(AGridMovement, Warning, TEXT("Piece picked up: %i-%i,%i"),
			Piece->Table_Address.Col,
			Piece->Table_Address.Row,
			Piece->Table_Address.Tri)

		//get an iteration count for the amount of tris in shape
		int32 tricount = GetCountOfTris(Piece->Shape);

		//iterate tricount times
		for (int32 i = 1; i <= tricount; i++) {

			//condense
			FTriangleUnit& TargetTri = ColMap[col].RowMap[row].TriMap[tri];

				////debug
				//const TEnumAsByte<E_Segment> Seg = TargetTri.Segment;
				//FString SegString = UEnum::GetValueAsString(Seg.GetValue());
				//UE_LOG(AHomeCheck, Warning, TEXT("Segment picked up: %s"), *SegString)

			//take out of grid
			TargetTri.bIsFilled = false;
			TargetTri.bIsOrigin = false;
			TargetTri.PiecePtr = nullptr;
			TargetTri.Piece_ID = 0;
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

void UBoardArbiter::PlaceClusterOntoBoard(UCluster* Cluster)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Cluster->Table_Address.PuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TMap<int32, FColHex>& ColMap = (Cluster->Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;

	//loop pieces
	for (auto& Piece : Cluster->HeldPieces) {

		//condense
		int32 col = Piece->Table_Address.Col;
		int32 row = Piece->Table_Address.Row;
		int32 tri = Piece->Table_Address.Tri;

			//debug
			UE_LOG(AGridMovement, Warning, TEXT("Piece placed on board: %i-%i,%i"),
			Piece->Table_Address.Col,
			Piece->Table_Address.Row,
			Piece->Table_Address.Tri)

		//get an iteration count for the amount of tris in shape
		int32 tricount = GetCountOfTris(Piece->Shape);

		//iterate tricount times
		for (int32 i = 1; i <= tricount; i++) {

			//condense
			FTriangleUnit& TargetTri = ColMap[col].RowMap[row].TriMap[tri];

			//if first, make origin
			if (i == 1) {
				TargetTri.bIsOrigin = true;
			}

			//add to board
			TargetTri.bIsFilled = true;
			TargetTri.PiecePtr = Piece;
			TargetTri.Piece_ID = Piece->pID;
			TargetTri.Segment = GetSegment(i);

				////debug
				//const TEnumAsByte<E_Segment> Seg = TargetTri.Segment;
				//FString SegString = UEnum::GetValueAsString(Seg.GetValue());
				//UE_LOG(AHomeCheck, Warning, TEXT("Segment placed: %s"), *SegString)

			//iterate tri
			tri++;

			//reset tri if over 5
			if (tri == 7) {
				tri = 1;
			}
		}
	}
}

void UBoardArbiter::DropClusterWhereItWasPickedUp(UCluster* Cluster, FTable_Address PivotAddress)
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
	PlaceClusterOntoBoard(Cluster);

	//detach cluster from cursor
	Cluster->ActorClusterPtr->SceneComp->DetachFromComponent(FDetachmentTransformRules(
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld, true));

	//move actorpieces
	Hub->PieceArbiter->MoveClusterMeshToBoard(Cluster);
}

bool UBoardArbiter::DropClusterSomewhereInTheBinOfThisPuzzle(UCluster* Cluster, TEnumAsByte<E_PuzzleLetter> PuzzleLetter)
{
	/* This will find a spot for a piece that we are transferring to a new puzzle*/

	//store current cluster address
	FTable_Address OldAddress = Cluster->Table_Address;

	//condense
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//SPACED OUT CHECK

		/* This checks the bin for a completely free hex to place the piece*/

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

						UE_LOG(LogTemp, Warning, TEXT("SUCCESS in moving piece*** %i - %i"), Col.Key, Row.Key)

						PlaceClusterOntoBoard(Cluster);

						//can return since cluster was placed
						return true;
					}
				}
			}
		}

	//PRECISE CHECK

		/* This checks every tri at this original rotation for a fit. If that doesn't work, 
		it rotates once, and tries to find a fit. If rotating 5 times still doesn't work, 
		there's no place for it. */

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

							PlaceClusterOntoBoard(Cluster);

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
	/* Cluster can't find a home. */

	//set address back to original, it will have rotated back to its original tri
	int32 ColChange = OldAddress.Col - Cluster->Table_Address.Col;
	int32 RowChange = OldAddress.Row - Cluster->Table_Address.Row;
	Hub->PieceArbiter->SetNewTable_Address(Cluster, OldAddress.PuzzleLetter, OldAddress.Board, ColChange, RowChange);

	//action failed
	return false;
}

TArray<UCluster*> UBoardArbiter::DropAllTheseClustersNearThisAddress(TArray<UCluster*> InSack, FTable_Address Table_Address)
{
	//build struct
	struct FCoordinateChange{

		//constructor
		FCoordinateChange(const int32& _ColChange, const int32& _RowChange) 
			: ColChange(_ColChange), RowChange(_RowChange){}

		int32 ColChange;
		int32 RowChange;
	};

	//build tarray
	TArray<FCoordinateChange> ChangeArray;
		//1st go around
		ChangeArray.Add(FCoordinateChange(0, 0));
		//2nd go around
		ChangeArray.Add(FCoordinateChange(0, -2));
		ChangeArray.Add(FCoordinateChange(-1, -1));
		ChangeArray.Add(FCoordinateChange(-1, 1));
		ChangeArray.Add(FCoordinateChange(0, 2));
		ChangeArray.Add(FCoordinateChange(1, 1));
		ChangeArray.Add(FCoordinateChange(1, -1));
		//3rd go around
		ChangeArray.Add(FCoordinateChange(0, -4));
		ChangeArray.Add(FCoordinateChange(-1, -3));
		ChangeArray.Add(FCoordinateChange(-2, -2));
		ChangeArray.Add(FCoordinateChange(-2, 0));
		ChangeArray.Add(FCoordinateChange(-2, 2));
		ChangeArray.Add(FCoordinateChange(-1, 3));
		ChangeArray.Add(FCoordinateChange(0, 4));
		ChangeArray.Add(FCoordinateChange(1, 3));
		ChangeArray.Add(FCoordinateChange(2, 2));
		ChangeArray.Add(FCoordinateChange(2, 0));
		ChangeArray.Add(FCoordinateChange(2, -2));
		ChangeArray.Add(FCoordinateChange(1, -3));
		//4th go around
		ChangeArray.Add(FCoordinateChange(0, -6));
		ChangeArray.Add(FCoordinateChange(-1, -5));
		ChangeArray.Add(FCoordinateChange(-2, -4));
		ChangeArray.Add(FCoordinateChange(-3, -3));
		ChangeArray.Add(FCoordinateChange(-3, -1));
		ChangeArray.Add(FCoordinateChange(-3, 1));
		ChangeArray.Add(FCoordinateChange(-3, 3));
		ChangeArray.Add(FCoordinateChange(-2, 4));
		ChangeArray.Add(FCoordinateChange(-1, 5));
		ChangeArray.Add(FCoordinateChange(0, 6));
		ChangeArray.Add(FCoordinateChange(1, 5));
		ChangeArray.Add(FCoordinateChange(2, 4));
		ChangeArray.Add(FCoordinateChange(3, 3));
		ChangeArray.Add(FCoordinateChange(3, 1));
		ChangeArray.Add(FCoordinateChange(3, -1));
		ChangeArray.Add(FCoordinateChange(3, -3));
		ChangeArray.Add(FCoordinateChange(2, -4));
		ChangeArray.Add(FCoordinateChange(1, -5));
		//5th go around
		ChangeArray.Add(FCoordinateChange(0, -8));
		ChangeArray.Add(FCoordinateChange(-1, -7));
		ChangeArray.Add(FCoordinateChange(-2, -6));
		ChangeArray.Add(FCoordinateChange(-3, -5));
		ChangeArray.Add(FCoordinateChange(-4, -4));
		ChangeArray.Add(FCoordinateChange(-4, -2));
		ChangeArray.Add(FCoordinateChange(-4, 0));
		ChangeArray.Add(FCoordinateChange(-4, 2));
		ChangeArray.Add(FCoordinateChange(-4, 4));
		ChangeArray.Add(FCoordinateChange(-3, 5));
		ChangeArray.Add(FCoordinateChange(-2, 6));
		ChangeArray.Add(FCoordinateChange(-1, 7));
		ChangeArray.Add(FCoordinateChange(0, 8));
		ChangeArray.Add(FCoordinateChange(1, 7));
		ChangeArray.Add(FCoordinateChange(2, 6));
		ChangeArray.Add(FCoordinateChange(3, 5));
		ChangeArray.Add(FCoordinateChange(4, 4));
		ChangeArray.Add(FCoordinateChange(4, 2));
		ChangeArray.Add(FCoordinateChange(4, 0));
		ChangeArray.Add(FCoordinateChange(4, -2));
		ChangeArray.Add(FCoordinateChange(4, -4));
		ChangeArray.Add(FCoordinateChange(3, -5));
		ChangeArray.Add(FCoordinateChange(2, -6));
		ChangeArray.Add(FCoordinateChange(1, -7));

//lazy placement

	//initialize timedelay elements
	float TimeToDelay = 0.f;
	const float TimeBetween = 0.1f;

	//copy tarray
	TArray<UCluster*> ClustersToPlace = InSack;

	//loop change array
	for (auto& Coords : ChangeArray) {
		
		//exit when finished with Clusters
		if (ClustersToPlace.Num() == 0) {
			break;
		}

		//initialize trigger to remove piece
		bool bClusterPlaced = false;

		//get first cluster
		UCluster* Cluster = ClustersToPlace[0];

		//get col and row from ChangeArray
		int32 col = Table_Address.Col + Coords.ColChange;
		int32 row = Table_Address.Row + Coords.RowChange;

		//condense
		TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Table_Address.PuzzleLetter;
		FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
		TMap<int32, FColHex>& ColMap = (Table_Address.Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;

		//safety check
		if (ColMap.Contains(col)) {
			if (ColMap[col].RowMap.Contains(row)) {

				//condense
				FRowHex& Hex = ColMap[col].RowMap[row];

				//loop up to 5 times, for rotation through tri
				for (int32 i = 0; i <= 4; i++) {
					//initialize tri
					int32 tri = i + Table_Address.Tri;

					//correct tri, if needed
					if (tri > 6) {
						tri -= 6;
					}

					//change cluster and pieces to possible new address
					int32 ColChange = col - Cluster->Table_Address.Col;
					int32 RowChange = row - Cluster->Table_Address.Row;
					Hub->PieceArbiter->SetNewTable_Address(Cluster, PuzzleLetter, Table_Address.Board, ColChange, RowChange);

					if (IsPlacementPossible(Cluster)) {

						//place info onto board
						PlaceClusterOntoBoard(Cluster);

						//spawn actorpieces
						Hub->MeshPieceMaker->SpawnTransferSackDroppedCluster(Cluster, TimeToDelay);

						//iterate TimeToDelay
						TimeToDelay += TimeBetween;

						//remove from copied sack
						ClustersToPlace.Remove(Cluster);

						//exit hex rotations
						break;
					}
				}
			}
			else {
				continue;
			}
		}
		else {
			continue;
		}

		//if no more clusters
		if (ClustersToPlace.Num() == 0) {
			//break out of coordination change array
			break;
		}
	}

/* There's still a possibility that all clusters won't be replaced.  This function then returns 
the cluster array that may not be empty */

	return ClustersToPlace;
}


// JOIN PIECES

void UBoardArbiter::HandleJoiningPieces(UCluster* Cluster)
{
	UE_LOG(AHomeCheck, Error, TEXT("+++++CLUSTER DROPPED+++++"))

	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];
	TEnumAsByte<E_Board> Board = Cluster->Table_Address.Board;

	//make array here because heldpieces will change during iteration
	TArray<UPiece*> PiecesToCheck;

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

				UPiece* MatchingHomePiece = DetermineIfThereIsAHomePieceMatch(col, row, TriToCheck, Join.Value, Board);

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

				UPiece* MatchingHomePiece = DetermineIfThereIsAHomePieceMatch(col, row, TriToCheck, Join.Value, Board);

				if (MatchingHomePiece) {
					Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
				}
			}

			/* The direction to check changes based off the current tri(rotation) of the piece. This
			can probably be cut down, but I'm reluctant to mess with such a crucial system */

			// if jTRI1
			if (Join.Key == jTRI1) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI1 check"))

				if (tri == 1) {
					UPiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					UPiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					UPiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					UPiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					UPiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					UPiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI2
			if (Join.Key == jTRI2) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI2 check"))

				//offset tri due to furthering of segments
				int32 tri_offset = 1;

				if (tri == 1) {
					UPiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					UPiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					UPiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					UPiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					UPiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					UPiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI3
			if (Join.Key == jTRI3) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI3 check"))

				//offset tri due to furthering of segments
				int32 tri_offset = 2;

				if (tri == 1) {
					UPiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					UPiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					UPiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					UPiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					UPiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					UPiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI4
			if (Join.Key == jTRI4) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI4 check"))

				//offset tri due to furthering of segments
				int32 tri_offset = 3;

				if (tri == 1) {
					UPiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					UPiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					UPiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					UPiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					UPiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					UPiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI5
			if (Join.Key == jTRI5) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI5 check"))

				//offset tri due to furthering of segments
				int32 tri_offset = 4;

				if (tri == 1) {
					UPiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					UPiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					UPiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					UPiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					UPiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					UPiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			// if jTRI6
			if (Join.Key == jTRI6) {

				UE_LOG(AHomeCheck, Display, TEXT("jTRI6 check"))

				//offset tri due to furthering of segments
				int32 tri_offset = 5;

				if (tri == 1) {
					UPiece* MatchingHomePiece = CheckInDirection_DownLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 2) {
					UPiece* MatchingHomePiece = CheckInDirection_Down(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 3) {
					UPiece* MatchingHomePiece = CheckInDirection_DownRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 4) {
					UPiece* MatchingHomePiece = CheckInDirection_UpRight(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 5) {
					UPiece* MatchingHomePiece = CheckInDirection_Up(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}

				if (tri == 6) {
					UPiece* MatchingHomePiece = CheckInDirection_UpLeft(col, row, tri + tri_offset, Join.Value, Board);

					if (MatchingHomePiece) {
						Hub->PieceArbiter->HandleJoiningPiecesAndClusters(MatchingHomePiece, Cluster, Join.Value, Piece);
					}
				}
			}

			UE_LOG(AHomeCheck, Error, TEXT("---------------"))
		}

	}
}

UPiece* UBoardArbiter::CheckInDirection_Up(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
{
	int32 NewCol = col;
	int32 NewRow = row - 2;
	int32 NewTri = tri + 3; /* opposite tri */

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit, Board);
}

UPiece* UBoardArbiter::CheckInDirection_UpLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
{
	int32 NewCol = col - 1;
	int32 NewRow = row - 1;
	int32 NewTri = tri + 3; /* opposite tri */

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit, Board);
}

UPiece* UBoardArbiter::CheckInDirection_UpRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
{
	int32 NewCol = col + 1;
	int32 NewRow = row - 1;
	int32 NewTri = tri + 3; /* opposite tri */

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit, Board);
}

UPiece* UBoardArbiter::CheckInDirection_Down(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
{
	int32 NewCol = col;
	int32 NewRow = row + 2;
	int32 NewTri = tri + 3; /* opposite tri */

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit, Board);
}

UPiece* UBoardArbiter::CheckInDirection_DownLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
{
	int32 NewCol = col - 1;
	int32 NewRow = row + 1;
	int32 NewTri = tri + 3; /* opposite tri */

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit, Board);
}

UPiece* UBoardArbiter::CheckInDirection_DownRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
{
	int32 NewCol = col + 1;
	int32 NewRow = row + 1;
	int32 NewTri = tri + 3; /* opposite tri */

	return DetermineIfThereIsAHomePieceMatch(NewCol, NewRow, NewTri, JoinUnit, Board);
}

UPiece* UBoardArbiter::DetermineIfThereIsAHomePieceMatch(int32 NewCol, int32 NewRow, int32 NewTri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board)
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
	TMap<int32, FColHex>& ColMap = (Board == BIN) ? Puzzle.ColMapBin : Puzzle.ColMapGrid;

		UE_LOG(LogTemp, Warning, TEXT("Col: %i"), NewCol)
		UE_LOG(LogTemp, Warning, TEXT("Row: %i"), NewRow)
		UE_LOG(LogTemp, Warning, TEXT("Tri: %i"), NewTri)

	//safety check, returns nullptr if trying to check off the board
	if (ColMap.Contains(NewCol)) {
		if (ColMap[NewCol].RowMap.Contains(NewRow)) {
		}
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}

	//find TriUnit in question
	FTriangleUnit& TriUnit = ColMap[NewCol].RowMap[NewRow].TriMap[NewTri];

	//if filled
	if (TriUnit.PiecePtr) {

		UE_LOG(AHomeCheck, Display, TEXT("Piece Found"))

			//if also a piece match
			if (TriUnit.PiecePtr->pID == JoinUnit.Piece_ID) {

				UE_LOG(AHomeCheck, Display, TEXT("Piece Match"))

					//if also a segment match
					if (TriUnit.Segment == JoinUnit.Segment) {

						UE_LOG(AHomeCheckSuccess, Warning, TEXT("JOIN!!!!!!!!!!!!!!!"))
							
							//success
							return TriUnit.PiecePtr;
					}
					else {
						UE_LOG(AHomeCheck, Display, TEXT("Segment  NO  Match"))
					}

				//debug
				const TEnumAsByte<E_Segment> LookSeg = JoinUnit.Segment;
				FString LookSegString = UEnum::GetValueAsString(LookSeg.GetValue());
				UE_LOG(AHomeCheck, Display, TEXT("Looking for : %s"), *LookSegString)

				const TEnumAsByte<E_Segment> FindSeg = TriUnit.Segment;
				FString FindSegString = UEnum::GetValueAsString(FindSeg.GetValue());
				UE_LOG(AHomeCheck, Display, TEXT("Finding : %s"), *FindSegString)

				UE_LOG(AHomeCheck, Display, TEXT("Other Piece Tri Where Im Looking: %i"), NewTri)
				UE_LOG(AHomeCheck, Display, TEXT("Other Piece Actual Tri: %i"), TriUnit.PiecePtr->Table_Address.Tri)
			}
			else {
				UE_LOG(AHomeCheck, Display, TEXT("Piece  NO  Match"))
			}
	}
	else {
		UE_LOG(AHomeCheck, Display, TEXT("--Spot Not Filled"))
	}

	UE_LOG(AHomeCheck, Display, TEXT("---"))

		//no match found
		return nullptr;
}


