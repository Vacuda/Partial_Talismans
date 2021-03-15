// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Enums/E_PieceShape.h"						// for PieceShape
#include "Talismans/Enums/E_Segment.h"                          // for Segment
#include "PieceMaker.generated.h"

class UTheGameInstance;
struct FTable_Address;
class UPiece;
struct FJoinUnit;


UCLASS()
class TALISMANS_API UPieceMaker : public UObject
{
	GENERATED_BODY()

public:

	UPieceMaker();

//SETUP

	void CatchTheGameInstance(UTheGameInstance* _GameInstance);


//GATHER INFO

	int32 GetCountOfTris(TEnumAsByte <E_PieceShape> Shape);
	int32 GetRandIntBasedOnHexCapacity(int32 HexCapacity);
	TEnumAsByte <E_PieceShape> GetShape(int32 ShapeNum);
	TEnumAsByte <E_Segment> GetSegment(int32 SegmentCount);


// FIND JOIN UNITS
	FJoinUnit FindJoinUnit_Low(int32 TriStart, TArray<UPiece*> HexArray);
	FJoinUnit FindJoinUnit_High(int32 TriStart, TArray<UPiece*> HexArray);


//CHANGE INFO

	void PiecesWillStartInBin();
	void RandomizeBinPlacement();
	void PiecesWillStartInGrid();
	void PiecesWillStartInVessels();
	void PlacePiecesIntoRespectiveContainers();


//BUILD

	//void BuildFullSetHexPieces();
	void BuildFullAndRandomlyCutPieces();
	void CreateClusters();
	void FillJoinMaps();


//MEMBERS

	UPROPERTY()
		UTheGameInstance* GameInstance;



















};
