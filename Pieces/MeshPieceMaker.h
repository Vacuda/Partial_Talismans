// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Structs/FPuzzleUnit.h"			// for FPuzzleUnit
#include "Talismans/Enums/E_PieceShape.h"		// for E_PieceShape
#include "MeshPieceMaker.generated.h"

class AMeshPiece;
class UMaterialInterface;
class UTexture;
class UHub;


UCLASS()
class TALISMANS_API UMeshPieceMaker : public UObject
{
	GENERATED_BODY()
	
public:

	UMeshPieceMaker();


//SETUP

	void CatchTheHub(UHub* _Hub);
	void FindMeshPieceStaticMeshes();


//GATHER INFO

	void GetCountOfTris(TEnumAsByte <E_PieceShape> Shape, int32* tricount);
	UStaticMesh* GetProperStaticMesh(TEnumAsByte <E_PieceShape> Shape);
	FVector GetLocationFromBinSocketCode(FName SocketCode);
	FVector GetLocationFromGridSocketCode(FName SocketCode);


//CHANGE INFO

	void SpawnGridMeshPieces();
	void SpawnBinMeshPieces();
	void SetMeshPieceTexture(AMeshPiece* MeshPiece, FPuzzleUnit& Puzzle);
	void DestroyBinMeshPieces();


//MEMBERS - SETUP


	UPROPERTY()
		UHub* Hub;


//MEMBERS - PIECES

	UPROPERTY()
		UTexture* Texture;

	UPROPERTY()
		UStaticMesh* SM_tri1;
	UPROPERTY()
		UStaticMesh* SM_tri2;
	UPROPERTY()
		UStaticMesh* SM_tri3;
	UPROPERTY()
		UStaticMesh* SM_tri4;
	UPROPERTY()
		UStaticMesh* SM_tri5;
	UPROPERTY()
		UStaticMesh* SM_tri6;

};
