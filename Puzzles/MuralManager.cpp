// Copyright 2020 Vacuda


#include "MuralManager.h"
#include "UObject/ConstructorHelpers.h"						// for Helpers
#include "Kismet/GameplayStatics.h"							// for GameplayStatics

#include "Talismans/NewWorldBuild/NewWorldBuild.h"			// for Builder
#include "Talismans/Admin/TheGameInstance.h"				// for GameInstance


UMuralManager::UMuralManager()
{
	FindAllMuralTextures_7x2();
	FindAllMuralTextures_7x3();
	FindAllMuralTextures_7x4();

	FindAllMuralTextures_6x2();
	FindAllMuralTextures_6x3();
	FindAllMuralTextures_6x4();

	FindAllMuralTextures_5x2();
	FindAllMuralTextures_5x3();
	FindAllMuralTextures_5x4();

	FindAllMuralTextures_4x2();
	FindAllMuralTextures_4x3();
	FindAllMuralTextures_4x4();

	FindAllMuralTextures_3x2();
	FindAllMuralTextures_3x3();
	FindAllMuralTextures_3x4();

	FindAllMuralTextures_2x2();
	FindAllMuralTextures_2x3();
	FindAllMuralTextures_2x4();

	FindAllBorderTexturesAndMasks();

}




//GATHER INFO

TArray<FString>& UMuralManager::ReturnProperArrayToUse(TEnumAsByte<E_GridSize> GridSize)
{
	if (GridSize == sz_7x4){
		return Texture_IDArray_7x4;
	}
	if (GridSize == sz_7x3) {
		return Texture_IDArray_7x3;
	}
	if (GridSize == sz_7x2) {
		return Texture_IDArray_7x2;
	}

	if (GridSize == sz_6x4) {
		return Texture_IDArray_6x4;
	}
	if (GridSize == sz_6x3) {
		return Texture_IDArray_6x3;
	}
	if (GridSize == sz_6x2) {
		return Texture_IDArray_6x2;
	}

	if (GridSize == sz_5x4) {
		return Texture_IDArray_5x4;
	}
	if (GridSize == sz_5x3) {
		return Texture_IDArray_5x3;
	}
	if (GridSize == sz_5x2) {
		return Texture_IDArray_5x2;
	}

	if (GridSize == sz_4x4) {
		return Texture_IDArray_4x4;
	}
	if (GridSize == sz_4x3) {
		return Texture_IDArray_4x3;
	}
	if (GridSize == sz_4x2) {
		return Texture_IDArray_4x2;
	}

	if (GridSize == sz_3x4) {
		return Texture_IDArray_3x4;
	}
	if (GridSize == sz_3x3) {
		return Texture_IDArray_3x3;
	}
	if (GridSize == sz_3x2) {
		return Texture_IDArray_3x2;
	}

	if (GridSize == sz_2x4) {
		return Texture_IDArray_2x4;
	}
	if (GridSize == sz_2x3) {
		return Texture_IDArray_2x3;
	}
	if (GridSize == sz_2x2) {
		return Texture_IDArray_2x2;
	}


	//safety
	return Texture_IDArray_7x3;
	
}

FString UMuralManager::GetProperTexture_ID(TEnumAsByte<E_GridSize> GridSize, bool bUseDebugTexture)
{
	//pick array
	auto& Texture_IDArray = ReturnProperArrayToUse(GridSize);

	//use debug texture
	if (bUseDebugTexture == true) {

		int32 RandBool = FMath::RandRange(0, 1); 

		if (RandBool == 0) {
			return Texture_IDArray[0];
		}
		else {
			return Texture_IDArray[1];
		}
	}
	//get and remove a mural
	else {
		//get a Random Index
		int32 RandIndex = FMath::RandRange(0, Texture_IDArray.Num() - 1);

		//find mural, dereference
		FString RemovedMuralName = Texture_IDArray[RandIndex];

		//ERROR GUARD
		if (Texture_IDArray.Num() == 1) {
			UE_LOG(LogTemp, Error, TEXT("reached texture limit"))

				//exit early.  don't remove texture
				return RemovedMuralName;
		}


		//remove Mural from Array
		Texture_IDArray.RemoveAt(RandIndex);

		return RemovedMuralName;
	}
}

UTexture* UMuralManager::GetProperTexture(FString Texture_ID)
{
	return TextureMap[Texture_ID].Get();
}

UTexture* UMuralManager::GetProperBorderTexture(TEnumAsByte<E_GridSize> GridSize)
{
	return BorderTextureMap[GridSize].Get();
}

UTexture* UMuralManager::GetProperBorderMask(TEnumAsByte<E_GridSize> GridSize)
{
	return BorderMaskMap[GridSize].Get();
}

//SETUP

void UMuralManager::FindAllMuralTextures_7x4()
{
	TextureMap.Emplace("m7x4_001", FindAsset("Texture'/Game/Murals/7x4/m7x4_001.m7x4_001'"));
	TextureMap.Emplace("m7x4_002", FindAsset("Texture'/Game/Murals/7x4/m7x4_002.m7x4_002'"));
	TextureMap.Emplace("m7x4_003", FindAsset("Texture'/Game/Murals/7x4/m7x4_003.m7x4_003'"));
	TextureMap.Emplace("m7x4_004", FindAsset("Texture'/Game/Murals/7x4/m7x4_004.m7x4_004'"));
	TextureMap.Emplace("m7x4_005", FindAsset("Texture'/Game/Murals/7x4/m7x4_005.m7x4_005'"));
	TextureMap.Emplace("m7x4_006", FindAsset("Texture'/Game/Murals/7x4/m7x4_006.m7x4_006'"));
	TextureMap.Emplace("m7x4_007", FindAsset("Texture'/Game/Murals/7x4/m7x4_007.m7x4_007'"));
	TextureMap.Emplace("m7x4_008", FindAsset("Texture'/Game/Murals/7x4/m7x4_008.m7x4_008'"));
	TextureMap.Emplace("m7x4_009", FindAsset("Texture'/Game/Murals/7x4/m7x4_009.m7x4_009'"));

	TextureMap.Emplace("m7x4_010", FindAsset("Texture'/Game/Murals/7x4/m7x4_010.m7x4_010'"));
	TextureMap.Emplace("m7x4_011", FindAsset("Texture'/Game/Murals/7x4/m7x4_011.m7x4_011'"));
	//TextureMap.Emplace("m7x4_012", FindAsset("Texture'/Game/Murals/7x4/m7x4_012.m7x4_012'"));
	//TextureMap.Emplace("m7x4_013", FindAsset("Texture'/Game/Murals/7x4/m7x4_013.m7x4_013'"));
	//TextureMap.Emplace("m7x4_014", FindAsset("Texture'/Game/Murals/7x4/m7x4_014.m7x4_014'"));
	//TextureMap.Emplace("m7x4_015", FindAsset("Texture'/Game/Murals/7x4/m7x4_015.m7x4_015'"));
	//TextureMap.Emplace("m7x4_016", FindAsset("Texture'/Game/Murals/7x4/m7x4_016.m7x4_016'"));
	//TextureMap.Emplace("m7x4_017", FindAsset("Texture'/Game/Murals/7x4/m7x4_017.m7x4_017'"));
	//TextureMap.Emplace("m7x4_018", FindAsset("Texture'/Game/Murals/7x4/m7x4_018.m7x4_018'"));
	//TextureMap.Emplace("m7x4_019", FindAsset("Texture'/Game/Murals/7x4/m7x4_019.m7x4_019'"));

	//TextureMap.Emplace("m7x4_020", FindAsset("Texture'/Game/Murals/7x4/m7x4_020.m7x4_020'"));
	//TextureMap.Emplace("m7x4_021", FindAsset("Texture'/Game/Murals/7x4/m7x4_021.m7x4_021'"));
	//TextureMap.Emplace("m7x4_022", FindAsset("Texture'/Game/Murals/7x4/m7x4_022.m7x4_022'"));
	//TextureMap.Emplace("m7x4_023", FindAsset("Texture'/Game/Murals/7x4/m7x4_023.m7x4_023'"));
	//TextureMap.Emplace("m7x4_024", FindAsset("Texture'/Game/Murals/7x4/m7x4_024.m7x4_024'"));
	//TextureMap.Emplace("m7x4_025", FindAsset("Texture'/Game/Murals/7x4/m7x4_025.m7x4_025'"));
	//TextureMap.Emplace("m7x4_026", FindAsset("Texture'/Game/Murals/7x4/m7x4_026.m7x4_026'"));
	//TextureMap.Emplace("m7x4_027", FindAsset("Texture'/Game/Murals/7x4/m7x4_027.m7x4_027'"));
	//TextureMap.Emplace("m7x4_028", FindAsset("Texture'/Game/Murals/7x4/m7x4_028.m7x4_028'"));
	//TextureMap.Emplace("m7x4_029", FindAsset("Texture'/Game/Murals/7x4/m7x4_029.m7x4_029'"));

	Texture_IDArray_7x4.Emplace("m7x4_001");
	Texture_IDArray_7x4.Emplace("m7x4_002");
	Texture_IDArray_7x4.Emplace("m7x4_003");
	Texture_IDArray_7x4.Emplace("m7x4_004");
	Texture_IDArray_7x4.Emplace("m7x4_005");
	Texture_IDArray_7x4.Emplace("m7x4_006");
	Texture_IDArray_7x4.Emplace("m7x4_007");
	Texture_IDArray_7x4.Emplace("m7x4_008");
	Texture_IDArray_7x4.Emplace("m7x4_009");

	Texture_IDArray_7x4.Emplace("m7x4_010");
	Texture_IDArray_7x4.Emplace("m7x4_011");
	//Texture_IDArray_7x4.Emplace("m7x4_012");
	//Texture_IDArray_7x4.Emplace("m7x4_013");
	//Texture_IDArray_7x4.Emplace("m7x4_014");
	//Texture_IDArray_7x4.Emplace("m7x4_015");
	//Texture_IDArray_7x4.Emplace("m7x4_016");
	//Texture_IDArray_7x4.Emplace("m7x4_017");
	//Texture_IDArray_7x4.Emplace("m7x4_018");
	//Texture_IDArray_7x4.Emplace("m7x4_019");

	//Texture_IDArray_7x4.Emplace("m7x4_020");
	//Texture_IDArray_7x4.Emplace("m7x4_021");
	//Texture_IDArray_7x4.Emplace("m7x4_022");
	//Texture_IDArray_7x4.Emplace("m7x4_023");
	//Texture_IDArray_7x4.Emplace("m7x4_024");
	//Texture_IDArray_7x4.Emplace("m7x4_025");
	//Texture_IDArray_7x4.Emplace("m7x4_026");
	//Texture_IDArray_7x4.Emplace("m7x4_027");
	//Texture_IDArray_7x4.Emplace("m7x4_028");
	//Texture_IDArray_7x4.Emplace("m7x4_029");

}

void UMuralManager::FindAllMuralTextures_7x3()
{
	TextureMap.Emplace("m7x3_001", FindAsset("Texture'/Game/Murals/7x3/m7x3_001.m7x3_001'"));
	TextureMap.Emplace("m7x3_002", FindAsset("Texture'/Game/Murals/7x3/m7x3_002.m7x3_002'"));
	TextureMap.Emplace("m7x3_003", FindAsset("Texture'/Game/Murals/7x3/m7x3_003.m7x3_003'"));
	TextureMap.Emplace("m7x3_004", FindAsset("Texture'/Game/Murals/7x3/m7x3_004.m7x3_004'"));
	TextureMap.Emplace("m7x3_005", FindAsset("Texture'/Game/Murals/7x3/m7x3_005.m7x3_005'"));
	TextureMap.Emplace("m7x3_006", FindAsset("Texture'/Game/Murals/7x3/m7x3_006.m7x3_006'"));
	TextureMap.Emplace("m7x3_007", FindAsset("Texture'/Game/Murals/7x3/m7x3_007.m7x3_007'"));
	TextureMap.Emplace("m7x3_008", FindAsset("Texture'/Game/Murals/7x3/m7x3_008.m7x3_008'"));
	TextureMap.Emplace("m7x3_009", FindAsset("Texture'/Game/Murals/7x3/m7x3_009.m7x3_009'"));

	TextureMap.Emplace("m7x3_010", FindAsset("Texture'/Game/Murals/7x3/m7x3_010.m7x3_010'"));
	TextureMap.Emplace("m7x3_011", FindAsset("Texture'/Game/Murals/7x3/m7x3_011.m7x3_011'"));
	//TextureMap.Emplace("m7x3_012", FindAsset("Texture'/Game/Murals/7x3/m7x3_012.m7x3_012'"));
	//TextureMap.Emplace("m7x3_013", FindAsset("Texture'/Game/Murals/7x3/m7x3_013.m7x3_013'"));
	//TextureMap.Emplace("m7x3_014", FindAsset("Texture'/Game/Murals/7x3/m7x3_014.m7x3_014'"));
	//TextureMap.Emplace("m7x3_015", FindAsset("Texture'/Game/Murals/7x3/m7x3_015.m7x3_015'"));
	//TextureMap.Emplace("m7x3_016", FindAsset("Texture'/Game/Murals/7x3/m7x3_016.m7x3_016'"));
	//TextureMap.Emplace("m7x3_017", FindAsset("Texture'/Game/Murals/7x3/m7x3_017.m7x3_017'"));
	//TextureMap.Emplace("m7x3_018", FindAsset("Texture'/Game/Murals/7x3/m7x3_018.m7x3_018'"));
	//TextureMap.Emplace("m7x3_019", FindAsset("Texture'/Game/Murals/7x3/m7x3_019.m7x3_019'"));

	//TextureMap.Emplace("m7x3_020", FindAsset("Texture'/Game/Murals/7x3/m7x3_020.m7x3_020'"));
	//TextureMap.Emplace("m7x3_021", FindAsset("Texture'/Game/Murals/7x3/m7x3_021.m7x3_021'"));
	//TextureMap.Emplace("m7x3_022", FindAsset("Texture'/Game/Murals/7x3/m7x3_022.m7x3_022'"));
	//TextureMap.Emplace("m7x3_023", FindAsset("Texture'/Game/Murals/7x3/m7x3_023.m7x3_023'"));
	//TextureMap.Emplace("m7x3_024", FindAsset("Texture'/Game/Murals/7x3/m7x3_024.m7x3_024'"));
	//TextureMap.Emplace("m7x3_025", FindAsset("Texture'/Game/Murals/7x3/m7x3_025.m7x3_025'"));
	//TextureMap.Emplace("m7x3_026", FindAsset("Texture'/Game/Murals/7x3/m7x3_026.m7x3_026'"));
	//TextureMap.Emplace("m7x3_027", FindAsset("Texture'/Game/Murals/7x3/m7x3_027.m7x3_027'"));
	//TextureMap.Emplace("m7x3_028", FindAsset("Texture'/Game/Murals/7x3/m7x3_028.m7x3_028'"));
	//TextureMap.Emplace("m7x3_029", FindAsset("Texture'/Game/Murals/7x3/m7x3_029.m7x3_029'"));

	TextureMap.Emplace("m7x3_debug_1", FindAsset("Texture'/Game/Murals/7x3/m7x3_debug_1.m7x3_debug_1'"));
	TextureMap.Emplace("m7x3_debug_2", FindAsset("Texture'/Game/Murals/7x3/m7x3_debug_2.m7x3_debug_2'"));

	Texture_IDArray_7x3.Emplace("m7x3_debug_1");
	Texture_IDArray_7x3.Emplace("m7x3_debug_2");

	Texture_IDArray_7x3.Emplace("m7x3_001");
	Texture_IDArray_7x3.Emplace("m7x3_002");
	Texture_IDArray_7x3.Emplace("m7x3_003");
	Texture_IDArray_7x3.Emplace("m7x3_004");
	Texture_IDArray_7x3.Emplace("m7x3_005");
	Texture_IDArray_7x3.Emplace("m7x3_006");
	Texture_IDArray_7x3.Emplace("m7x3_007");
	Texture_IDArray_7x3.Emplace("m7x3_008");
	Texture_IDArray_7x3.Emplace("m7x3_009");

	Texture_IDArray_7x3.Emplace("m7x3_010");
	Texture_IDArray_7x3.Emplace("m7x3_011");
	//Texture_IDArray_7x3.Emplace("m7x3_012");
	//Texture_IDArray_7x3.Emplace("m7x3_013");
	//Texture_IDArray_7x3.Emplace("m7x3_014");
	//Texture_IDArray_7x3.Emplace("m7x3_015");
	//Texture_IDArray_7x3.Emplace("m7x3_016");
	//Texture_IDArray_7x3.Emplace("m7x3_017");
	//Texture_IDArray_7x3.Emplace("m7x3_018");
	//Texture_IDArray_7x3.Emplace("m7x3_019");

	//Texture_IDArray_7x3.Emplace("m7x3_020");
	//Texture_IDArray_7x3.Emplace("m7x3_021");
	//Texture_IDArray_7x3.Emplace("m7x3_022");
	//Texture_IDArray_7x3.Emplace("m7x3_023");
	//Texture_IDArray_7x3.Emplace("m7x3_024");
	//Texture_IDArray_7x3.Emplace("m7x3_025");
	//Texture_IDArray_7x3.Emplace("m7x3_026");
	//Texture_IDArray_7x3.Emplace("m7x3_027");
	//Texture_IDArray_7x3.Emplace("m7x3_028");
	//Texture_IDArray_7x3.Emplace("m7x3_029");
}

