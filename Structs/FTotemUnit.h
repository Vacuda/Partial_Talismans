// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "Talismans/Enums/E_TotemType.h"				// for TotemType
#include "Talismans/Enums/E_PuzzleLetter.h"				// for PuzzleLetter
#include "Talismans/Enums/E_VesselType.h"				// for VesselType
#include "Talismans/Structs/FRoom_Address.h"			// for Room_Address
#include "FTotemUnit.generated.h"


class UPiece;


USTRUCT()
struct FTotemUnit
{
	GENERATED_BODY()

	UPROPERTY()
		TEnumAsByte <E_TotemType> TotemType = tVACANT;

	UPROPERTY()
		FRoom_Address Room_Address;

	UPROPERTY()
		TEnumAsByte <E_PuzzleLetter> PuzzleLetter;

	UPROPERTY()
		bool bIsOrigin = false;

	UPROPERTY()
		TEnumAsByte <E_VesselType> VesselType = v_NONE;

	UPROPERTY()
		TArray<int32> Vessel_Piece_IDArray;

};
