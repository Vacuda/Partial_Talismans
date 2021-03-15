// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Enums/E_TempleSize.h"				// for TempleSize
#include "Talismans/Enums/E_RoomLetter.h"				// for RoomLetter
#include "Talismans/Enums/E_PuzzleLetter.h"				// for PuzzleLetter
#include "Talismans/Enums/E_GridSize.h"					// for GridSize
#include "Talismans/Enums/E_VesselType.h"				// for VesselType
#include "Talismans/Enums/E_DoorDirection.h"			// for DoorDirection
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
	void FindAllGridStaticMeshes();
	UStaticMesh* FindAsset(FString Name);
	void Setup(UTheGameInstance* _GameInstance);

//FUNCTIONALITY


	void BuildANewWorld(UTheGameInstance* _GameInstance);

	void Build_Rooms();
	void Build_TotemPoles();
	void Build_DoorInformation();
	void PlaceDoorAtThisPosition(TEnumAsByte<E_RoomLetter> RoomLetter, TEnumAsByte<E_DoorDirection> DoorDirection);

	void Build_Puzzles();
	void Set_PuzzleGridHeightAndWidths();
	void Set_GridStaticMeshes();
	void Set_MuralTextures();
	void Set_BordersOnMurals();

	void Build_PuzzleGridMaps();
	void Build_PuzzleBinMaps();

	void CreateRoomLetterArrayForRandomRoomLetters();
	void Place_PuzzlesIntoRooms();

	void Populate_FloorTotems();
	void Populate_FinaleTotems();
	void Populate_DoorTotems();
	void Populate_VesselTotems();
	TEnumAsByte<E_VesselType> GetRandomVessel();

	bool bIsTablePlacementPossible(
		TEnumAsByte <E_RoomLetter> RoomLetter, int32 Col, int32 Row);
	TEnumAsByte <E_RoomLetter> GetRandomRoomLetter();

//MEMBERS

	UPROPERTY()
		TEnumAsByte <E_TempleSize> TempleSize;
	UPROPERTY()
		UTheGameInstance* GameInstance;
	UPROPERTY()
		TMap<int32, TEnumAsByte<E_PuzzleLetter>> PuzzleLetterLookupMap;
	UPROPERTY()
		TArray<TEnumAsByte<E_RoomLetter>> RoomLetterArray;
	UPROPERTY()
		TArray<TEnumAsByte <E_GridSize>> PuzzleSizeArray;
	UPROPERTY()
		TMap<TEnumAsByte<E_GridSize>, TSoftObjectPtr<UStaticMesh>> GridsMap;

		









	
};