void UMuralManager::FindAllMuralTextures_7x2()
{
	TextureMap.Emplace("m7x2_001", FindAsset("Texture'/Game/Murals/7x2/m7x2_001.m7x2_001'"));
	TextureMap.Emplace("m7x2_002", FindAsset("Texture'/Game/Murals/7x2/m7x2_002.m7x2_002'"));
	TextureMap.Emplace("m7x2_003", FindAsset("Texture'/Game/Murals/7x2/m7x2_003.m7x2_003'"));
	TextureMap.Emplace("m7x2_004", FindAsset("Texture'/Game/Murals/7x2/m7x2_004.m7x2_004'"));
	TextureMap.Emplace("m7x2_005", FindAsset("Texture'/Game/Murals/7x2/m7x2_005.m7x2_005'"));
	TextureMap.Emplace("m7x2_006", FindAsset("Texture'/Game/Murals/7x2/m7x2_006.m7x2_006'"));
	TextureMap.Emplace("m7x2_007", FindAsset("Texture'/Game/Murals/7x2/m7x2_007.m7x2_007'"));
	TextureMap.Emplace("m7x2_008", FindAsset("Texture'/Game/Murals/7x2/m7x2_008.m7x2_008'"));
	TextureMap.Emplace("m7x2_009", FindAsset("Texture'/Game/Murals/7x2/m7x2_009.m7x2_009'"));

	TextureMap.Emplace("m7x2_010", FindAsset("Texture'/Game/Murals/7x2/m7x2_010.m7x2_010'"));
	TextureMap.Emplace("m7x2_011", FindAsset("Texture'/Game/Murals/7x2/m7x2_011.m7x2_011'"));
	//TextureMap.Emplace("m7x2_012", FindAsset("Texture'/Game/Murals/7x2/m7x2_012.m7x2_012'"));
	//TextureMap.Emplace("m7x2_013", FindAsset("Texture'/Game/Murals/7x2/m7x2_013.m7x2_013'"));
	//TextureMap.Emplace("m7x2_014", FindAsset("Texture'/Game/Murals/7x2/m7x2_014.m7x2_014'"));
	//TextureMap.Emplace("m7x2_015", FindAsset("Texture'/Game/Murals/7x2/m7x2_015.m7x2_015'"));
	//TextureMap.Emplace("m7x2_016", FindAsset("Texture'/Game/Murals/7x2/m7x2_016.m7x2_016'"));
	//TextureMap.Emplace("m7x2_017", FindAsset("Texture'/Game/Murals/7x2/m7x2_017.m7x2_017'"));
	//TextureMap.Emplace("m7x2_018", FindAsset("Texture'/Game/Murals/7x2/m7x2_018.m7x2_018'"));
	//TextureMap.Emplace("m7x2_019", FindAsset("Texture'/Game/Murals/7x2/m7x2_019.m7x2_019'"));

	//TextureMap.Emplace("m7x2_020", FindAsset("Texture'/Game/Murals/7x2/m7x2_020.m7x2_020'"));
	//TextureMap.Emplace("m7x2_021", FindAsset("Texture'/Game/Murals/7x2/m7x2_021.m7x2_021'"));
	//TextureMap.Emplace("m7x2_022", FindAsset("Texture'/Game/Murals/7x2/m7x2_022.m7x2_022'"));
	//TextureMap.Emplace("m7x2_023", FindAsset("Texture'/Game/Murals/7x2/m7x2_023.m7x2_023'"));
	//TextureMap.Emplace("m7x2_024", FindAsset("Texture'/Game/Murals/7x2/m7x2_024.m7x2_024'"));
	//TextureMap.Emplace("m7x2_025", FindAsset("Texture'/Game/Murals/7x2/m7x2_025.m7x2_025'"));
	//TextureMap.Emplace("m7x2_026", FindAsset("Texture'/Game/Murals/7x2/m7x2_026.m7x2_026'"));
	//TextureMap.Emplace("m7x2_027", FindAsset("Texture'/Game/Murals/7x2/m7x2_027.m7x2_027'"));
	//TextureMap.Emplace("m7x2_028", FindAsset("Texture'/Game/Murals/7x2/m7x2_028.m7x2_028'"));
	//TextureMap.Emplace("m7x2_029", FindAsset("Texture'/Game/Murals/7x2/m7x2_029.m7x2_029'"));


	Texture_IDArray_7x2.Emplace("m7x2_001");
	Texture_IDArray_7x2.Emplace("m7x2_002");
	Texture_IDArray_7x2.Emplace("m7x2_003");
	Texture_IDArray_7x2.Emplace("m7x2_004");
	Texture_IDArray_7x2.Emplace("m7x2_005");
	Texture_IDArray_7x2.Emplace("m7x2_006");
	Texture_IDArray_7x2.Emplace("m7x2_007");
	Texture_IDArray_7x2.Emplace("m7x2_008");
	Texture_IDArray_7x2.Emplace("m7x2_009");

	Texture_IDArray_7x2.Emplace("m7x2_010");
	Texture_IDArray_7x2.Emplace("m7x2_011");
	//Texture_IDArray_7x2.Emplace("m7x2_012");
	//Texture_IDArray_7x2.Emplace("m7x2_013");
	//Texture_IDArray_7x2.Emplace("m7x2_014");
	//Texture_IDArray_7x2.Emplace("m7x2_015");
	//Texture_IDArray_7x2.Emplace("m7x2_016");
	//Texture_IDArray_7x2.Emplace("m7x2_017");
	//Texture_IDArray_7x2.Emplace("m7x2_018");
	//Texture_IDArray_7x2.Emplace("m7x2_019");

	//Texture_IDArray_7x2.Emplace("m7x2_020");
	//Texture_IDArray_7x2.Emplace("m7x2_021");
	//Texture_IDArray_7x2.Emplace("m7x2_022");
	//Texture_IDArray_7x2.Emplace("m7x2_023");
	//Texture_IDArray_7x2.Emplace("m7x2_024");
	//Texture_IDArray_7x2.Emplace("m7x2_025");
	//Texture_IDArray_7x2.Emplace("m7x2_026");
	//Texture_IDArray_7x2.Emplace("m7x2_027");
	//Texture_IDArray_7x2.Emplace("m7x2_028");
	//Texture_IDArray_7x2.Emplace("m7x2_029");
}


void UMuralManager::FindAllMuralTextures_6x4()
{
	TextureMap.Emplace("m6x4_001", FindAsset("Texture'/Game/Murals/6x4/m6x4_001.m6x4_001'"));
	TextureMap.Emplace("m6x4_002", FindAsset("Texture'/Game/Murals/6x4/m6x4_002.m6x4_002'"));
	TextureMap.Emplace("m6x4_003", FindAsset("Texture'/Game/Murals/6x4/m6x4_003.m6x4_003'"));
	TextureMap.Emplace("m6x4_004", FindAsset("Texture'/Game/Murals/6x4/m6x4_004.m6x4_004'"));
	TextureMap.Emplace("m6x4_005", FindAsset("Texture'/Game/Murals/6x4/m6x4_005.m6x4_005'"));
	TextureMap.Emplace("m6x4_006", FindAsset("Texture'/Game/Murals/6x4/m6x4_006.m6x4_006'"));
	TextureMap.Emplace("m6x4_007", FindAsset("Texture'/Game/Murals/6x4/m6x4_007.m6x4_007'"));
	TextureMap.Emplace("m6x4_008", FindAsset("Texture'/Game/Murals/6x4/m6x4_008.m6x4_008'"));
	TextureMap.Emplace("m6x4_009", FindAsset("Texture'/Game/Murals/6x4/m6x4_009.m6x4_009'"));

	TextureMap.Emplace("m6x4_010", FindAsset("Texture'/Game/Murals/6x4/m6x4_010.m6x4_010'"));
	TextureMap.Emplace("m6x4_011", FindAsset("Texture'/Game/Murals/6x4/m6x4_011.m6x4_011'"));
	//TextureMap.Emplace("m6x4_012", FindAsset("Texture'/Game/Murals/6x4/m6x4_012.m6x4_012'"));
	//TextureMap.Emplace("m6x4_013", FindAsset("Texture'/Game/Murals/6x4/m6x4_013.m6x4_013'"));
	//TextureMap.Emplace("m6x4_014", FindAsset("Texture'/Game/Murals/6x4/m6x4_014.m6x4_014'"));
	//TextureMap.Emplace("m6x4_015", FindAsset("Texture'/Game/Murals/6x4/m6x4_015.m6x4_015'"));
	//TextureMap.Emplace("m6x4_016", FindAsset("Texture'/Game/Murals/6x4/m6x4_016.m6x4_016'"));
	//TextureMap.Emplace("m6x4_017", FindAsset("Texture'/Game/Murals/6x4/m6x4_017.m6x4_017'"));
	//TextureMap.Emplace("m6x4_018", FindAsset("Texture'/Game/Murals/6x4/m6x4_018.m6x4_018'"));
	//TextureMap.Emplace("m6x4_019", FindAsset("Texture'/Game/Murals/6x4/m6x4_019.m6x4_019'"));

	//TextureMap.Emplace("m6x4_020", FindAsset("Texture'/Game/Murals/6x4/m6x4_020.m6x4_020'"));
	//TextureMap.Emplace("m6x4_021", FindAsset("Texture'/Game/Murals/6x4/m6x4_021.m6x4_021'"));
	//TextureMap.Emplace("m6x4_022", FindAsset("Texture'/Game/Murals/6x4/m6x4_022.m6x4_022'"));
	//TextureMap.Emplace("m6x4_023", FindAsset("Texture'/Game/Murals/6x4/m6x4_023.m6x4_023'"));
	//TextureMap.Emplace("m6x4_024", FindAsset("Texture'/Game/Murals/6x4/m6x4_024.m6x4_024'"));
	//TextureMap.Emplace("m6x4_025", FindAsset("Texture'/Game/Murals/6x4/m6x4_025.m6x4_025'"));
	//TextureMap.Emplace("m6x4_026", FindAsset("Texture'/Game/Murals/6x4/m6x4_026.m6x4_026'"));
	//TextureMap.Emplace("m6x4_027", FindAsset("Texture'/Game/Murals/6x4/m6x4_027.m6x4_027'"));
	//TextureMap.Emplace("m6x4_028", FindAsset("Texture'/Game/Murals/6x4/m6x4_028.m6x4_028'"));
	//TextureMap.Emplace("m6x4_029", FindAsset("Texture'/Game/Murals/6x4/m6x4_029.m6x4_029'"));


	Texture_IDArray_6x4.Emplace("m6x4_001");
	Texture_IDArray_6x4.Emplace("m6x4_002");
	Texture_IDArray_6x4.Emplace("m6x4_003");
	Texture_IDArray_6x4.Emplace("m6x4_004");
	Texture_IDArray_6x4.Emplace("m6x4_005");
	Texture_IDArray_6x4.Emplace("m6x4_006");
	Texture_IDArray_6x4.Emplace("m6x4_007");
	Texture_IDArray_6x4.Emplace("m6x4_008");
	Texture_IDArray_6x4.Emplace("m6x4_009");

	Texture_IDArray_6x4.Emplace("m6x4_010");
	Texture_IDArray_6x4.Emplace("m6x4_011");
	//Texture_IDArray_6x4.Emplace("m6x4_012");
	//Texture_IDArray_6x4.Emplace("m6x4_013");
	//Texture_IDArray_6x4.Emplace("m6x4_014");
	//Texture_IDArray_6x4.Emplace("m6x4_015");
	//Texture_IDArray_6x4.Emplace("m6x4_016");
	//Texture_IDArray_6x4.Emplace("m6x4_017");
	//Texture_IDArray_6x4.Emplace("m6x4_018");
	//Texture_IDArray_6x4.Emplace("m6x4_019");

	//Texture_IDArray_6x4.Emplace("m6x4_020");
	//Texture_IDArray_6x4.Emplace("m6x4_021");
	//Texture_IDArray_6x4.Emplace("m6x4_022");
	//Texture_IDArray_6x4.Emplace("m6x4_023");
	//Texture_IDArray_6x4.Emplace("m6x4_024");
	//Texture_IDArray_6x4.Emplace("m6x4_025");
	//Texture_IDArray_6x4.Emplace("m6x4_026");
	//Texture_IDArray_6x4.Emplace("m6x4_027");
	//Texture_IDArray_6x4.Emplace("m6x4_028");
	//Texture_IDArray_6x4.Emplace("m6x4_029");
}

