// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "Talismans/Enums/E_PuzzleLetter.h"						// for PuzzleLetter
#include "Talismans/Enums/E_GridSize.h"							// for E_GridSize
#include "Talismans/Structs/FRoom_Address.h"					// for Room_Address
#include "Talismans/Structs/FTable_Address.h"					// for Table_Address
#include "Talismans/Structs/FColHex.h"							// for ColHex
#include "FPuzzleUnit.generated.h"

USTRUCT(BlueprintType)
struct FPuzzleUnit : public FTableRowBase
{
	GENERATED_BODY()





	UPROPERTY()
		TEnumAsByte <E_PuzzleLetter> PuzzleLetter;

	UPROPERTY()
		TEnumAsByte <E_RoomLetter> RoomLetter;

	UPROPERTY()
		TMap<int32, FColHex> ColMapGrid;

	UPROPERTY()
		TMap<int32, FColHex> ColMapBin;

	UPROPERTY()
		int32 PuzzleGridHeight;

	UPROPERTY()
		int32 PuzzleGridWidth;

	UPROPERTY()
		TArray<APiece*> HomePiecesArray;

	UPROPERTY()
		TEnumAsByte<E_GridSize> GridSize;
	
	UPROPERTY()
		bool bIsBordered;

	UPROPERTY()
		UStaticMesh* GridStaticMesh;

	UPROPERTY()
		UTexture* MuralTexture;

	UPROPERTY()
		FRoom_Address Room_Address;

	UPROPERTY()
		FTable_Address ExitTable_Address;

	UPROPERTY()
		bool bIsPlaced = false;

	UPROPERTY()
		bool bIsComplete = false;

	

	UPROPERTY()
		bool bIsDiscovered = false;












};
