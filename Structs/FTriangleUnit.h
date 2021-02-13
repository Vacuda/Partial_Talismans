// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "Talismans/Structs/FTable_Address.h"			// for FTable_Address
#include "Talismans/Enums/E_Segment.h"					// for E_Segment
#include "Talismans/Pieces/Piece.h"						// for APiece
#include "Engine/DataTable.h"
#include "FTriangleUnit.generated.h"



USTRUCT()
struct FTriangleUnit
{
	GENERATED_BODY()

	UPROPERTY()
		FTable_Address Table_Address;

	UPROPERTY()
		bool bIsFilled = false;

	UPROPERTY()
		bool bIsOrigin = false;

	UPROPERTY()
		bool bIsCemented = false;

	UPROPERTY()
		APiece* PiecePtr = nullptr;

	UPROPERTY()
		TEnumAsByte <E_Segment> Segment = SEGNONE;




	
};