void UMuralManager::FindAllMuralTextures_6x3()
{
	TextureMap.Emplace("m6x3_001", FindAsset("Texture'/Game/Murals/6x3/m6x3_001.m6x3_001'"));
	TextureMap.Emplace("m6x3_002", FindAsset("Texture'/Game/Murals/6x3/m6x3_002.m6x3_002'"));
	TextureMap.Emplace("m6x3_003", FindAsset("Texture'/Game/Murals/6x3/m6x3_003.m6x3_003'"));
	TextureMap.Emplace("m6x3_004", FindAsset("Texture'/Game/Murals/6x3/m6x3_004.m6x3_004'"));
	TextureMap.Emplace("m6x3_005", FindAsset("Texture'/Game/Murals/6x3/m6x3_005.m6x3_005'"));
	TextureMap.Emplace("m6x3_006", FindAsset("Texture'/Game/Murals/6x3/m6x3_006.m6x3_006'"));
	TextureMap.Emplace("m6x3_007", FindAsset("Texture'/Game/Murals/6x3/m6x3_007.m6x3_007'"));
	TextureMap.Emplace("m6x3_008", FindAsset("Texture'/Game/Murals/6x3/m6x3_008.m6x3_008'"));
	TextureMap.Emplace("m6x3_009", FindAsset("Texture'/Game/Murals/6x3/m6x3_009.m6x3_009'"));

	TextureMap.Emplace("m6x3_010", FindAsset("Texture'/Game/Murals/6x3/m6x3_010.m6x3_010'"));
	TextureMap.Emplace("m6x3_011", FindAsset("Texture'/Game/Murals/6x3/m6x3_011.m6x3_011'"));
	//TextureMap.Emplace("m6x3_012", FindAsset("Texture'/Game/Murals/6x3/m6x3_012.m6x3_012'"));
	//TextureMap.Emplace("m6x3_013", FindAsset("Texture'/Game/Murals/6x3/m6x3_013.m6x3_013'"));
	//TextureMap.Emplace("m6x3_014", FindAsset("Texture'/Game/Murals/6x3/m6x3_014.m6x3_014'"));
	//TextureMap.Emplace("m6x3_015", FindAsset("Texture'/Game/Murals/6x3/m6x3_015.m6x3_015'"));
	//TextureMap.Emplace("m6x3_016", FindAsset("Texture'/Game/Murals/6x3/m6x3_016.m6x3_016'"));
	//TextureMap.Emplace("m6x3_017", FindAsset("Texture'/Game/Murals/6x3/m6x3_017.m6x3_017'"));
	//TextureMap.Emplace("m6x3_018", FindAsset("Texture'/Game/Murals/6x3/m6x3_018.m6x3_018'"));
	//TextureMap.Emplace("m6x3_019", FindAsset("Texture'/Game/Murals/6x3/m6x3_019.m6x3_019'"));

	//TextureMap.Emplace("m6x3_020", FindAsset("Texture'/Game/Murals/6x3/m6x3_020.m6x3_020'"));
	//TextureMap.Emplace("m6x3_021", FindAsset("Texture'/Game/Murals/6x3/m6x3_021.m6x3_021'"));
	//TextureMap.Emplace("m6x3_022", FindAsset("Texture'/Game/Murals/6x3/m6x3_022.m6x3_022'"));
	//TextureMap.Emplace("m6x3_023", FindAsset("Texture'/Game/Murals/6x3/m6x3_023.m6x3_023'"));
	//TextureMap.Emplace("m6x3_024", FindAsset("Texture'/Game/Murals/6x3/m6x3_024.m6x3_024'"));
	//TextureMap.Emplace("m6x3_025", FindAsset("Texture'/Game/Murals/6x3/m6x3_025.m6x3_025'"));
	//TextureMap.Emplace("m6x3_026", FindAsset("Texture'/Game/Murals/6x3/m6x3_026.m6x3_026'"));
	//TextureMap.Emplace("m6x3_027", FindAsset("Texture'/Game/Murals/6x3/m6x3_027.m6x3_027'"));
	//TextureMap.Emplace("m6x3_028", FindAsset("Texture'/Game/Murals/6x3/m6x3_028.m6x3_028'"));
	//TextureMap.Emplace("m6x3_029", FindAsset("Texture'/Game/Murals/6x3/m6x3_029.m6x3_029'"));


	Texture_IDArray_6x3.Emplace("m6x3_001");
	Texture_IDArray_6x3.Emplace("m6x3_002");
	Texture_IDArray_6x3.Emplace("m6x3_003");
	Texture_IDArray_6x3.Emplace("m6x3_004");
	Texture_IDArray_6x3.Emplace("m6x3_005");
	Texture_IDArray_6x3.Emplace("m6x3_006");
	Texture_IDArray_6x3.Emplace("m6x3_007");
	Texture_IDArray_6x3.Emplace("m6x3_008");
	Texture_IDArray_6x3.Emplace("m6x3_009");

	Texture_IDArray_6x3.Emplace("m6x3_010");
	Texture_IDArray_6x3.Emplace("m6x3_011");
	//Texture_IDArray_6x3.Emplace("m6x3_012");
	//Texture_IDArray_6x3.Emplace("m6x3_013");
	//Texture_IDArray_6x3.Emplace("m6x3_014");
	//Texture_IDArray_6x3.Emplace("m6x3_015");
	//Texture_IDArray_6x3.Emplace("m6x3_016");
	//Texture_IDArray_6x3.Emplace("m6x3_017");
	//Texture_IDArray_6x3.Emplace("m6x3_018");
	//Texture_IDArray_6x3.Emplace("m6x3_019");

	//Texture_IDArray_6x3.Emplace("m6x3_020");
	//Texture_IDArray_6x3.Emplace("m6x3_021");
	//Texture_IDArray_6x3.Emplace("m6x3_022");
	//Texture_IDArray_6x3.Emplace("m6x3_023");
	//Texture_IDArray_6x3.Emplace("m6x3_024");
	//Texture_IDArray_6x3.Emplace("m6x3_025");
	//Texture_IDArray_6x3.Emplace("m6x3_026");
	//Texture_IDArray_6x3.Emplace("m6x3_027");
	//Texture_IDArray_6x3.Emplace("m6x3_028");
	//Texture_IDArray_6x3.Emplace("m6x3_029");
}

void UMuralManager::FindAllMuralTextures_6x2()
{
	TextureMap.Emplace("m6x2_001", FindAsset("Texture'/Game/Murals/6x2/m6x2_001.m6x2_001'"));
	TextureMap.Emplace("m6x2_002", FindAsset("Texture'/Game/Murals/6x2/m6x2_002.m6x2_002'"));
	TextureMap.Emplace("m6x2_003", FindAsset("Texture'/Game/Murals/6x2/m6x2_003.m6x2_003'"));
	TextureMap.Emplace("m6x2_004", FindAsset("Texture'/Game/Murals/6x2/m6x2_004.m6x2_004'"));
	TextureMap.Emplace("m6x2_005", FindAsset("Texture'/Game/Murals/6x2/m6x2_005.m6x2_005'"));
	TextureMap.Emplace("m6x2_006", FindAsset("Texture'/Game/Murals/6x2/m6x2_006.m6x2_006'"));
	TextureMap.Emplace("m6x2_007", FindAsset("Texture'/Game/Murals/6x2/m6x2_007.m6x2_007'"));
	TextureMap.Emplace("m6x2_008", FindAsset("Texture'/Game/Murals/6x2/m6x2_008.m6x2_008'"));
	TextureMap.Emplace("m6x2_009", FindAsset("Texture'/Game/Murals/6x2/m6x2_009.m6x2_009'"));

	TextureMap.Emplace("m6x2_010", FindAsset("Texture'/Game/Murals/6x2/m6x2_010.m6x2_010'"));
	TextureMap.Emplace("m6x2_011", FindAsset("Texture'/Game/Murals/6x2/m6x2_011.m6x2_011'"));
	//TextureMap.Emplace("m6x2_012", FindAsset("Texture'/Game/Murals/6x2/m6x2_012.m6x2_012'"));
	//TextureMap.Emplace("m6x2_013", FindAsset("Texture'/Game/Murals/6x2/m6x2_013.m6x2_013'"));
	//TextureMap.Emplace("m6x2_014", FindAsset("Texture'/Game/Murals/6x2/m6x2_014.m6x2_014'"));
	//TextureMap.Emplace("m6x2_015", FindAsset("Texture'/Game/Murals/6x2/m6x2_015.m6x2_015'"));
	//TextureMap.Emplace("m6x2_016", FindAsset("Texture'/Game/Murals/6x2/m6x2_016.m6x2_016'"));
	//TextureMap.Emplace("m6x2_017", FindAsset("Texture'/Game/Murals/6x2/m6x2_017.m6x2_017'"));
	//TextureMap.Emplace("m6x2_018", FindAsset("Texture'/Game/Murals/6x2/m6x2_018.m6x2_018'"));
	//TextureMap.Emplace("m6x2_019", FindAsset("Texture'/Game/Murals/6x2/m6x2_019.m6x2_019'"));

	//TextureMap.Emplace("m6x2_020", FindAsset("Texture'/Game/Murals/6x2/m6x2_020.m6x2_020'"));
	//TextureMap.Emplace("m6x2_021", FindAsset("Texture'/Game/Murals/6x2/m6x2_021.m6x2_021'"));
	//TextureMap.Emplace("m6x2_022", FindAsset("Texture'/Game/Murals/6x2/m6x2_022.m6x2_022'"));
	//TextureMap.Emplace("m6x2_023", FindAsset("Texture'/Game/Murals/6x2/m6x2_023.m6x2_023'"));
	//TextureMap.Emplace("m6x2_024", FindAsset("Texture'/Game/Murals/6x2/m6x2_024.m6x2_024'"));
	//TextureMap.Emplace("m6x2_025", FindAsset("Texture'/Game/Murals/6x2/m6x2_025.m6x2_025'"));
	//TextureMap.Emplace("m6x2_026", FindAsset("Texture'/Game/Murals/6x2/m6x2_026.m6x2_026'"));
	//TextureMap.Emplace("m6x2_027", FindAsset("Texture'/Game/Murals/6x2/m6x2_027.m6x2_027'"));
	//TextureMap.Emplace("m6x2_028", FindAsset("Texture'/Game/Murals/6x2/m6x2_028.m6x2_028'"));
	//TextureMap.Emplace("m6x2_029", FindAsset("Texture'/Game/Murals/6x2/m6x2_029.m6x2_029'"));


	Texture_IDArray_6x2.Emplace("m6x2_001");
	Texture_IDArray_6x2.Emplace("m6x2_002");
	Texture_IDArray_6x2.Emplace("m6x2_003");
	Texture_IDArray_6x2.Emplace("m6x2_004");
	Texture_IDArray_6x2.Emplace("m6x2_005");
	Texture_IDArray_6x2.Emplace("m6x2_006");
	Texture_IDArray_6x2.Emplace("m6x2_007");
	Texture_IDArray_6x2.Emplace("m6x2_008");
	Texture_IDArray_6x2.Emplace("m6x2_009");

	Texture_IDArray_6x2.Emplace("m6x2_010");
	Texture_IDArray_6x2.Emplace("m6x2_011");
	//Texture_IDArray_6x2.Emplace("m6x2_012");
	//Texture_IDArray_6x2.Emplace("m6x2_013");
	//Texture_IDArray_6x2.Emplace("m6x2_014");
	//Texture_IDArray_6x2.Emplace("m6x2_015");
	//Texture_IDArray_6x2.Emplace("m6x2_016");
	//Texture_IDArray_6x2.Emplace("m6x2_017");
	//Texture_IDArray_6x2.Emplace("m6x2_018");
	//Texture_IDArray_6x2.Emplace("m6x2_019");

	//Texture_IDArray_6x2.Emplace("m6x2_020");
	//Texture_IDArray_6x2.Emplace("m6x2_021");
	//Texture_IDArray_6x2.Emplace("m6x2_022");
	//Texture_IDArray_6x2.Emplace("m6x2_023");
	//Texture_IDArray_6x2.Emplace("m6x2_024");
	//Texture_IDArray_6x2.Emplace("m6x2_025");
	//Texture_IDArray_6x2.Emplace("m6x2_026");
	//Texture_IDArray_6x2.Emplace("m6x2_027");
	//Texture_IDArray_6x2.Emplace("m6x2_028");
	//Texture_IDArray_6x2.Emplace("m6x2_029");
}


void UMuralManager::FindAllMuralTextures_5x4()
{
	TextureMap.Emplace("m5x4_001", FindAsset("Texture'/Game/Murals/5x4/m5x4_001.m5x4_001'"));
	TextureMap.Emplace("m5x4_002", FindAsset("Texture'/Game/Murals/5x4/m5x4_002.m5x4_002'"));
	TextureMap.Emplace("m5x4_003", FindAsset("Texture'/Game/Murals/5x4/m5x4_003.m5x4_003'"));
	TextureMap.Emplace("m5x4_004", FindAsset("Texture'/Game/Murals/5x4/m5x4_004.m5x4_004'"));
	TextureMap.Emplace("m5x4_005", FindAsset("Texture'/Game/Murals/5x4/m5x4_005.m5x4_005'"));
	TextureMap.Emplace("m5x4_006", FindAsset("Texture'/Game/Murals/5x4/m5x4_006.m5x4_006'"));
	TextureMap.Emplace("m5x4_007", FindAsset("Texture'/Game/Murals/5x4/m5x4_007.m5x4_007'"));
	TextureMap.Emplace("m5x4_008", FindAsset("Texture'/Game/Murals/5x4/m5x4_008.m5x4_008'"));
	TextureMap.Emplace("m5x4_009", FindAsset("Texture'/Game/Murals/5x4/m5x4_009.m5x4_009'"));

	TextureMap.Emplace("m5x4_010", FindAsset("Texture'/Game/Murals/5x4/m5x4_010.m5x4_010'"));
	TextureMap.Emplace("m5x4_011", FindAsset("Texture'/Game/Murals/5x4/m5x4_011.m5x4_011'"));
	//TextureMap.Emplace("m5x4_012", FindAsset("Texture'/Game/Murals/5x4/m5x4_012.m5x4_012'"));
	//TextureMap.Emplace("m5x4_013", FindAsset("Texture'/Game/Murals/5x4/m5x4_013.m5x4_013'"));
	//TextureMap.Emplace("m5x4_014", FindAsset("Texture'/Game/Murals/5x4/m5x4_014.m5x4_014'"));
	//TextureMap.Emplace("m5x4_015", FindAsset("Texture'/Game/Murals/5x4/m5x4_015.m5x4_015'"));
	//TextureMap.Emplace("m5x4_016", FindAsset("Texture'/Game/Murals/5x4/m5x4_016.m5x4_016'"));
	//TextureMap.Emplace("m5x4_017", FindAsset("Texture'/Game/Murals/5x4/m5x4_017.m5x4_017'"));
	//TextureMap.Emplace("m5x4_018", FindAsset("Texture'/Game/Murals/5x4/m5x4_018.m5x4_018'"));
	//TextureMap.Emplace("m5x4_019", FindAsset("Texture'/Game/Murals/5x4/m5x4_019.m5x4_019'"));

	//TextureMap.Emplace("m5x4_020", FindAsset("Texture'/Game/Murals/5x4/m5x4_020.m5x4_020'"));
	//TextureMap.Emplace("m5x4_021", FindAsset("Texture'/Game/Murals/5x4/m5x4_021.m5x4_021'"));
	//TextureMap.Emplace("m5x4_022", FindAsset("Texture'/Game/Murals/5x4/m5x4_022.m5x4_022'"));
	//TextureMap.Emplace("m5x4_023", FindAsset("Texture'/Game/Murals/5x4/m5x4_023.m5x4_023'"));
	//TextureMap.Emplace("m5x4_024", FindAsset("Texture'/Game/Murals/5x4/m5x4_024.m5x4_024'"));
	//TextureMap.Emplace("m5x4_025", FindAsset("Texture'/Game/Murals/5x4/m5x4_025.m5x4_025'"));
	//TextureMap.Emplace("m5x4_026", FindAsset("Texture'/Game/Murals/5x4/m5x4_026.m5x4_026'"));
	//TextureMap.Emplace("m5x4_027", FindAsset("Texture'/Game/Murals/5x4/m5x4_027.m5x4_027'"));
	//TextureMap.Emplace("m5x4_028", FindAsset("Texture'/Game/Murals/5x4/m5x4_028.m5x4_028'"));
	//TextureMap.Emplace("m5x4_029", FindAsset("Texture'/Game/Murals/5x4/m5x4_029.m5x4_029'"));


	Texture_IDArray_5x4.Emplace("m5x4_001");
	Texture_IDArray_5x4.Emplace("m5x4_002");
	Texture_IDArray_5x4.Emplace("m5x4_003");
	Texture_IDArray_5x4.Emplace("m5x4_004");
	Texture_IDArray_5x4.Emplace("m5x4_005");
	Texture_IDArray_5x4.Emplace("m5x4_006");
	Texture_IDArray_5x4.Emplace("m5x4_007");
	Texture_IDArray_5x4.Emplace("m5x4_008");
	Texture_IDArray_5x4.Emplace("m5x4_009");

	Texture_IDArray_5x4.Emplace("m5x4_010");
	Texture_IDArray_5x4.Emplace("m5x4_011");
	//Texture_IDArray_5x4.Emplace("m5x4_012");
	//Texture_IDArray_5x4.Emplace("m5x4_013");
	//Texture_IDArray_5x4.Emplace("m5x4_014");
	//Texture_IDArray_5x4.Emplace("m5x4_015");
	//Texture_IDArray_5x4.Emplace("m5x4_016");
	//Texture_IDArray_5x4.Emplace("m5x4_017");
	//Texture_IDArray_5x4.Emplace("m5x4_018");
	//Texture_IDArray_5x4.Emplace("m5x4_019");

	//Texture_IDArray_5x4.Emplace("m5x4_020");
	//Texture_IDArray_5x4.Emplace("m5x4_021");
	//Texture_IDArray_5x4.Emplace("m5x4_022");
	//Texture_IDArray_5x4.Emplace("m5x4_023");
	//Texture_IDArray_5x4.Emplace("m5x4_024");
	//Texture_IDArray_5x4.Emplace("m5x4_025");
	//Texture_IDArray_5x4.Emplace("m5x4_026");
	//Texture_IDArray_5x4.Emplace("m5x4_027");
	//Texture_IDArray_5x4.Emplace("m5x4_028");
	//Texture_IDArray_5x4.Emplace("m5x4_029");
}

