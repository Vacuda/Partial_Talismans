// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Enums/E_TempleSize.h"				// for TempleSize
#include "Talismans/Enums/E_RoomLetter.h"				// for RoomLetter
#include "Talismans/Enums/E_PuzzleLetter.h"				// for PuzzleLetter
#include "Talismans/Enums/E_GridSize.h"					// for GridSize
#include "Talismans/Enums/E_VesselType.h"				// for VesselType
#include "NewWorldBuild.generated.h"

class UTheGameInstance;

UCLASS()
class TALISMANS_API UNewWorldBuild : public UObject
{
	GENERATED_BODY()

public:

	UNewWorldBuild();

//SETUP
	void CreatePuzzleLetterLookupMap();
	void FindAllStaticMeshes();
	void Setup(UTheGameInstance* _GameInstance);

//FUNCTIONALITY


	void BuildANewWorld(UTheGameInstance* _GameInstance);

	void Build_Rooms();
	void Build_TotemPoles();

	void Build_Puzzles();
	void Set_PuzzleGridHeightAndWidths();
	void Set_GridStaticMeshes();
	void Set_MuralTextures();
	void Set_BordersOnMurals();

	void Build_PuzzleGridMaps();
	void Build_PuzzleBinMaps();

	void CreateRoomLetterArrayForRandomRoomLetters();
	void Place_PuzzlesIntoRooms();

	void Populate_RoomsWithFloors();
	void Populate_RoomsWithFinale();
	void Populate_RoomsWithVessels();
	TEnumAsByte<E_VesselType> GetRandomVessel();

	bool bIsTablePlacementPossible(
		TEnumAsByte <E_RoomLetter> RoomLetter, int32 Col, int32 Row);
	TEnumAsByte <E_RoomLetter> GetRandomRoomLetter();

//MEMBERS

	UPROPERTY()
		TEnumAsByte <E_TempleSize> TempleSize;
	UPROPERTY()
		int32 AmountOfPieces;
	UPROPERTY()
		int32 AmountOfTables;
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY()
		TMap<int32, TEnumAsByte<E_PuzzleLetter>> PuzzleLetterLookupMap;
	UPROPERTY()
		TArray<TEnumAsByte<E_RoomLetter>> RoomLetterArray;
	UPROPERTY()
		TArray<TEnumAsByte <E_GridSize>> PuzzleSizeArray;

//MEMBERS - STATICMESHES

	UPROPERTY()
		UStaticMesh* SM_Grid_7x3;
		









	
};
