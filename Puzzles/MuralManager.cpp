// Copyright 2020 Vacuda


#include "MuralManager.h"
#include "UObject/ConstructorHelpers.h"						// for Helpers
#include "Kismet/GameplayStatics.h"							// for GameplayStatics

#include "Talismans/NewWorldBuild/NewWorldBuild.h"			// for Builder
#include "Talismans/Admin/TheGameInstance.h"				// for GameInstance


UMuralManager::UMuralManager()
{
	FindAllMuralTextures_7x3();
}


//SETUP

void UMuralManager::FindAllMuralTextures_7x3()
{
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_001.mural_001'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_002.mural_002'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_003.mural_003'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_004.mural_004'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_005.mural_005'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_006.mural_006'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_007.mural_007'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_008.mural_008'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_009.mural_009'"));

	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_010.mural_010'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_011.mural_011'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_012.mural_012'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_013.mural_013'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_014.mural_014'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_015.mural_015'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_016.mural_016'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_017.mural_017'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_018.mural_018'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_019.mural_019'"));

	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_020.mural_020'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_021.mural_021'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_022.mural_022'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_023.mural_023'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_024.mural_024'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_025.mural_025'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_026.mural_026'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_027.mural_027'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_028.mural_028'"));
	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_029.mural_029'"));

	TextureArray_7x3.Emplace(FindAsset("Texture'/Game/Murals/mural_030.mural_030'"));
}

UTexture* UMuralManager::FindAsset(FString Name)
{
	ConstructorHelpers::FObjectFinder<UTexture> Asset((TEXT("%s"), *Name));
	return Asset.Object;
}


//GATHER INFO

TArray<TSoftObjectPtr<UTexture>>& UMuralManager::ReturnProperArrayToUse(TEnumAsByte<E_GridSize> GridSize)
{
	if (GridSize == sz_7x3){
		return TextureArray_7x3;
	}
	else {
		return TextureArray_7x3;
	}
}

UTexture* UMuralManager::GetProperTexture(TEnumAsByte<E_GridSize> GridSize, bool bUseDebugTexture)
{
	//pick array
	auto& TextureArray = ReturnProperArrayToUse(GridSize);

	//use debug texture
	if (bUseDebugTexture == true) {

		int32 RandBool = FMath::RandRange(0, 1);

		if (RandBool == 0) {
			return TextureArray[1].Get();
		}
		else {
			return TextureArray[19].Get();
		}
	}
	//get and remove a mural
	else {
		//get a Random Index
		int32 RandIndex = FMath::RandRange(0, TextureArray.Num() - 1);

		//find mural, dereference
		UTexture* RemovedMural = TextureArray[RandIndex].Get();

		//remove Mural from Array
		TextureArray.RemoveAt(RandIndex);

		return RemovedMural;
	}
}