void UMuralManager::FindAllMuralTextures_5x3()
{
	TextureMap.Emplace("m5x3_001", FindAsset("Texture'/Game/Murals/5x3/m5x3_001.m5x3_001'"));
	TextureMap.Emplace("m5x3_002", FindAsset("Texture'/Game/Murals/5x3/m5x3_002.m5x3_002'"));
	TextureMap.Emplace("m5x3_003", FindAsset("Texture'/Game/Murals/5x3/m5x3_003.m5x3_003'"));
	TextureMap.Emplace("m5x3_004", FindAsset("Texture'/Game/Murals/5x3/m5x3_004.m5x3_004'"));
	TextureMap.Emplace("m5x3_005", FindAsset("Texture'/Game/Murals/5x3/m5x3_005.m5x3_005'"));
	TextureMap.Emplace("m5x3_006", FindAsset("Texture'/Game/Murals/5x3/m5x3_006.m5x3_006'"));
	TextureMap.Emplace("m5x3_007", FindAsset("Texture'/Game/Murals/5x3/m5x3_007.m5x3_007'"));
	TextureMap.Emplace("m5x3_008", FindAsset("Texture'/Game/Murals/5x3/m5x3_008.m5x3_008'"));
	TextureMap.Emplace("m5x3_009", FindAsset("Texture'/Game/Murals/5x3/m5x3_009.m5x3_009'"));

	TextureMap.Emplace("m5x3_010", FindAsset("Texture'/Game/Murals/5x3/m5x3_010.m5x3_010'"));
	TextureMap.Emplace("m5x3_011", FindAsset("Texture'/Game/Murals/5x3/m5x3_011.m5x3_011'"));
	//TextureMap.Emplace("m5x3_012", FindAsset("Texture'/Game/Murals/5x3/m5x3_012.m5x3_012'"));
	//TextureMap.Emplace("m5x3_013", FindAsset("Texture'/Game/Murals/5x3/m5x3_013.m5x3_013'"));
	//TextureMap.Emplace("m5x3_014", FindAsset("Texture'/Game/Murals/5x3/m5x3_014.m5x3_014'"));
	//TextureMap.Emplace("m5x3_015", FindAsset("Texture'/Game/Murals/5x3/m5x3_015.m5x3_015'"));
	//TextureMap.Emplace("m5x3_016", FindAsset("Texture'/Game/Murals/5x3/m5x3_016.m5x3_016'"));
	//TextureMap.Emplace("m5x3_017", FindAsset("Texture'/Game/Murals/5x3/m5x3_017.m5x3_017'"));
	//TextureMap.Emplace("m5x3_018", FindAsset("Texture'/Game/Murals/5x3/m5x3_018.m5x3_018'"));
	//TextureMap.Emplace("m5x3_019", FindAsset("Texture'/Game/Murals/5x3/m5x3_019.m5x3_019'"));

	//TextureMap.Emplace("m5x3_020", FindAsset("Texture'/Game/Murals/5x3/m5x3_020.m5x3_020'"));
	//TextureMap.Emplace("m5x3_021", FindAsset("Texture'/Game/Murals/5x3/m5x3_021.m5x3_021'"));
	//TextureMap.Emplace("m5x3_022", FindAsset("Texture'/Game/Murals/5x3/m5x3_022.m5x3_022'"));
	//TextureMap.Emplace("m5x3_023", FindAsset("Texture'/Game/Murals/5x3/m5x3_023.m5x3_023'"));
	//TextureMap.Emplace("m5x3_024", FindAsset("Texture'/Game/Murals/5x3/m5x3_024.m5x3_024'"));
	//TextureMap.Emplace("m5x3_025", FindAsset("Texture'/Game/Murals/5x3/m5x3_025.m5x3_025'"));
	//TextureMap.Emplace("m5x3_026", FindAsset("Texture'/Game/Murals/5x3/m5x3_026.m5x3_026'"));
	//TextureMap.Emplace("m5x3_027", FindAsset("Texture'/Game/Murals/5x3/m5x3_027.m5x3_027'"));
	//TextureMap.Emplace("m5x3_028", FindAsset("Texture'/Game/Murals/5x3/m5x3_028.m5x3_028'"));
	//TextureMap.Emplace("m5x3_029", FindAsset("Texture'/Game/Murals/5x3/m5x3_029.m5x3_029'"));


	Texture_IDArray_5x3.Emplace("m5x3_001");
	Texture_IDArray_5x3.Emplace("m5x3_002");
	Texture_IDArray_5x3.Emplace("m5x3_003");
	Texture_IDArray_5x3.Emplace("m5x3_004");
	Texture_IDArray_5x3.Emplace("m5x3_005");
	Texture_IDArray_5x3.Emplace("m5x3_006");
	Texture_IDArray_5x3.Emplace("m5x3_007");
	Texture_IDArray_5x3.Emplace("m5x3_008");
	Texture_IDArray_5x3.Emplace("m5x3_009");

	Texture_IDArray_5x3.Emplace("m5x3_010");
	Texture_IDArray_5x3.Emplace("m5x3_011");
	//Texture_IDArray_5x3.Emplace("m5x3_012");
	//Texture_IDArray_5x3.Emplace("m5x3_013");
	//Texture_IDArray_5x3.Emplace("m5x3_014");
	//Texture_IDArray_5x3.Emplace("m5x3_015");
	//Texture_IDArray_5x3.Emplace("m5x3_016");
	//Texture_IDArray_5x3.Emplace("m5x3_017");
	//Texture_IDArray_5x3.Emplace("m5x3_018");
	//Texture_IDArray_5x3.Emplace("m5x3_019");

	//Texture_IDArray_5x3.Emplace("m5x3_020");
	//Texture_IDArray_5x3.Emplace("m5x3_021");
	//Texture_IDArray_5x3.Emplace("m5x3_022");
	//Texture_IDArray_5x3.Emplace("m5x3_023");
	//Texture_IDArray_5x3.Emplace("m5x3_024");
	//Texture_IDArray_5x3.Emplace("m5x3_025");
	//Texture_IDArray_5x3.Emplace("m5x3_026");
	//Texture_IDArray_5x3.Emplace("m5x3_027");
	//Texture_IDArray_5x3.Emplace("m5x3_028");
	//Texture_IDArray_5x3.Emplace("m5x3_029");
}

void UMuralManager::FindAllMuralTextures_5x2()
{
	TextureMap.Emplace("m5x2_001", FindAsset("Texture'/Game/Murals/5x2/m5x2_001.m5x2_001'"));
	TextureMap.Emplace("m5x2_002", FindAsset("Texture'/Game/Murals/5x2/m5x2_002.m5x2_002'"));
	TextureMap.Emplace("m5x2_003", FindAsset("Texture'/Game/Murals/5x2/m5x2_003.m5x2_003'"));
	TextureMap.Emplace("m5x2_004", FindAsset("Texture'/Game/Murals/5x2/m5x2_004.m5x2_004'"));
	TextureMap.Emplace("m5x2_005", FindAsset("Texture'/Game/Murals/5x2/m5x2_005.m5x2_005'"));
	TextureMap.Emplace("m5x2_006", FindAsset("Texture'/Game/Murals/5x2/m5x2_006.m5x2_006'"));
	TextureMap.Emplace("m5x2_007", FindAsset("Texture'/Game/Murals/5x2/m5x2_007.m5x2_007'"));
	TextureMap.Emplace("m5x2_008", FindAsset("Texture'/Game/Murals/5x2/m5x2_008.m5x2_008'"));
	TextureMap.Emplace("m5x2_009", FindAsset("Texture'/Game/Murals/5x2/m5x2_009.m5x2_009'"));

	TextureMap.Emplace("m5x2_010", FindAsset("Texture'/Game/Murals/5x2/m5x2_010.m5x2_010'"));
	TextureMap.Emplace("m5x2_011", FindAsset("Texture'/Game/Murals/5x2/m5x2_011.m5x2_011'"));
	//TextureMap.Emplace("m5x2_012", FindAsset("Texture'/Game/Murals/5x2/m5x2_012.m5x2_012'"));
	//TextureMap.Emplace("m5x2_013", FindAsset("Texture'/Game/Murals/5x2/m5x2_013.m5x2_013'"));
	//TextureMap.Emplace("m5x2_014", FindAsset("Texture'/Game/Murals/5x2/m5x2_014.m5x2_014'"));
	//TextureMap.Emplace("m5x2_015", FindAsset("Texture'/Game/Murals/5x2/m5x2_015.m5x2_015'"));
	//TextureMap.Emplace("m5x2_016", FindAsset("Texture'/Game/Murals/5x2/m5x2_016.m5x2_016'"));
	//TextureMap.Emplace("m5x2_017", FindAsset("Texture'/Game/Murals/5x2/m5x2_017.m5x2_017'"));
	//TextureMap.Emplace("m5x2_018", FindAsset("Texture'/Game/Murals/5x2/m5x2_018.m5x2_018'"));
	//TextureMap.Emplace("m5x2_019", FindAsset("Texture'/Game/Murals/5x2/m5x2_019.m5x2_019'"));

	//TextureMap.Emplace("m5x2_020", FindAsset("Texture'/Game/Murals/5x2/m5x2_020.m5x2_020'"));
	//TextureMap.Emplace("m5x2_021", FindAsset("Texture'/Game/Murals/5x2/m5x2_021.m5x2_021'"));
	//TextureMap.Emplace("m5x2_022", FindAsset("Texture'/Game/Murals/5x2/m5x2_022.m5x2_022'"));
	//TextureMap.Emplace("m5x2_023", FindAsset("Texture'/Game/Murals/5x2/m5x2_023.m5x2_023'"));
	//TextureMap.Emplace("m5x2_024", FindAsset("Texture'/Game/Murals/5x2/m5x2_024.m5x2_024'"));
	//TextureMap.Emplace("m5x2_025", FindAsset("Texture'/Game/Murals/5x2/m5x2_025.m5x2_025'"));
	//TextureMap.Emplace("m5x2_026", FindAsset("Texture'/Game/Murals/5x2/m5x2_026.m5x2_026'"));
	//TextureMap.Emplace("m5x2_027", FindAsset("Texture'/Game/Murals/5x2/m5x2_027.m5x2_027'"));
	//TextureMap.Emplace("m5x2_028", FindAsset("Texture'/Game/Murals/5x2/m5x2_028.m5x2_028'"));
	//TextureMap.Emplace("m5x2_029", FindAsset("Texture'/Game/Murals/5x2/m5x2_029.m5x2_029'"));


	Texture_IDArray_5x2.Emplace("m5x2_001");
	Texture_IDArray_5x2.Emplace("m5x2_002");
	Texture_IDArray_5x2.Emplace("m5x2_003");
	Texture_IDArray_5x2.Emplace("m5x2_004");
	Texture_IDArray_5x2.Emplace("m5x2_005");
	Texture_IDArray_5x2.Emplace("m5x2_006");
	Texture_IDArray_5x2.Emplace("m5x2_007");
	Texture_IDArray_5x2.Emplace("m5x2_008");
	Texture_IDArray_5x2.Emplace("m5x2_009");

	Texture_IDArray_5x2.Emplace("m5x2_010");
	Texture_IDArray_5x2.Emplace("m5x2_011");
	//Texture_IDArray_5x2.Emplace("m5x2_012");
	//Texture_IDArray_5x2.Emplace("m5x2_013");
	//Texture_IDArray_5x2.Emplace("m5x2_014");
	//Texture_IDArray_5x2.Emplace("m5x2_015");
	//Texture_IDArray_5x2.Emplace("m5x2_016");
	//Texture_IDArray_5x2.Emplace("m5x2_017");
	//Texture_IDArray_5x2.Emplace("m5x2_018");
	//Texture_IDArray_5x2.Emplace("m5x2_019");

	//Texture_IDArray_5x2.Emplace("m5x2_020");
	//Texture_IDArray_5x2.Emplace("m5x2_021");
	//Texture_IDArray_5x2.Emplace("m5x2_022");
	//Texture_IDArray_5x2.Emplace("m5x2_023");
	//Texture_IDArray_5x2.Emplace("m5x2_024");
	//Texture_IDArray_5x2.Emplace("m5x2_025");
	//Texture_IDArray_5x2.Emplace("m5x2_026");
	//Texture_IDArray_5x2.Emplace("m5x2_027");
	//Texture_IDArray_5x2.Emplace("m5x2_028");
	//Texture_IDArray_5x2.Emplace("m5x2_029");

}


