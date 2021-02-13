// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Enums/E_GridSize.h"							// for E_GridSize
#include "MuralManager.generated.h"

class UTheGameInstance;
class UNewWorldBuild;


UCLASS()
class TALISMANS_API UMuralManager : public UObject
{
	GENERATED_BODY()

public:

	UMuralManager();

//SETUP

	void FindAllMuralTextures_7x3();
	UTexture* FindAsset(FString Name);


//GATHER INFO
	UTexture* GetProperTexture(TEnumAsByte<E_GridSize> GridSize, bool bUseDebugTexture);
	TArray<TSoftObjectPtr<UTexture>>& ReturnProperArrayToUse(TEnumAsByte<E_GridSize> GridSize);

//MEMBERS



	UPROPERTY()
		TArray<TSoftObjectPtr<UTexture>> TextureArray_7x3;		





















};

