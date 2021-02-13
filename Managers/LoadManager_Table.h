// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Structs/FTable_Address.h"							// for FTable_Address
#include "LoadManager_Table.generated.h"


class APuzzleLevel;
class UHub;

UCLASS()
class TALISMANS_API ULoadManager_Table : public UObject
{
	GENERATED_BODY()
	
public:

	void RunLoadManager();
	void CreateHub();



	void MakeNewObjects();

	void FindTheGameInstance();
	void FindThePlayerController();
	void FindThePuzzleLevel();
	void FindThePawnCursor();
	void FindTheBinMesh();
	void FindTheGridMesh();
	void FindTheTableLightMaterial();
	void FindThePuzzleGridHeightAndWidth();
	void FindTheStartingTable_Address();

	void SendTheHubToEveryone();

	UPROPERTY()
		UHub* Hub;
	UPROPERTY()
		APuzzleLevel* PuzzleLevel;

};