void UMuralManager::FindAllMuralTextures_4x4()
{
	TextureMap.Emplace("m4x4_001", FindAsset("Texture'/Game/Murals/4x4/m4x4_001.m4x4_001'"));
	TextureMap.Emplace("m4x4_002", FindAsset("Texture'/Game/Murals/4x4/m4x4_002.m4x4_002'"));
	TextureMap.Emplace("m4x4_003", FindAsset("Texture'/Game/Murals/4x4/m4x4_003.m4x4_003'"));
	TextureMap.Emplace("m4x4_004", FindAsset("Texture'/Game/Murals/4x4/m4x4_004.m4x4_004'"));
	TextureMap.Emplace("m4x4_005", FindAsset("Texture'/Game/Murals/4x4/m4x4_005.m4x4_005'"));
	TextureMap.Emplace("m4x4_006", FindAsset("Texture'/Game/Murals/4x4/m4x4_006.m4x4_006'"));
	TextureMap.Emplace("m4x4_007", FindAsset("Texture'/Game/Murals/4x4/m4x4_007.m4x4_007'"));
	TextureMap.Emplace("m4x4_008", FindAsset("Texture'/Game/Murals/4x4/m4x4_008.m4x4_008'"));
	TextureMap.Emplace("m4x4_009", FindAsset("Texture'/Game/Murals/4x4/m4x4_009.m4x4_009'"));

	TextureMap.Emplace("m4x4_010", FindAsset("Texture'/Game/Murals/4x4/m4x4_010.m4x4_010'"));
	TextureMap.Emplace("m4x4_011", FindAsset("Texture'/Game/Murals/4x4/m4x4_011.m4x4_011'"));
	TextureMap.Emplace("m4x4_012", FindAsset("Texture'/Game/Murals/4x4/m4x4_012.m4x4_012'"));
	//TextureMap.Emplace("m4x4_013", FindAsset("Texture'/Game/Murals/4x4/m4x4_013.m4x4_013'"));
	//TextureMap.Emplace("m4x4_014", FindAsset("Texture'/Game/Murals/4x4/m4x4_014.m4x4_014'"));
	//TextureMap.Emplace("m4x4_015", FindAsset("Texture'/Game/Murals/4x4/m4x4_015.m4x4_015'"));
	//TextureMap.Emplace("m4x4_016", FindAsset("Texture'/Game/Murals/4x4/m4x4_016.m4x4_016'"));
	//TextureMap.Emplace("m4x4_017", FindAsset("Texture'/Game/Murals/4x4/m4x4_017.m4x4_017'"));
	//TextureMap.Emplace("m4x4_018", FindAsset("Texture'/Game/Murals/4x4/m4x4_018.m4x4_018'"));
	//TextureMap.Emplace("m4x4_019", FindAsset("Texture'/Game/Murals/4x4/m4x4_019.m4x4_019'"));

	//TextureMap.Emplace("m4x4_020", FindAsset("Texture'/Game/Murals/4x4/m4x4_020.m4x4_020'"));
	//TextureMap.Emplace("m4x4_021", FindAsset("Texture'/Game/Murals/4x4/m4x4_021.m4x4_021'"));
	//TextureMap.Emplace("m4x4_022", FindAsset("Texture'/Game/Murals/4x4/m4x4_022.m4x4_022'"));
	//TextureMap.Emplace("m4x4_023", FindAsset("Texture'/Game/Murals/4x4/m4x4_023.m4x4_023'"));
	//TextureMap.Emplace("m4x4_024", FindAsset("Texture'/Game/Murals/4x4/m4x4_024.m4x4_024'"));
	//TextureMap.Emplace("m4x4_025", FindAsset("Texture'/Game/Murals/4x4/m4x4_025.m4x4_025'"));
	//TextureMap.Emplace("m4x4_026", FindAsset("Texture'/Game/Murals/4x4/m4x4_026.m4x4_026'"));
	//TextureMap.Emplace("m4x4_027", FindAsset("Texture'/Game/Murals/4x4/m4x4_027.m4x4_027'"));
	//TextureMap.Emplace("m4x4_028", FindAsset("Texture'/Game/Murals/4x4/m4x4_028.m4x4_028'"));
	//TextureMap.Emplace("m4x4_029", FindAsset("Texture'/Game/Murals/4x4/m4x4_029.m4x4_029'"));


	Texture_IDArray_4x4.Emplace("m4x4_001");
	Texture_IDArray_4x4.Emplace("m4x4_002");
	Texture_IDArray_4x4.Emplace("m4x4_003");
	Texture_IDArray_4x4.Emplace("m4x4_004");
	Texture_IDArray_4x4.Emplace("m4x4_005");
	Texture_IDArray_4x4.Emplace("m4x4_006");
	Texture_IDArray_4x4.Emplace("m4x4_007");
	Texture_IDArray_4x4.Emplace("m4x4_008");
	Texture_IDArray_4x4.Emplace("m4x4_009");

	Texture_IDArray_4x4.Emplace("m4x4_010");
	Texture_IDArray_4x4.Emplace("m4x4_011");
	Texture_IDArray_4x4.Emplace("m4x4_012");
	//Texture_IDArray_4x4.Emplace("m4x4_013");
	//Texture_IDArray_4x4.Emplace("m4x4_014");
	//Texture_IDArray_4x4.Emplace("m4x4_015");
	//Texture_IDArray_4x4.Emplace("m4x4_016");
	//Texture_IDArray_4x4.Emplace("m4x4_017");
	//Texture_IDArray_4x4.Emplace("m4x4_018");
	//Texture_IDArray_4x4.Emplace("m4x4_019");

	//Texture_IDArray_4x4.Emplace("m4x4_020");
	//Texture_IDArray_4x4.Emplace("m4x4_021");
	//Texture_IDArray_4x4.Emplace("m4x4_022");
	//Texture_IDArray_4x4.Emplace("m4x4_023");
	//Texture_IDArray_4x4.Emplace("m4x4_024");
	//Texture_IDArray_4x4.Emplace("m4x4_025");
	//Texture_IDArray_4x4.Emplace("m4x4_026");
	//Texture_IDArray_4x4.Emplace("m4x4_027");
	//Texture_IDArray_4x4.Emplace("m4x4_028");
	//Texture_IDArray_4x4.Emplace("m4x4_029");

}

void UMuralManager::FindAllMuralTextures_4x3()
{
	TextureMap.Emplace("m4x3_001", FindAsset("Texture'/Game/Murals/4x3/m4x3_001.m4x3_001'"));
	TextureMap.Emplace("m4x3_002", FindAsset("Texture'/Game/Murals/4x3/m4x3_002.m4x3_002'"));
	TextureMap.Emplace("m4x3_003", FindAsset("Texture'/Game/Murals/4x3/m4x3_003.m4x3_003'"));
	TextureMap.Emplace("m4x3_004", FindAsset("Texture'/Game/Murals/4x3/m4x3_004.m4x3_004'"));
	TextureMap.Emplace("m4x3_005", FindAsset("Texture'/Game/Murals/4x3/m4x3_005.m4x3_005'"));
	TextureMap.Emplace("m4x3_006", FindAsset("Texture'/Game/Murals/4x3/m4x3_006.m4x3_006'"));
	TextureMap.Emplace("m4x3_007", FindAsset("Texture'/Game/Murals/4x3/m4x3_007.m4x3_007'"));
	TextureMap.Emplace("m4x3_008", FindAsset("Texture'/Game/Murals/4x3/m4x3_008.m4x3_008'"));
	TextureMap.Emplace("m4x3_009", FindAsset("Texture'/Game/Murals/4x3/m4x3_009.m4x3_009'"));

	TextureMap.Emplace("m4x3_010", FindAsset("Texture'/Game/Murals/4x3/m4x3_010.m4x3_010'"));
	TextureMap.Emplace("m4x3_011", FindAsset("Texture'/Game/Murals/4x3/m4x3_011.m4x3_011'"));
	//TextureMap.Emplace("m4x3_012", FindAsset("Texture'/Game/Murals/4x3/m4x3_012.m4x3_012'"));
	//TextureMap.Emplace("m4x3_013", FindAsset("Texture'/Game/Murals/4x3/m4x3_013.m4x3_013'"));
	//TextureMap.Emplace("m4x3_014", FindAsset("Texture'/Game/Murals/4x3/m4x3_014.m4x3_014'"));
	//TextureMap.Emplace("m4x3_015", FindAsset("Texture'/Game/Murals/4x3/m4x3_015.m4x3_015'"));
	//TextureMap.Emplace("m4x3_016", FindAsset("Texture'/Game/Murals/4x3/m4x3_016.m4x3_016'"));
	//TextureMap.Emplace("m4x3_017", FindAsset("Texture'/Game/Murals/4x3/m4x3_017.m4x3_017'"));
	//TextureMap.Emplace("m4x3_018", FindAsset("Texture'/Game/Murals/4x3/m4x3_018.m4x3_018'"));
	//TextureMap.Emplace("m4x3_019", FindAsset("Texture'/Game/Murals/4x3/m4x3_019.m4x3_019'"));

	//TextureMap.Emplace("m4x3_020", FindAsset("Texture'/Game/Murals/4x3/m4x3_020.m4x3_020'"));
	//TextureMap.Emplace("m4x3_021", FindAsset("Texture'/Game/Murals/4x3/m4x3_021.m4x3_021'"));
	//TextureMap.Emplace("m4x3_022", FindAsset("Texture'/Game/Murals/4x3/m4x3_022.m4x3_022'"));
	//TextureMap.Emplace("m4x3_023", FindAsset("Texture'/Game/Murals/4x3/m4x3_023.m4x3_023'"));
	//TextureMap.Emplace("m4x3_024", FindAsset("Texture'/Game/Murals/4x3/m4x3_024.m4x3_024'"));
	//TextureMap.Emplace("m4x3_025", FindAsset("Texture'/Game/Murals/4x3/m4x3_025.m4x3_025'"));
	//TextureMap.Emplace("m4x3_026", FindAsset("Texture'/Game/Murals/4x3/m4x3_026.m4x3_026'"));
	//TextureMap.Emplace("m4x3_027", FindAsset("Texture'/Game/Murals/4x3/m4x3_027.m4x3_027'"));
	//TextureMap.Emplace("m4x3_028", FindAsset("Texture'/Game/Murals/4x3/m4x3_028.m4x3_028'"));
	//TextureMap.Emplace("m4x3_029", FindAsset("Texture'/Game/Murals/4x3/m4x3_029.m4x3_029'"));


	Texture_IDArray_4x3.Emplace("m4x3_001");
	Texture_IDArray_4x3.Emplace("m4x3_002");
	Texture_IDArray_4x3.Emplace("m4x3_003");
	Texture_IDArray_4x3.Emplace("m4x3_004");
	Texture_IDArray_4x3.Emplace("m4x3_005");
	Texture_IDArray_4x3.Emplace("m4x3_006");
	Texture_IDArray_4x3.Emplace("m4x3_007");
	Texture_IDArray_4x3.Emplace("m4x3_008");
	Texture_IDArray_4x3.Emplace("m4x3_009");

	Texture_IDArray_4x3.Emplace("m4x3_010");
	Texture_IDArray_4x3.Emplace("m4x3_011");
	//Texture_IDArray_4x3.Emplace("m4x3_012");
	//Texture_IDArray_4x3.Emplace("m4x3_013");
	//Texture_IDArray_4x3.Emplace("m4x3_014");
	//Texture_IDArray_4x3.Emplace("m4x3_015");
	//Texture_IDArray_4x3.Emplace("m4x3_016");
	//Texture_IDArray_4x3.Emplace("m4x3_017");
	//Texture_IDArray_4x3.Emplace("m4x3_018");
	//Texture_IDArray_4x3.Emplace("m4x3_019");

	//Texture_IDArray_4x3.Emplace("m4x3_020");
	//Texture_IDArray_4x3.Emplace("m4x3_021");
	//Texture_IDArray_4x3.Emplace("m4x3_022");
	//Texture_IDArray_4x3.Emplace("m4x3_023");
	//Texture_IDArray_4x3.Emplace("m4x3_024");
	//Texture_IDArray_4x3.Emplace("m4x3_025");
	//Texture_IDArray_4x3.Emplace("m4x3_026");
	//Texture_IDArray_4x3.Emplace("m4x3_027");
	//Texture_IDArray_4x3.Emplace("m4x3_028");
	//Texture_IDArray_4x3.Emplace("m4x3_029");

}

