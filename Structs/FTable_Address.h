// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "Talismans/Enums/E_Board.h"							// for E_Board
#include "Talismans/Enums/E_PuzzleLetter.h"					// for PuzzleLetter
#include "FTable_Address.generated.h"

USTRUCT()
struct FTable_Address
{
	GENERATED_BODY()


	UPROPERTY()
		TEnumAsByte <E_PuzzleLetter> PuzzleLetter;

	UPROPERTY()
		TEnumAsByte <E_Board> Board = NONE;

	UPROPERTY()
		int32 Col = 0;

	UPROPERTY()
		int32 Row = 0;

	UPROPERTY()
		int32 Tri = 0;

	UPROPERTY()
		FName SocketCode = ReturnTheSocketCode();

	UPROPERTY()
		FRotator Rotation = ReturnTheRotation();


 
	FRotator ReturnTheRotation();
	FName ReturnTheSocketCode();




};