// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talismans/Structs/FPuzzleUnit.h"			// for FPuzzleUnit
#include "Talismans/Enums/E_PieceShape.h"			// for E_PieceShape
#include "Talismans/Enums/E_GridSize.h"				// for E_GridSize
#include "MeshPieceMaker.generated.h"

class AActorPiece;
class UMaterialInterface;
class UTexture;
class UCluster;
class UHub;


UCLASS()
class TALISMANS_API UMeshPieceMaker : public UObject
{
	GENERATED_BODY()
	
public:

	UMeshPieceMaker();


//SETUP

	void CatchTheHub(UHub* _Hub);
	void FindActorPieceMeshes();
	UStaticMesh* FindPieceMesh(FString Name);
	USkeletalMesh* FindItemPieceMesh(FString Name);


//GATHER INFO

	void GetCountOfTris(TEnumAsByte <E_PieceShape> Shape, int32* tricount);



//CHANGE INFO

	void SpawnActorPieces();
	void SetActorPieceTexture(AActorPiece* ActorPiece, FPuzzleUnit& Puzzle);
	void SpawnProperGridMesh();
	FVector GetGridLocationDueToGridSize(TEnumAsByte<E_GridSize> GridSize);
	void SpawnTransferSackDroppedCluster(UCluster* Cluster, float TimeToDelay);



//MEMBERS - SETUP


	UPROPERTY()
		UHub* Hub;
	UPROPERTY()
		TMap<TEnumAsByte<E_PieceShape>, TSoftObjectPtr<UStaticMesh>> StaticMeshMap;
	UPROPERTY()
		TMap<TEnumAsByte<E_PieceShape>, TSoftObjectPtr<USkeletalMesh>> SkeletalMeshMap;


};