void UMuralManager::FindAllMuralTextures_4x2()
{
	TextureMap.Emplace("m4x2_001", FindAsset("Texture'/Game/Murals/4x2/m4x2_001.m4x2_001'"));
	TextureMap.Emplace("m4x2_002", FindAsset("Texture'/Game/Murals/4x2/m4x2_002.m4x2_002'"));
	TextureMap.Emplace("m4x2_003", FindAsset("Texture'/Game/Murals/4x2/m4x2_003.m4x2_003'"));
	TextureMap.Emplace("m4x2_004", FindAsset("Texture'/Game/Murals/4x2/m4x2_004.m4x2_004'"));
	TextureMap.Emplace("m4x2_005", FindAsset("Texture'/Game/Murals/4x2/m4x2_005.m4x2_005'"));
	TextureMap.Emplace("m4x2_006", FindAsset("Texture'/Game/Murals/4x2/m4x2_006.m4x2_006'"));
	TextureMap.Emplace("m4x2_007", FindAsset("Texture'/Game/Murals/4x2/m4x2_007.m4x2_007'"));
	TextureMap.Emplace("m4x2_008", FindAsset("Texture'/Game/Murals/4x2/m4x2_008.m4x2_008'"));
	TextureMap.Emplace("m4x2_009", FindAsset("Texture'/Game/Murals/4x2/m4x2_009.m4x2_009'"));

	TextureMap.Emplace("m4x2_010", FindAsset("Texture'/Game/Murals/4x2/m4x2_010.m4x2_010'"));
	TextureMap.Emplace("m4x2_011", FindAsset("Texture'/Game/Murals/4x2/m4x2_011.m4x2_011'"));
	//TextureMap.Emplace("m4x2_012", FindAsset("Texture'/Game/Murals/4x2/m4x2_012.m4x2_012'"));
	//TextureMap.Emplace("m4x2_013", FindAsset("Texture'/Game/Murals/4x2/m4x2_013.m4x2_013'"));
	//TextureMap.Emplace("m4x2_014", FindAsset("Texture'/Game/Murals/4x2/m4x2_014.m4x2_014'"));
	//TextureMap.Emplace("m4x2_015", FindAsset("Texture'/Game/Murals/4x2/m4x2_015.m4x2_015'"));
	//TextureMap.Emplace("m4x2_016", FindAsset("Texture'/Game/Murals/4x2/m4x2_016.m4x2_016'"));
	//TextureMap.Emplace("m4x2_017", FindAsset("Texture'/Game/Murals/4x2/m4x2_017.m4x2_017'"));
	//TextureMap.Emplace("m4x2_018", FindAsset("Texture'/Game/Murals/4x2/m4x2_018.m4x2_018'"));
	//TextureMap.Emplace("m4x2_019", FindAsset("Texture'/Game/Murals/4x2/m4x2_019.m4x2_019'"));

	//TextureMap.Emplace("m4x2_020", FindAsset("Texture'/Game/Murals/4x2/m4x2_020.m4x2_020'"));
	//TextureMap.Emplace("m4x2_021", FindAsset("Texture'/Game/Murals/4x2/m4x2_021.m4x2_021'"));
	//TextureMap.Emplace("m4x2_022", FindAsset("Texture'/Game/Murals/4x2/m4x2_022.m4x2_022'"));
	//TextureMap.Emplace("m4x2_023", FindAsset("Texture'/Game/Murals/4x2/m4x2_023.m4x2_023'"));
	//TextureMap.Emplace("m4x2_024", FindAsset("Texture'/Game/Murals/4x2/m4x2_024.m4x2_024'"));
	//TextureMap.Emplace("m4x2_025", FindAsset("Texture'/Game/Murals/4x2/m4x2_025.m4x2_025'"));
	//TextureMap.Emplace("m4x2_026", FindAsset("Texture'/Game/Murals/4x2/m4x2_026.m4x2_026'"));
	//TextureMap.Emplace("m4x2_027", FindAsset("Texture'/Game/Murals/4x2/m4x2_027.m4x2_027'"));
	//TextureMap.Emplace("m4x2_028", FindAsset("Texture'/Game/Murals/4x2/m4x2_028.m4x2_028'"));
	//TextureMap.Emplace("m4x2_029", FindAsset("Texture'/Game/Murals/4x2/m4x2_029.m4x2_029'"));


	Texture_IDArray_4x2.Emplace("m4x2_001");
	Texture_IDArray_4x2.Emplace("m4x2_002");
	Texture_IDArray_4x2.Emplace("m4x2_003");
	Texture_IDArray_4x2.Emplace("m4x2_004");
	Texture_IDArray_4x2.Emplace("m4x2_005");
	Texture_IDArray_4x2.Emplace("m4x2_006");
	Texture_IDArray_4x2.Emplace("m4x2_007");
	Texture_IDArray_4x2.Emplace("m4x2_008");
	Texture_IDArray_4x2.Emplace("m4x2_009");

	Texture_IDArray_4x2.Emplace("m4x2_010");
	Texture_IDArray_4x2.Emplace("m4x2_011");
	//Texture_IDArray_4x2.Emplace("m4x2_012");
	//Texture_IDArray_4x2.Emplace("m4x2_013");
	//Texture_IDArray_4x2.Emplace("m4x2_014");
	//Texture_IDArray_4x2.Emplace("m4x2_015");
	//Texture_IDArray_4x2.Emplace("m4x2_016");
	//Texture_IDArray_4x2.Emplace("m4x2_017");
	//Texture_IDArray_4x2.Emplace("m4x2_018");
	//Texture_IDArray_4x2.Emplace("m4x2_019");

	//Texture_IDArray_4x2.Emplace("m4x2_020");
	//Texture_IDArray_4x2.Emplace("m4x2_021");
	//Texture_IDArray_4x2.Emplace("m4x2_022");
	//Texture_IDArray_4x2.Emplace("m4x2_023");
	//Texture_IDArray_4x2.Emplace("m4x2_024");
	//Texture_IDArray_4x2.Emplace("m4x2_025");
	//Texture_IDArray_4x2.Emplace("m4x2_026");
	//Texture_IDArray_4x2.Emplace("m4x2_027");
	//Texture_IDArray_4x2.Emplace("m4x2_028");
	//Texture_IDArray_4x2.Emplace("m4x2_029");

}


void UMuralManager::FindAllMuralTextures_3x4()
{
	TextureMap.Emplace("m3x4_001", FindAsset("Texture'/Game/Murals/3x4/m3x4_001.m3x4_001'"));
	TextureMap.Emplace("m3x4_002", FindAsset("Texture'/Game/Murals/3x4/m3x4_002.m3x4_002'"));
	TextureMap.Emplace("m3x4_003", FindAsset("Texture'/Game/Murals/3x4/m3x4_003.m3x4_003'"));
	TextureMap.Emplace("m3x4_004", FindAsset("Texture'/Game/Murals/3x4/m3x4_004.m3x4_004'"));
	TextureMap.Emplace("m3x4_005", FindAsset("Texture'/Game/Murals/3x4/m3x4_005.m3x4_005'"));
	TextureMap.Emplace("m3x4_006", FindAsset("Texture'/Game/Murals/3x4/m3x4_006.m3x4_006'"));
	TextureMap.Emplace("m3x4_007", FindAsset("Texture'/Game/Murals/3x4/m3x4_007.m3x4_007'"));
	TextureMap.Emplace("m3x4_008", FindAsset("Texture'/Game/Murals/3x4/m3x4_008.m3x4_008'"));
	TextureMap.Emplace("m3x4_009", FindAsset("Texture'/Game/Murals/3x4/m3x4_009.m3x4_009'"));

	TextureMap.Emplace("m3x4_010", FindAsset("Texture'/Game/Murals/3x4/m3x4_010.m3x4_010'"));
	TextureMap.Emplace("m3x4_011", FindAsset("Texture'/Game/Murals/3x4/m3x4_011.m3x4_011'"));
	//TextureMap.Emplace("m3x4_012", FindAsset("Texture'/Game/Murals/3x4/m3x4_012.m3x4_012'"));
	//TextureMap.Emplace("m3x4_013", FindAsset("Texture'/Game/Murals/3x4/m3x4_013.m3x4_013'"));
	//TextureMap.Emplace("m3x4_014", FindAsset("Texture'/Game/Murals/3x4/m3x4_014.m3x4_014'"));
	//TextureMap.Emplace("m3x4_015", FindAsset("Texture'/Game/Murals/3x4/m3x4_015.m3x4_015'"));
	//TextureMap.Emplace("m3x4_016", FindAsset("Texture'/Game/Murals/3x4/m3x4_016.m3x4_016'"));
	//TextureMap.Emplace("m3x4_017", FindAsset("Texture'/Game/Murals/3x4/m3x4_017.m3x4_017'"));
	//TextureMap.Emplace("m3x4_018", FindAsset("Texture'/Game/Murals/3x4/m3x4_018.m3x4_018'"));
	//TextureMap.Emplace("m3x4_019", FindAsset("Texture'/Game/Murals/3x4/m3x4_019.m3x4_019'"));

	//TextureMap.Emplace("m3x4_020", FindAsset("Texture'/Game/Murals/3x4/m3x4_020.m3x4_020'"));
	//TextureMap.Emplace("m3x4_021", FindAsset("Texture'/Game/Murals/3x4/m3x4_021.m3x4_021'"));
	//TextureMap.Emplace("m3x4_022", FindAsset("Texture'/Game/Murals/3x4/m3x4_022.m3x4_022'"));
	//TextureMap.Emplace("m3x4_023", FindAsset("Texture'/Game/Murals/3x4/m3x4_023.m3x4_023'"));
	//TextureMap.Emplace("m3x4_024", FindAsset("Texture'/Game/Murals/3x4/m3x4_024.m3x4_024'"));
	//TextureMap.Emplace("m3x4_025", FindAsset("Texture'/Game/Murals/3x4/m3x4_025.m3x4_025'"));
	//TextureMap.Emplace("m3x4_026", FindAsset("Texture'/Game/Murals/3x4/m3x4_026.m3x4_026'"));
	//TextureMap.Emplace("m3x4_027", FindAsset("Texture'/Game/Murals/3x4/m3x4_027.m3x4_027'"));
	//TextureMap.Emplace("m3x4_028", FindAsset("Texture'/Game/Murals/3x4/m3x4_028.m3x4_028'"));
	//TextureMap.Emplace("m3x4_029", FindAsset("Texture'/Game/Murals/3x4/m3x4_029.m3x4_029'"));


	Texture_IDArray_3x4.Emplace("m3x4_001");
	Texture_IDArray_3x4.Emplace("m3x4_002");
	Texture_IDArray_3x4.Emplace("m3x4_003");
	Texture_IDArray_3x4.Emplace("m3x4_004");
	Texture_IDArray_3x4.Emplace("m3x4_005");
	Texture_IDArray_3x4.Emplace("m3x4_006");
	Texture_IDArray_3x4.Emplace("m3x4_007");
	Texture_IDArray_3x4.Emplace("m3x4_008");
	Texture_IDArray_3x4.Emplace("m3x4_009");

	Texture_IDArray_3x4.Emplace("m3x4_010");
	Texture_IDArray_3x4.Emplace("m3x4_011");
	//Texture_IDArray_3x4.Emplace("m3x4_012");
	//Texture_IDArray_3x4.Emplace("m3x4_013");
	//Texture_IDArray_3x4.Emplace("m3x4_014");
	//Texture_IDArray_3x4.Emplace("m3x4_015");
	//Texture_IDArray_3x4.Emplace("m3x4_016");
	//Texture_IDArray_3x4.Emplace("m3x4_017");
	//Texture_IDArray_3x4.Emplace("m3x4_018");
	//Texture_IDArray_3x4.Emplace("m3x4_019");

	//Texture_IDArray_3x4.Emplace("m3x4_020");
	//Texture_IDArray_3x4.Emplace("m3x4_021");
	//Texture_IDArray_3x4.Emplace("m3x4_022");
	//Texture_IDArray_3x4.Emplace("m3x4_023");
	//Texture_IDArray_3x4.Emplace("m3x4_024");
	//Texture_IDArray_3x4.Emplace("m3x4_025");
	//Texture_IDArray_3x4.Emplace("m3x4_026");
	//Texture_IDArray_3x4.Emplace("m3x4_027");
	//Texture_IDArray_3x4.Emplace("m3x4_028");
	//Texture_IDArray_3x4.Emplace("m3x4_029");
}

void UMuralManager::FindAllMuralTextures_3x3()
{
	TextureMap.Emplace("m3x3_001", FindAsset("Texture'/Game/Murals/3x3/m3x3_001.m3x3_001'"));
	TextureMap.Emplace("m3x3_002", FindAsset("Texture'/Game/Murals/3x3/m3x3_002.m3x3_002'"));
	TextureMap.Emplace("m3x3_003", FindAsset("Texture'/Game/Murals/3x3/m3x3_003.m3x3_003'"));
	TextureMap.Emplace("m3x3_004", FindAsset("Texture'/Game/Murals/3x3/m3x3_004.m3x3_004'"));
	TextureMap.Emplace("m3x3_005", FindAsset("Texture'/Game/Murals/3x3/m3x3_005.m3x3_005'"));
	TextureMap.Emplace("m3x3_006", FindAsset("Texture'/Game/Murals/3x3/m3x3_006.m3x3_006'"));
	TextureMap.Emplace("m3x3_007", FindAsset("Texture'/Game/Murals/3x3/m3x3_007.m3x3_007'"));
	TextureMap.Emplace("m3x3_008", FindAsset("Texture'/Game/Murals/3x3/m3x3_008.m3x3_008'"));
	TextureMap.Emplace("m3x3_009", FindAsset("Texture'/Game/Murals/3x3/m3x3_009.m3x3_009'"));

	TextureMap.Emplace("m3x3_010", FindAsset("Texture'/Game/Murals/3x3/m3x3_010.m3x3_010'"));
	TextureMap.Emplace("m3x3_011", FindAsset("Texture'/Game/Murals/3x3/m3x3_011.m3x3_011'"));
	//TextureMap.Emplace("m3x3_012", FindAsset("Texture'/Game/Murals/3x3/m3x3_012.m3x3_012'"));
	//TextureMap.Emplace("m3x3_013", FindAsset("Texture'/Game/Murals/3x3/m3x3_013.m3x3_013'"));
	//TextureMap.Emplace("m3x3_014", FindAsset("Texture'/Game/Murals/3x3/m3x3_014.m3x3_014'"));
	//TextureMap.Emplace("m3x3_015", FindAsset("Texture'/Game/Murals/3x3/m3x3_015.m3x3_015'"));
	//TextureMap.Emplace("m3x3_016", FindAsset("Texture'/Game/Murals/3x3/m3x3_016.m3x3_016'"));
	//TextureMap.Emplace("m3x3_017", FindAsset("Texture'/Game/Murals/3x3/m3x3_017.m3x3_017'"));
	//TextureMap.Emplace("m3x3_018", FindAsset("Texture'/Game/Murals/3x3/m3x3_018.m3x3_018'"));
	//TextureMap.Emplace("m3x3_019", FindAsset("Texture'/Game/Murals/3x3/m3x3_019.m3x3_019'"));

	//TextureMap.Emplace("m3x3_020", FindAsset("Texture'/Game/Murals/3x3/m3x3_020.m3x3_020'"));
	//TextureMap.Emplace("m3x3_021", FindAsset("Texture'/Game/Murals/3x3/m3x3_021.m3x3_021'"));
	//TextureMap.Emplace("m3x3_022", FindAsset("Texture'/Game/Murals/3x3/m3x3_022.m3x3_022'"));
	//TextureMap.Emplace("m3x3_023", FindAsset("Texture'/Game/Murals/3x3/m3x3_023.m3x3_023'"));
	//TextureMap.Emplace("m3x3_024", FindAsset("Texture'/Game/Murals/3x3/m3x3_024.m3x3_024'"));
	//TextureMap.Emplace("m3x3_025", FindAsset("Texture'/Game/Murals/3x3/m3x3_025.m3x3_025'"));
	//TextureMap.Emplace("m3x3_026", FindAsset("Texture'/Game/Murals/3x3/m3x3_026.m3x3_026'"));
	//TextureMap.Emplace("m3x3_027", FindAsset("Texture'/Game/Murals/3x3/m3x3_027.m3x3_027'"));
	//TextureMap.Emplace("m3x3_028", FindAsset("Texture'/Game/Murals/3x3/m3x3_028.m3x3_028'"));
	//TextureMap.Emplace("m3x3_029", FindAsset("Texture'/Game/Murals/3x3/m3x3_029.m3x3_029'"));


	Texture_IDArray_3x3.Emplace("m3x3_001");
	Texture_IDArray_3x3.Emplace("m3x3_002");
	Texture_IDArray_3x3.Emplace("m3x3_003");
	Texture_IDArray_3x3.Emplace("m3x3_004");
	Texture_IDArray_3x3.Emplace("m3x3_005");
	Texture_IDArray_3x3.Emplace("m3x3_006");
	Texture_IDArray_3x3.Emplace("m3x3_007");
	Texture_IDArray_3x3.Emplace("m3x3_008");
	Texture_IDArray_3x3.Emplace("m3x3_009");

	Texture_IDArray_3x3.Emplace("m3x3_010");
	Texture_IDArray_3x3.Emplace("m3x3_011");
	//Texture_IDArray_3x3.Emplace("m3x3_012");
	//Texture_IDArray_3x3.Emplace("m3x3_013");
	//Texture_IDArray_3x3.Emplace("m3x3_014");
	//Texture_IDArray_3x3.Emplace("m3x3_015");
	//Texture_IDArray_3x3.Emplace("m3x3_016");
	//Texture_IDArray_3x3.Emplace("m3x3_017");
	//Texture_IDArray_3x3.Emplace("m3x3_018");
	//Texture_IDArray_3x3.Emplace("m3x3_019");

	//Texture_IDArray_3x3.Emplace("m3x3_020");
	//Texture_IDArray_3x3.Emplace("m3x3_021");
	//Texture_IDArray_3x3.Emplace("m3x3_022");
	//Texture_IDArray_3x3.Emplace("m3x3_023");
	//Texture_IDArray_3x3.Emplace("m3x3_024");
	//Texture_IDArray_3x3.Emplace("m3x3_025");
	//Texture_IDArray_3x3.Emplace("m3x3_026");
	//Texture_IDArray_3x3.Emplace("m3x3_027");
	//Texture_IDArray_3x3.Emplace("m3x3_028");
	//Texture_IDArray_3x3.Emplace("m3x3_029");

}

