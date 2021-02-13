// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Enums/E_PieceShape.h"					// for E_PieceShape
#include "Talismans/Enums/E_Direction.h"					// for E_Direction
#include "Talismans/Enums/E_Segment.h"						// for E_Segment
#include "Talismans/Enums/E_PuzzleLetter.h"					// for E_PuzzleLetter
#include "BinArbiter.generated.h"

struct FLocationPackage;
struct FTable_Address;
struct FJoinUnit;
class UHub;
class ACluster;
class APiece;

UCLASS()
class TALISMANS_API UBinArbiter : public UObject
{
	GENERATED_BODY()

public:

// SETUP

	void CatchTheHub(UHub* _Hub);


// GATHER INFO

	void FindAllMovableClusters(FTable_Address Table_Address, TArray<ACluster*>* AllMovableClusters);
	int32 GetCountOfTris(TEnumAsByte <E_PieceShape> Shape);
	bool IsPlacementPossible(ACluster* Cluster);
	ACluster* FindPossibleClusterToSelect(FTable_Address Table_Address, int32 TriPick);
	TEnumAsByte <E_Segment> GetSegment(int32 SegmentCount);

// DEBUG

	int32 GetNum();


// MAKE CHANGES

	void ChangeLocationPackageToGetMovementDestination(FLocationPackage* Package);
	void CalculateNewPositionOnBin(int32* NewCol, int32* NewRow, TEnumAsByte<E_Direction> ProposedDirection);


// MOVE PIECE

	void PickClusterOffBin(ACluster* Cluster);
	void PlaceClusterIntoBin(ACluster* Cluster);
	void DropClusterWhereItWasPickedUp(ACluster* Cluster, FTable_Address PivotAddress);
	bool DropClusterSomewhereInTheBinOfThisPuzzle(ACluster* Cluster, TEnumAsByte<E_PuzzleLetter> PuzzleLetter);


// JOIN PIECES

	void HandleJoiningPieces(ACluster* Cluster);
	APiece* CheckInDirection_Up(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit);
	APiece* CheckInDirection_UpLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit);
	APiece* CheckInDirection_UpRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit);
	APiece* CheckInDirection_Down(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit);
	APiece* CheckInDirection_DownLeft(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit);
	APiece* CheckInDirection_DownRight(int32 col, int32 row, int32 tri, FJoinUnit JoinUnit);
	APiece* DetermineIfThereIsAHomePieceMatch(int32 NewCol, int32 NewRow, int32 NewTri, FJoinUnit JoinUnit);




// MEMBERS - SETUP

	UPROPERTY()
		UHub* Hub;

};
