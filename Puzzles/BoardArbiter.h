// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Enums/E_PieceShape.h"						// for PieceShape
#include "Talismans/Enums/E_Direction.h"						// for Direction
#include "Talismans/Enums/E_Segment.h"							// for Segment
#include "Talismans/Enums/E_PuzzleLetter.h"						// for E_PuzzleLetter
#include "Talismans/Enums/E_Board.h"							// for E_Board
#include "BoardArbiter.generated.h"

struct FLocationPackage;
struct FTable_Address;
struct FJoinUnit;
class UCluster;
class UPiece;
class UHub;

UCLASS()
class TALISMANS_API UBoardArbiter : public UObject
{
	GENERATED_BODY()

public:

	UBoardArbiter();


//SETUP

	void CatchTheHub(UHub* _Hub);

//GATHER INFO

	FVector GetLocationFromTable_Address(FTable_Address Table_Address);
	void FindAllMovableClusters(FTable_Address Table_Address, TArray<UCluster*>* AllMovableClusters);
	int32 GetCountOfTris(TEnumAsByte <E_PieceShape> Shape);
	bool IsPlacementPossible(UCluster* Cluster);
	UCluster* FindPossibleClusterToSelect(FTable_Address Table_Address, int32 TriPick);
	TEnumAsByte <E_Segment> GetSegment(int32 SegmentCount);
	UPiece* GetItemPieceOnTheBoardHere(FTable_Address Table_Address);
	UCluster* FindClusterInThisDirectionFromThisAddress(TEnumAsByte<E_Direction> Direction, FTable_Address Table_Address);

	
//CHANGE INFO

	void ChangeLocationPackageToGetMovementDestination(FLocationPackage* Package);
	void CalculateNewPositionOnBoard(int32* NewCol, int32* NewRow, TEnumAsByte<E_Direction> ProposedDirection);
	void GetNewInfoBasedOnDynamicGridSize_BinToLeft(int32* NewCol, int32* NewRow, FLocationPackage* Package);
	void PickClusterOffBoard(UCluster* Cluster);
	void PlaceClusterOntoBoard(UCluster* Cluster);
	void DropClusterWhereItWasPickedUp(UCluster* Cluster, FTable_Address PivotAddress);
	bool DropClusterSomewhereInTheBinOfThisPuzzle(UCluster* Cluster, TEnumAsByte<E_PuzzleLetter> PuzzleLetter);
	TArray<UCluster*> DropAllTheseClustersNearThisAddress(TArray<UCluster*> InSack, FTable_Address Table_Address);


//JOIN PIECES

	void HandleJoiningPieces(UCluster* Cluster);
	UPiece* CheckInDirection_Up(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);
	UPiece* CheckInDirection_UpLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);
	UPiece* CheckInDirection_UpRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);
	UPiece* CheckInDirection_Down(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);
	UPiece* CheckInDirection_DownLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);
	UPiece* CheckInDirection_DownRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);
	UPiece* DetermineIfThereIsAHomePieceMatch(int32 NewCol, int32 NewRow, int32 NewTri, FJoinUnit JoinUnit, TEnumAsByte<E_Board> Board);


// MEMBERS - SETUP

	UPROPERTY()
		UHub* Hub;
};