void UMuralManager::FindAllMuralTextures_3x2()
{
	TextureMap.Emplace("m3x2_001", FindAsset("Texture'/Game/Murals/3x2/m3x2_001.m3x2_001'"));
	TextureMap.Emplace("m3x2_002", FindAsset("Texture'/Game/Murals/3x2/m3x2_002.m3x2_002'"));
	TextureMap.Emplace("m3x2_003", FindAsset("Texture'/Game/Murals/3x2/m3x2_003.m3x2_003'"));
	TextureMap.Emplace("m3x2_004", FindAsset("Texture'/Game/Murals/3x2/m3x2_004.m3x2_004'"));
	TextureMap.Emplace("m3x2_005", FindAsset("Texture'/Game/Murals/3x2/m3x2_005.m3x2_005'"));
	TextureMap.Emplace("m3x2_006", FindAsset("Texture'/Game/Murals/3x2/m3x2_006.m3x2_006'"));
	TextureMap.Emplace("m3x2_007", FindAsset("Texture'/Game/Murals/3x2/m3x2_007.m3x2_007'"));
	TextureMap.Emplace("m3x2_008", FindAsset("Texture'/Game/Murals/3x2/m3x2_008.m3x2_008'"));
	TextureMap.Emplace("m3x2_009", FindAsset("Texture'/Game/Murals/3x2/m3x2_009.m3x2_009'"));

	TextureMap.Emplace("m3x2_010", FindAsset("Texture'/Game/Murals/3x2/m3x2_010.m3x2_010'"));
	TextureMap.Emplace("m3x2_011", FindAsset("Texture'/Game/Murals/3x2/m3x2_011.m3x2_011'"));
	//TextureMap.Emplace("m3x2_012", FindAsset("Texture'/Game/Murals/3x2/m3x2_012.m3x2_012'"));
	//TextureMap.Emplace("m3x2_013", FindAsset("Texture'/Game/Murals/3x2/m3x2_013.m3x2_013'"));
	//TextureMap.Emplace("m3x2_014", FindAsset("Texture'/Game/Murals/3x2/m3x2_014.m3x2_014'"));
	//TextureMap.Emplace("m3x2_015", FindAsset("Texture'/Game/Murals/3x2/m3x2_015.m3x2_015'"));
	//TextureMap.Emplace("m3x2_016", FindAsset("Texture'/Game/Murals/3x2/m3x2_016.m3x2_016'"));
	//TextureMap.Emplace("m3x2_017", FindAsset("Texture'/Game/Murals/3x2/m3x2_017.m3x2_017'"));
	//TextureMap.Emplace("m3x2_018", FindAsset("Texture'/Game/Murals/3x2/m3x2_018.m3x2_018'"));
	//TextureMap.Emplace("m3x2_019", FindAsset("Texture'/Game/Murals/3x2/m3x2_019.m3x2_019'"));

	//TextureMap.Emplace("m3x2_020", FindAsset("Texture'/Game/Murals/3x2/m3x2_020.m3x2_020'"));
	//TextureMap.Emplace("m3x2_021", FindAsset("Texture'/Game/Murals/3x2/m3x2_021.m3x2_021'"));
	//TextureMap.Emplace("m3x2_022", FindAsset("Texture'/Game/Murals/3x2/m3x2_022.m3x2_022'"));
	//TextureMap.Emplace("m3x2_023", FindAsset("Texture'/Game/Murals/3x2/m3x2_023.m3x2_023'"));
	//TextureMap.Emplace("m3x2_024", FindAsset("Texture'/Game/Murals/3x2/m3x2_024.m3x2_024'"));
	//TextureMap.Emplace("m3x2_025", FindAsset("Texture'/Game/Murals/3x2/m3x2_025.m3x2_025'"));
	//TextureMap.Emplace("m3x2_026", FindAsset("Texture'/Game/Murals/3x2/m3x2_026.m3x2_026'"));
	//TextureMap.Emplace("m3x2_027", FindAsset("Texture'/Game/Murals/3x2/m3x2_027.m3x2_027'"));
	//TextureMap.Emplace("m3x2_028", FindAsset("Texture'/Game/Murals/3x2/m3x2_028.m3x2_028'"));
	//TextureMap.Emplace("m3x2_029", FindAsset("Texture'/Game/Murals/3x2/m3x2_029.m3x2_029'"));


	Texture_IDArray_3x2.Emplace("m3x2_001");
	Texture_IDArray_3x2.Emplace("m3x2_002");
	Texture_IDArray_3x2.Emplace("m3x2_003");
	Texture_IDArray_3x2.Emplace("m3x2_004");
	Texture_IDArray_3x2.Emplace("m3x2_005");
	Texture_IDArray_3x2.Emplace("m3x2_006");
	Texture_IDArray_3x2.Emplace("m3x2_007");
	Texture_IDArray_3x2.Emplace("m3x2_008");
	Texture_IDArray_3x2.Emplace("m3x2_009");

	Texture_IDArray_3x2.Emplace("m3x2_010");
	Texture_IDArray_3x2.Emplace("m3x2_011");
	//Texture_IDArray_3x2.Emplace("m3x2_012");
	//Texture_IDArray_3x2.Emplace("m3x2_013");
	//Texture_IDArray_3x2.Emplace("m3x2_014");
	//Texture_IDArray_3x2.Emplace("m3x2_015");
	//Texture_IDArray_3x2.Emplace("m3x2_016");
	//Texture_IDArray_3x2.Emplace("m3x2_017");
	//Texture_IDArray_3x2.Emplace("m3x2_018");
	//Texture_IDArray_3x2.Emplace("m3x2_019");

	//Texture_IDArray_3x2.Emplace("m3x2_020");
	//Texture_IDArray_3x2.Emplace("m3x2_021");
	//Texture_IDArray_3x2.Emplace("m3x2_022");
	//Texture_IDArray_3x2.Emplace("m3x2_023");
	//Texture_IDArray_3x2.Emplace("m3x2_024");
	//Texture_IDArray_3x2.Emplace("m3x2_025");
	//Texture_IDArray_3x2.Emplace("m3x2_026");
	//Texture_IDArray_3x2.Emplace("m3x2_027");
	//Texture_IDArray_3x2.Emplace("m3x2_028");
	//Texture_IDArray_3x2.Emplace("m3x2_029");
}


void UMuralManager::FindAllMuralTextures_2x4()
{
	TextureMap.Emplace("m2x4_001", FindAsset("Texture'/Game/Murals/2x4/m2x4_001.m2x4_001'"));
	TextureMap.Emplace("m2x4_002", FindAsset("Texture'/Game/Murals/2x4/m2x4_002.m2x4_002'"));
	TextureMap.Emplace("m2x4_003", FindAsset("Texture'/Game/Murals/2x4/m2x4_003.m2x4_003'"));
	TextureMap.Emplace("m2x4_004", FindAsset("Texture'/Game/Murals/2x4/m2x4_004.m2x4_004'"));
	TextureMap.Emplace("m2x4_005", FindAsset("Texture'/Game/Murals/2x4/m2x4_005.m2x4_005'"));
	TextureMap.Emplace("m2x4_006", FindAsset("Texture'/Game/Murals/2x4/m2x4_006.m2x4_006'"));
	TextureMap.Emplace("m2x4_007", FindAsset("Texture'/Game/Murals/2x4/m2x4_007.m2x4_007'"));
	TextureMap.Emplace("m2x4_008", FindAsset("Texture'/Game/Murals/2x4/m2x4_008.m2x4_008'"));
	TextureMap.Emplace("m2x4_009", FindAsset("Texture'/Game/Murals/2x4/m2x4_009.m2x4_009'"));

	TextureMap.Emplace("m2x4_010", FindAsset("Texture'/Game/Murals/2x4/m2x4_010.m2x4_010'"));
	TextureMap.Emplace("m2x4_011", FindAsset("Texture'/Game/Murals/2x4/m2x4_011.m2x4_011'"));
	//TextureMap.Emplace("m2x4_012", FindAsset("Texture'/Game/Murals/2x4/m2x4_012.m2x4_012'"));
	//TextureMap.Emplace("m2x4_013", FindAsset("Texture'/Game/Murals/2x4/m2x4_013.m2x4_013'"));
	//TextureMap.Emplace("m2x4_014", FindAsset("Texture'/Game/Murals/2x4/m2x4_014.m2x4_014'"));
	//TextureMap.Emplace("m2x4_015", FindAsset("Texture'/Game/Murals/2x4/m2x4_015.m2x4_015'"));
	//TextureMap.Emplace("m2x4_016", FindAsset("Texture'/Game/Murals/2x4/m2x4_016.m2x4_016'"));
	//TextureMap.Emplace("m2x4_017", FindAsset("Texture'/Game/Murals/2x4/m2x4_017.m2x4_017'"));
	//TextureMap.Emplace("m2x4_018", FindAsset("Texture'/Game/Murals/2x4/m2x4_018.m2x4_018'"));
	//TextureMap.Emplace("m2x4_019", FindAsset("Texture'/Game/Murals/2x4/m2x4_019.m2x4_019'"));

	//TextureMap.Emplace("m2x4_020", FindAsset("Texture'/Game/Murals/2x4/m2x4_020.m2x4_020'"));
	//TextureMap.Emplace("m2x4_021", FindAsset("Texture'/Game/Murals/2x4/m2x4_021.m2x4_021'"));
	//TextureMap.Emplace("m2x4_022", FindAsset("Texture'/Game/Murals/2x4/m2x4_022.m2x4_022'"));
	//TextureMap.Emplace("m2x4_023", FindAsset("Texture'/Game/Murals/2x4/m2x4_023.m2x4_023'"));
	//TextureMap.Emplace("m2x4_024", FindAsset("Texture'/Game/Murals/2x4/m2x4_024.m2x4_024'"));
	//TextureMap.Emplace("m2x4_025", FindAsset("Texture'/Game/Murals/2x4/m2x4_025.m2x4_025'"));
	//TextureMap.Emplace("m2x4_026", FindAsset("Texture'/Game/Murals/2x4/m2x4_026.m2x4_026'"));
	//TextureMap.Emplace("m2x4_027", FindAsset("Texture'/Game/Murals/2x4/m2x4_027.m2x4_027'"));
	//TextureMap.Emplace("m2x4_028", FindAsset("Texture'/Game/Murals/2x4/m2x4_028.m2x4_028'"));
	//TextureMap.Emplace("m2x4_029", FindAsset("Texture'/Game/Murals/2x4/m2x4_029.m2x4_029'"));


	Texture_IDArray_2x4.Emplace("m2x4_001");
	Texture_IDArray_2x4.Emplace("m2x4_002");
	Texture_IDArray_2x4.Emplace("m2x4_003");
	Texture_IDArray_2x4.Emplace("m2x4_004");
	Texture_IDArray_2x4.Emplace("m2x4_005");
	Texture_IDArray_2x4.Emplace("m2x4_006");
	Texture_IDArray_2x4.Emplace("m2x4_007");
	Texture_IDArray_2x4.Emplace("m2x4_008");
	Texture_IDArray_2x4.Emplace("m2x4_009");

	Texture_IDArray_2x4.Emplace("m2x4_010");
	Texture_IDArray_2x4.Emplace("m2x4_011");
	//Texture_IDArray_2x4.Emplace("m2x4_012");
	//Texture_IDArray_2x4.Emplace("m2x4_013");
	//Texture_IDArray_2x4.Emplace("m2x4_014");
	//Texture_IDArray_2x4.Emplace("m2x4_015");
	//Texture_IDArray_2x4.Emplace("m2x4_016");
	//Texture_IDArray_2x4.Emplace("m2x4_017");
	//Texture_IDArray_2x4.Emplace("m2x4_018");
	//Texture_IDArray_2x4.Emplace("m2x4_019");

	//Texture_IDArray_2x4.Emplace("m2x4_020");
	//Texture_IDArray_2x4.Emplace("m2x4_021");
	//Texture_IDArray_2x4.Emplace("m2x4_022");
	//Texture_IDArray_2x4.Emplace("m2x4_023");
	//Texture_IDArray_2x4.Emplace("m2x4_024");
	//Texture_IDArray_2x4.Emplace("m2x4_025");
	//Texture_IDArray_2x4.Emplace("m2x4_026");
	//Texture_IDArray_2x4.Emplace("m2x4_027");
	//Texture_IDArray_2x4.Emplace("m2x4_028");
	//Texture_IDArray_2x4.Emplace("m2x4_029");

}

