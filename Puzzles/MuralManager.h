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


//GATHER INFO
	FString GetProperTexture_ID(TEnumAsByte<E_GridSize> GridSize, bool bUseDebugTexture);
	UTexture* GetProperTexture(FString Texture_ID);
	UTexture* GetProperBorderTexture(TEnumAsByte<E_GridSize> GridSize);
	UTexture* GetProperBorderMask(TEnumAsByte<E_GridSize> GridSize);
	
	TArray<FString>& ReturnProperArrayToUse(TEnumAsByte<E_GridSize> GridSize);

//SETUP

	UTexture* FindAsset(FString Name);

	void FindAllMuralTextures_7x4();
	void FindAllMuralTextures_7x3();
	void FindAllMuralTextures_7x2();

	void FindAllMuralTextures_6x4();
	void FindAllMuralTextures_6x3();
	void FindAllMuralTextures_6x2();

	void FindAllMuralTextures_5x4();
	void FindAllMuralTextures_5x3();
	void FindAllMuralTextures_5x2();

	void FindAllMuralTextures_4x4();
	void FindAllMuralTextures_4x3();
	void FindAllMuralTextures_4x2();

	void FindAllMuralTextures_3x4();
	void FindAllMuralTextures_3x3();
	void FindAllMuralTextures_3x2();

	void FindAllMuralTextures_2x4();
	void FindAllMuralTextures_2x3();
	void FindAllMuralTextures_2x2();

	void FindAllBorderTexturesAndMasks();

//MEMBERS

	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_7x4;		
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_7x3;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_7x2;

	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_6x4;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_6x3;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_6x2;

	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_5x4;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_5x3;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_5x2;

	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_4x4;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_4x3;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_4x2;

	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_3x4;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_3x3;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_3x2;

	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_2x4;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_2x3;
	//UPROPERTY()
	//	TMap<FString, TSoftObjectPtr<UTexture>> TextureMap_2x2;

	UPROPERTY()
		TMap<FString, TSoftObjectPtr<UTexture>> TextureMap;
	UPROPERTY()
		TMap<TEnumAsByte<E_GridSize>, TSoftObjectPtr<UTexture>> BorderTextureMap;
	UPROPERTY()
		TMap<TEnumAsByte<E_GridSize>, TSoftObjectPtr<UTexture>> BorderMaskMap;


//ID Arrays

	UPROPERTY()
		TArray<FString> Texture_IDArray_7x4;
	UPROPERTY()
		TArray<FString> Texture_IDArray_7x3;
	UPROPERTY()
		TArray<FString> Texture_IDArray_7x2;

	UPROPERTY()
		TArray<FString> Texture_IDArray_6x4;
	UPROPERTY()
		TArray<FString> Texture_IDArray_6x3;
	UPROPERTY()
		TArray<FString> Texture_IDArray_6x2;

	UPROPERTY()
		TArray<FString> Texture_IDArray_5x4;
	UPROPERTY()
		TArray<FString> Texture_IDArray_5x3;
	UPROPERTY()
		TArray<FString> Texture_IDArray_5x2;

	UPROPERTY()
		TArray<FString> Texture_IDArray_4x4;
	UPROPERTY()
		TArray<FString> Texture_IDArray_4x3;
	UPROPERTY()
		TArray<FString> Texture_IDArray_4x2;

	UPROPERTY()
		TArray<FString> Texture_IDArray_3x4;
	UPROPERTY()
		TArray<FString> Texture_IDArray_3x3;
	UPROPERTY()
		TArray<FString> Texture_IDArray_3x2;

	UPROPERTY()
		TArray<FString> Texture_IDArray_2x4;
	UPROPERTY()
		TArray<FString> Texture_IDArray_2x3;
	UPROPERTY()
		TArray<FString> Texture_IDArray_2x2;






















};