void UMuralManager::FindAllMuralTextures_2x3()
{
	TextureMap.Emplace("m2x3_001", FindAsset("Texture'/Game/Murals/2x3/m2x3_001.m2x3_001'"));
	TextureMap.Emplace("m2x3_002", FindAsset("Texture'/Game/Murals/2x3/m2x3_002.m2x3_002'"));
	TextureMap.Emplace("m2x3_003", FindAsset("Texture'/Game/Murals/2x3/m2x3_003.m2x3_003'"));
	TextureMap.Emplace("m2x3_004", FindAsset("Texture'/Game/Murals/2x3/m2x3_004.m2x3_004'"));
	TextureMap.Emplace("m2x3_005", FindAsset("Texture'/Game/Murals/2x3/m2x3_005.m2x3_005'"));
	TextureMap.Emplace("m2x3_006", FindAsset("Texture'/Game/Murals/2x3/m2x3_006.m2x3_006'"));
	TextureMap.Emplace("m2x3_007", FindAsset("Texture'/Game/Murals/2x3/m2x3_007.m2x3_007'"));
	TextureMap.Emplace("m2x3_008", FindAsset("Texture'/Game/Murals/2x3/m2x3_008.m2x3_008'"));
	TextureMap.Emplace("m2x3_009", FindAsset("Texture'/Game/Murals/2x3/m2x3_009.m2x3_009'"));

	TextureMap.Emplace("m2x3_010", FindAsset("Texture'/Game/Murals/2x3/m2x3_010.m2x3_010'"));
	TextureMap.Emplace("m2x3_011", FindAsset("Texture'/Game/Murals/2x3/m2x3_011.m2x3_011'"));
	//TextureMap.Emplace("m2x3_012", FindAsset("Texture'/Game/Murals/2x3/m2x3_012.m2x3_012'"));
	//TextureMap.Emplace("m2x3_013", FindAsset("Texture'/Game/Murals/2x3/m2x3_013.m2x3_013'"));
	//TextureMap.Emplace("m2x3_014", FindAsset("Texture'/Game/Murals/2x3/m2x3_014.m2x3_014'"));
	//TextureMap.Emplace("m2x3_015", FindAsset("Texture'/Game/Murals/2x3/m2x3_015.m2x3_015'"));
	//TextureMap.Emplace("m2x3_016", FindAsset("Texture'/Game/Murals/2x3/m2x3_016.m2x3_016'"));
	//TextureMap.Emplace("m2x3_017", FindAsset("Texture'/Game/Murals/2x3/m2x3_017.m2x3_017'"));
	//TextureMap.Emplace("m2x3_018", FindAsset("Texture'/Game/Murals/2x3/m2x3_018.m2x3_018'"));
	//TextureMap.Emplace("m2x3_019", FindAsset("Texture'/Game/Murals/2x3/m2x3_019.m2x3_019'"));

	//TextureMap.Emplace("m2x3_020", FindAsset("Texture'/Game/Murals/2x3/m2x3_020.m2x3_020'"));
	//TextureMap.Emplace("m2x3_021", FindAsset("Texture'/Game/Murals/2x3/m2x3_021.m2x3_021'"));
	//TextureMap.Emplace("m2x3_022", FindAsset("Texture'/Game/Murals/2x3/m2x3_022.m2x3_022'"));
	//TextureMap.Emplace("m2x3_023", FindAsset("Texture'/Game/Murals/2x3/m2x3_023.m2x3_023'"));
	//TextureMap.Emplace("m2x3_024", FindAsset("Texture'/Game/Murals/2x3/m2x3_024.m2x3_024'"));
	//TextureMap.Emplace("m2x3_025", FindAsset("Texture'/Game/Murals/2x3/m2x3_025.m2x3_025'"));
	//TextureMap.Emplace("m2x3_026", FindAsset("Texture'/Game/Murals/2x3/m2x3_026.m2x3_026'"));
	//TextureMap.Emplace("m2x3_027", FindAsset("Texture'/Game/Murals/2x3/m2x3_027.m2x3_027'"));
	//TextureMap.Emplace("m2x3_028", FindAsset("Texture'/Game/Murals/2x3/m2x3_028.m2x3_028'"));
	//TextureMap.Emplace("m2x3_029", FindAsset("Texture'/Game/Murals/2x3/m2x3_029.m2x3_029'"));


	Texture_IDArray_2x3.Emplace("m2x3_001");
	Texture_IDArray_2x3.Emplace("m2x3_002");
	Texture_IDArray_2x3.Emplace("m2x3_003");
	Texture_IDArray_2x3.Emplace("m2x3_004");
	Texture_IDArray_2x3.Emplace("m2x3_005");
	Texture_IDArray_2x3.Emplace("m2x3_006");
	Texture_IDArray_2x3.Emplace("m2x3_007");
	Texture_IDArray_2x3.Emplace("m2x3_008");
	Texture_IDArray_2x3.Emplace("m2x3_009");

	Texture_IDArray_2x3.Emplace("m2x3_010");
	Texture_IDArray_2x3.Emplace("m2x3_011");
	//Texture_IDArray_2x3.Emplace("m2x3_012");
	//Texture_IDArray_2x3.Emplace("m2x3_013");
	//Texture_IDArray_2x3.Emplace("m2x3_014");
	//Texture_IDArray_2x3.Emplace("m2x3_015");
	//Texture_IDArray_2x3.Emplace("m2x3_016");
	//Texture_IDArray_2x3.Emplace("m2x3_017");
	//Texture_IDArray_2x3.Emplace("m2x3_018");
	//Texture_IDArray_2x3.Emplace("m2x3_019");

	//Texture_IDArray_2x3.Emplace("m2x3_020");
	//Texture_IDArray_2x3.Emplace("m2x3_021");
	//Texture_IDArray_2x3.Emplace("m2x3_022");
	//Texture_IDArray_2x3.Emplace("m2x3_023");
	//Texture_IDArray_2x3.Emplace("m2x3_024");
	//Texture_IDArray_2x3.Emplace("m2x3_025");
	//Texture_IDArray_2x3.Emplace("m2x3_026");
	//Texture_IDArray_2x3.Emplace("m2x3_027");
	//Texture_IDArray_2x3.Emplace("m2x3_028");
	//Texture_IDArray_2x3.Emplace("m2x3_029");

}

void UMuralManager::FindAllMuralTextures_2x2()
{
	TextureMap.Emplace("m2x2_001", FindAsset("Texture'/Game/Murals/2x2/m2x2_001.m2x2_001'"));
	TextureMap.Emplace("m2x2_002", FindAsset("Texture'/Game/Murals/2x2/m2x2_002.m2x2_002'"));
	TextureMap.Emplace("m2x2_003", FindAsset("Texture'/Game/Murals/2x2/m2x2_003.m2x2_003'"));
	TextureMap.Emplace("m2x2_004", FindAsset("Texture'/Game/Murals/2x2/m2x2_004.m2x2_004'"));
	TextureMap.Emplace("m2x2_005", FindAsset("Texture'/Game/Murals/2x2/m2x2_005.m2x2_005'"));
	TextureMap.Emplace("m2x2_006", FindAsset("Texture'/Game/Murals/2x2/m2x2_006.m2x2_006'"));
	TextureMap.Emplace("m2x2_007", FindAsset("Texture'/Game/Murals/2x2/m2x2_007.m2x2_007'"));
	TextureMap.Emplace("m2x2_008", FindAsset("Texture'/Game/Murals/2x2/m2x2_008.m2x2_008'"));
	TextureMap.Emplace("m2x2_009", FindAsset("Texture'/Game/Murals/2x2/m2x2_009.m2x2_009'"));

	TextureMap.Emplace("m2x2_010", FindAsset("Texture'/Game/Murals/2x2/m2x2_010.m2x2_010'"));
	TextureMap.Emplace("m2x2_011", FindAsset("Texture'/Game/Murals/2x2/m2x2_011.m2x2_011'"));
	//TextureMap.Emplace("m2x2_012", FindAsset("Texture'/Game/Murals/2x2/m2x2_012.m2x2_012'"));
	//TextureMap.Emplace("m2x2_013", FindAsset("Texture'/Game/Murals/2x2/m2x2_013.m2x2_013'"));
	//TextureMap.Emplace("m2x2_014", FindAsset("Texture'/Game/Murals/2x2/m2x2_014.m2x2_014'"));
	//TextureMap.Emplace("m2x2_015", FindAsset("Texture'/Game/Murals/2x2/m2x2_015.m2x2_015'"));
	//TextureMap.Emplace("m2x2_016", FindAsset("Texture'/Game/Murals/2x2/m2x2_016.m2x2_016'"));
	//TextureMap.Emplace("m2x2_017", FindAsset("Texture'/Game/Murals/2x2/m2x2_017.m2x2_017'"));
	//TextureMap.Emplace("m2x2_018", FindAsset("Texture'/Game/Murals/2x2/m2x2_018.m2x2_018'"));
	//TextureMap.Emplace("m2x2_019", FindAsset("Texture'/Game/Murals/2x2/m2x2_019.m2x2_019'"));

	//TextureMap.Emplace("m2x2_020", FindAsset("Texture'/Game/Murals/2x2/m2x2_020.m2x2_020'"));
	//TextureMap.Emplace("m2x2_021", FindAsset("Texture'/Game/Murals/2x2/m2x2_021.m2x2_021'"));
	//TextureMap.Emplace("m2x2_022", FindAsset("Texture'/Game/Murals/2x2/m2x2_022.m2x2_022'"));
	//TextureMap.Emplace("m2x2_023", FindAsset("Texture'/Game/Murals/2x2/m2x2_023.m2x2_023'"));
	//TextureMap.Emplace("m2x2_024", FindAsset("Texture'/Game/Murals/2x2/m2x2_024.m2x2_024'"));
	//TextureMap.Emplace("m2x2_025", FindAsset("Texture'/Game/Murals/2x2/m2x2_025.m2x2_025'"));
	//TextureMap.Emplace("m2x2_026", FindAsset("Texture'/Game/Murals/2x2/m2x2_026.m2x2_026'"));
	//TextureMap.Emplace("m2x2_027", FindAsset("Texture'/Game/Murals/2x2/m2x2_027.m2x2_027'"));
	//TextureMap.Emplace("m2x2_028", FindAsset("Texture'/Game/Murals/2x2/m2x2_028.m2x2_028'"));
	//TextureMap.Emplace("m2x2_029", FindAsset("Texture'/Game/Murals/2x2/m2x2_029.m2x2_029'"));


	Texture_IDArray_2x2.Emplace("m2x2_001");
	Texture_IDArray_2x2.Emplace("m2x2_002");
	Texture_IDArray_2x2.Emplace("m2x2_003");
	Texture_IDArray_2x2.Emplace("m2x2_004");
	Texture_IDArray_2x2.Emplace("m2x2_005");
	Texture_IDArray_2x2.Emplace("m2x2_006");
	Texture_IDArray_2x2.Emplace("m2x2_007");
	Texture_IDArray_2x2.Emplace("m2x2_008");
	Texture_IDArray_2x2.Emplace("m2x2_009");

	Texture_IDArray_2x2.Emplace("m2x2_010");
	Texture_IDArray_2x2.Emplace("m2x2_011");
	//Texture_IDArray_2x2.Emplace("m2x2_012");
	//Texture_IDArray_2x2.Emplace("m2x2_013");
	//Texture_IDArray_2x2.Emplace("m2x2_014");
	//Texture_IDArray_2x2.Emplace("m2x2_015");
	//Texture_IDArray_2x2.Emplace("m2x2_016");
	//Texture_IDArray_2x2.Emplace("m2x2_017");
	//Texture_IDArray_2x2.Emplace("m2x2_018");
	//Texture_IDArray_2x2.Emplace("m2x2_019");

	//Texture_IDArray_2x2.Emplace("m2x2_020");
	//Texture_IDArray_2x2.Emplace("m2x2_021");
	//Texture_IDArray_2x2.Emplace("m2x2_022");
	//Texture_IDArray_2x2.Emplace("m2x2_023");
	//Texture_IDArray_2x2.Emplace("m2x2_024");
	//Texture_IDArray_2x2.Emplace("m2x2_025");
	//Texture_IDArray_2x2.Emplace("m2x2_026");
	//Texture_IDArray_2x2.Emplace("m2x2_027");
	//Texture_IDArray_2x2.Emplace("m2x2_028");
	//Texture_IDArray_2x2.Emplace("m2x2_029");
}

void UMuralManager::FindAllBorderTexturesAndMasks()
{
	//border textures
	BorderTextureMap.Emplace(sz_7x4, FindAsset("Texture'/Game/Murals/7x4/border_7x4.border_7x4'"));
	BorderTextureMap.Emplace(sz_7x3, FindAsset("Texture'/Game/Murals/7x3/border_7x3.border_7x3'"));
	BorderTextureMap.Emplace(sz_7x2, FindAsset("Texture'/Game/Murals/7x2/border_7x2.border_7x2'"));

	BorderTextureMap.Emplace(sz_6x4, FindAsset("Texture'/Game/Murals/6x4/border_6x4.border_6x4'"));
	BorderTextureMap.Emplace(sz_6x3, FindAsset("Texture'/Game/Murals/6x3/border_6x3.border_6x3'"));
	BorderTextureMap.Emplace(sz_6x2, FindAsset("Texture'/Game/Murals/6x2/border_6x2.border_6x2'"));

	BorderTextureMap.Emplace(sz_5x4, FindAsset("Texture'/Game/Murals/5x4/border_5x4.border_5x4'"));
	BorderTextureMap.Emplace(sz_5x3, FindAsset("Texture'/Game/Murals/5x3/border_5x3.border_5x3'"));
	BorderTextureMap.Emplace(sz_5x2, FindAsset("Texture'/Game/Murals/5x2/border_5x2.border_5x2'"));

	BorderTextureMap.Emplace(sz_4x4, FindAsset("Texture'/Game/Murals/4x4/border_4x4.border_4x4'"));
	BorderTextureMap.Emplace(sz_4x3, FindAsset("Texture'/Game/Murals/4x3/border_4x3.border_4x3'"));
	BorderTextureMap.Emplace(sz_4x2, FindAsset("Texture'/Game/Murals/4x2/border_4x2.border_4x2'"));

	BorderTextureMap.Emplace(sz_3x4, FindAsset("Texture'/Game/Murals/3x4/border_3x4.border_3x4'"));
	BorderTextureMap.Emplace(sz_3x3, FindAsset("Texture'/Game/Murals/3x3/border_3x3.border_3x3'"));
	BorderTextureMap.Emplace(sz_3x2, FindAsset("Texture'/Game/Murals/3x2/border_3x2.border_3x2'"));

	BorderTextureMap.Emplace(sz_2x4, FindAsset("Texture'/Game/Murals/2x4/border_2x4.border_2x4'"));
	BorderTextureMap.Emplace(sz_2x3, FindAsset("Texture'/Game/Murals/2x3/border_2x3.border_2x3'"));
	BorderTextureMap.Emplace(sz_2x2, FindAsset("Texture'/Game/Murals/2x2/border_2x2.border_2x2'"));


	//border textures
	BorderMaskMap.Emplace(sz_7x4, FindAsset("Texture'/Game/Murals/7x4/border_7x4.border_7x4'"));
	BorderMaskMap.Emplace(sz_7x3, FindAsset("Texture'/Game/Murals/7x3/border_7x3.border_7x3'"));
	BorderMaskMap.Emplace(sz_7x2, FindAsset("Texture'/Game/Murals/7x2/border_7x2.border_7x2'"));

	BorderMaskMap.Emplace(sz_6x4, FindAsset("Texture'/Game/Murals/6x4/border_6x4.border_6x4'"));
	BorderMaskMap.Emplace(sz_6x3, FindAsset("Texture'/Game/Murals/6x3/border_6x3.border_6x3'"));
	BorderMaskMap.Emplace(sz_6x2, FindAsset("Texture'/Game/Murals/6x2/border_6x2.border_6x2'"));

	BorderMaskMap.Emplace(sz_5x4, FindAsset("Texture'/Game/Murals/5x4/border_5x4.border_5x4'"));
	BorderMaskMap.Emplace(sz_5x3, FindAsset("Texture'/Game/Murals/5x3/border_5x3.border_5x3'"));
	BorderMaskMap.Emplace(sz_5x2, FindAsset("Texture'/Game/Murals/5x2/border_5x2.border_5x2'"));

	BorderMaskMap.Emplace(sz_4x4, FindAsset("Texture'/Game/Murals/4x4/border_4x4.border_4x4'"));
	BorderMaskMap.Emplace(sz_4x3, FindAsset("Texture'/Game/Murals/4x3/border_4x3.border_4x3'"));
	BorderMaskMap.Emplace(sz_4x2, FindAsset("Texture'/Game/Murals/4x2/border_4x2.border_4x2'"));

	BorderMaskMap.Emplace(sz_3x4, FindAsset("Texture'/Game/Murals/3x4/border_3x4.border_3x4'"));
	BorderMaskMap.Emplace(sz_3x3, FindAsset("Texture'/Game/Murals/3x3/border_3x3.border_3x3'"));
	BorderMaskMap.Emplace(sz_3x2, FindAsset("Texture'/Game/Murals/3x2/border_3x2.border_3x2'"));

	BorderMaskMap.Emplace(sz_2x4, FindAsset("Texture'/Game/Murals/2x4/border_2x4.border_2x4'"));
	BorderMaskMap.Emplace(sz_2x3, FindAsset("Texture'/Game/Murals/2x3/border_2x3.border_2x3'"));
	BorderMaskMap.Emplace(sz_2x2, FindAsset("Texture'/Game/Murals/2x2/border_2x2.border_2x2'"));

}


UTexture* UMuralManager::FindAsset(FString Name)
{
	ConstructorHelpers::FObjectFinder<UTexture> Asset((TEXT("%s"), *Name));
	return Asset.Object;
}

