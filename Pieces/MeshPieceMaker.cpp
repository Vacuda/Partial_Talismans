// Copyright 2020 Vacuda


#include "MeshPieceMaker.h"
#include "UObject/ConstructorHelpers.h"					// for Helpers
#include "Materials/MaterialInterface.h"				// for MaterialInterface
#include "Materials/MaterialInstanceDynamic.h"			// for MatericalInstanceDynamic
#include "Engine/Texture.h"								// for Utexture
#include "Components/StaticMeshComponent.h"				// for GetMaterialIndex

#include "Talismans/Admin/Hub.h"						// for Hub
#include "Talismans/Admin/TheGameInstance.h"			// for TheGameInstance
#include "Talismans/TableNavigation/BoardArbiter.h"		// for BoardArbiter
#include "Talismans/Structs/FTable_Address.h"			// for FTable_Address
#include "Talismans/Pieces/ActorPiece.h"				// for ActorPiece
#include "Talismans/Pieces/ActorCluster.h"				// for ActorCluster
#include "Talismans/Pieces/Cluster.h"					// for Cluster
#include "Talismans/Admin/BasicSceneActor.h"			// for BasicSceneActor

UMeshPieceMaker::UMeshPieceMaker()
{
	FindActorPieceMeshes();
}


// SETUP

void UMeshPieceMaker::CatchTheHub(UHub* _Hub)
{
	Hub = _Hub;
}

void UMeshPieceMaker::FindActorPieceMeshes()
{
	StaticMeshMap.Emplace(TRI1, FindPieceMesh("StaticMesh'/Game/Meshes/Pieces/SM_tri1.SM_tri1'"));
	StaticMeshMap.Emplace(TRI2, FindPieceMesh("StaticMesh'/Game/Meshes/Pieces/SM_tri2.SM_tri2'"));
	StaticMeshMap.Emplace(TRI3, FindPieceMesh("StaticMesh'/Game/Meshes/Pieces/SM_tri3.SM_tri3'"));
	StaticMeshMap.Emplace(TRI4, FindPieceMesh("StaticMesh'/Game/Meshes/Pieces/SM_tri4.SM_tri4'"));
	StaticMeshMap.Emplace(TRI5, FindPieceMesh("StaticMesh'/Game/Meshes/Pieces/SM_tri5.SM_tri5'"));
	StaticMeshMap.Emplace(TRI6, FindPieceMesh("StaticMesh'/Game/Meshes/Pieces/SM_tri6.SM_tri6'"));

	//ItemPieces
	SkeletalMeshMap.Emplace(IP_TOPUZZLE_2, FindItemPieceMesh("SkeletalMesh'/Game/Meshes/ItemPieces/ToPuzzle/SKM_itempiece_topuzzle_2way.SKM_itempiece_topuzzle_2way'"));
	SkeletalMeshMap.Emplace(IP_TOPUZZLE_4, FindItemPieceMesh("SkeletalMesh'/Game/Meshes/ItemPieces/ToPuzzle/SKM_itempiece_topuzzle_4way.SKM_itempiece_topuzzle_4way'"));
	SkeletalMeshMap.Emplace(IP_TOPUZZLE_6, FindItemPieceMesh("SkeletalMesh'/Game/Meshes/ItemPieces/ToPuzzle/SKM_itempiece_topuzzle_6way.SKM_itempiece_topuzzle_6way'"));

}

UStaticMesh* UMeshPieceMaker::FindPieceMesh(FString Name)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset((TEXT("%s"), *Name));
	return Asset.Object;
}

USkeletalMesh* UMeshPieceMaker::FindItemPieceMesh(FString Name)
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset((TEXT("%s"), *Name));
	return Asset.Object;
}


// GATHER INFO

void UMeshPieceMaker::GetCountOfTris(TEnumAsByte <E_PieceShape> Shape, int32* tricount)
{
	if (Shape == TRI1) {
		*tricount = 1;
		return;
	}
	if (Shape == TRI2) {
		*tricount = 2;
		return;
	}
	if (Shape == TRI3) {
		*tricount = 3;
		return;
	}
	if (Shape == TRI4) {
		*tricount = 4;
		return;
	}
	if (Shape == TRI5) {
		*tricount = 5;
		return;
	}
	if (Shape == TRI6) {
		*tricount = 6;
		return;
	}
}



//CHANGE INFO

void UMeshPieceMaker::SpawnActorPieces()
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//initialize array to house all clusters needed to spawn
	TArray<UCluster*> ClustersToSpawn;

	//loop cols - for ColMapBin
	for (auto& Col : Puzzle.ColMapBin) {

		//loop rows
		for (auto& Row : Col.Value.RowMap) {

			//loop tris
			for (auto& Tri : Row.Value.TriMap) {

				if (Tri.Value.PiecePtr) {
					ClustersToSpawn.AddUnique(Tri.Value.PiecePtr->ClusterPtr);
				}
			}
		}
	}

	//loop cols - for ColMapGrid
	for (auto& Col : Puzzle.ColMapGrid) {

		//loop rows
		for (auto& Row : Col.Value.RowMap) {

			//loop tris
			for (auto& Tri : Row.Value.TriMap) {

				if (Tri.Value.PiecePtr) {
					ClustersToSpawn.AddUnique(Tri.Value.PiecePtr->ClusterPtr);
				}
			}
		}
	}

	//loop ClustersToSpawn
	for (auto& Cluster : ClustersToSpawn) {

		//SPAWN CLUSTER

			//build params
			FVector ClusterLocation = Hub->BoardArbiter->GetLocationFromTable_Address(Cluster->Table_Address);
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;

			//get rotation
			FRotator ClusterRotation = Cluster->Table_Address.ReturnTheRotation();

			//spawn cluster
			AActorCluster* ActorCluster = GetWorld()->SpawnActor<AActorCluster>(ClusterLocation, ClusterRotation, SpawnParams);

			//link meshcluster and cluster
			ActorCluster->ClusterPtr = Cluster;
			Cluster->ActorClusterPtr = ActorCluster;

		//SPAWN EACH PIECE

			for (auto& Piece : Cluster->HeldPieces) {

				//build params
				FVector PieceLocation = Hub->BoardArbiter->GetLocationFromTable_Address(Piece->Table_Address);

				//get rotation
				FRotator PieceRotation = Piece->Table_Address.ReturnTheRotation();

				//spawn ActorPiece
				AActorPiece* ActorPiece = GetWorld()->SpawnActor<AActorPiece>(PieceLocation, PieceRotation, SpawnParams);

				//if not ItemPiece
				if (Piece->bIsItemPiece == false) {

					//set ProperStaticMesh
					UStaticMesh* ProperStaticMesh = StaticMeshMap[Piece->Shape].Get();

					//set StaticMesh
					ActorPiece->PieceMesh->SetStaticMesh(ProperStaticMesh);

					//link meshpiece and piece
					ActorPiece->PiecePtr = Piece;
					Piece->ActorPiecePtr = ActorPiece;

					//set ActorPiece texture for standard piece
					TEnumAsByte <E_PuzzleLetter> ThisPiecesPuzzleLetter = ActorPiece->PiecePtr->HomeTable_Address.PuzzleLetter;
					FPuzzleUnit& ThisPiecesPuzzle = Hub->GameInstance->PuzzleMap[ThisPiecesPuzzleLetter];
					SetActorPieceTexture(ActorPiece, ThisPiecesPuzzle);

					//attach to cluster
					ActorPiece->AttachToComponent(ActorCluster->SceneComp, FAttachmentTransformRules(
						EAttachmentRule::KeepWorld,
						EAttachmentRule::KeepWorld,
						EAttachmentRule::SnapToTarget,
						true));
				}
				else {

					//set ProperSkeletalMesh
					USkeletalMesh* ProperSkeletalMesh = SkeletalMeshMap[Piece->Shape].Get();

					//set mesh
					ActorPiece->ItemPieceMesh->SetSkeletalMesh(ProperSkeletalMesh);

					//reset root component and location
					ActorPiece->SetRootComponent(ActorPiece->ItemPieceMesh);
					ActorPiece->SetActorLocation(PieceLocation);

					//link meshpiece and piece
					ActorPiece->PiecePtr = Piece;
					Piece->ActorPiecePtr = ActorPiece;

					//attach to cluster
					ActorPiece->AttachToComponent(ActorCluster->SceneComp, FAttachmentTransformRules(
						EAttachmentRule::KeepWorld,
						EAttachmentRule::KeepWorld,
						EAttachmentRule::SnapToTarget,
						true));
				}
			}
	}
}

void UMeshPieceMaker::SetActorPieceTexture(AActorPiece* ActorPiece, FPuzzleUnit& Puzzle)
{
	//find current Material
	UMaterialInterface* BaseMat = ActorPiece->PieceMesh->GetMaterial(0);

	//make new Instance of Material
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BaseMat, ActorPiece->PieceMesh);

	//set MuralTexture
	DynMaterial->SetTextureParameterValue(TEXT("MuralTexture"), Puzzle.MuralTexture);

	//set Border on
	if (Puzzle.bIsBordered) {
		DynMaterial->SetScalarParameterValue(TEXT("BorderSwitch"), 1.0f);

		//set border texture and mask
		DynMaterial->SetTextureParameterValue(TEXT("BorderTexture"), Puzzle.BorderTexture);
		DynMaterial->SetTextureParameterValue(TEXT("BorderMask"), Puzzle.BorderMask);

	}
	//set border off
	else {
		DynMaterial->SetScalarParameterValue(TEXT("BorderSwitch"), 0.0f);
	}

	//set TotalCols
	DynMaterial->SetScalarParameterValue(TEXT("TotalCols"), Puzzle.PuzzleGridWidth);

	//set TotalRows
	DynMaterial->SetScalarParameterValue(TEXT("TotalRows"), Puzzle.PuzzleGridHeight);

	//set Col Position 
	DynMaterial->SetScalarParameterValue(TEXT("Col"), ActorPiece->PiecePtr->HomeTable_Address.Col);

	//set Row Position
	DynMaterial->SetScalarParameterValue(TEXT("Row"), ActorPiece->PiecePtr->HomeTable_Address.Row - 1);

	//numbers off because rotation goes clockwise, not counter-clockwise
	if (ActorPiece->PiecePtr->HomeTable_Address.Tri == 1) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 1);
	}

	if (ActorPiece->PiecePtr->HomeTable_Address.Tri == 2) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 6);
	}

	if (ActorPiece->PiecePtr->HomeTable_Address.Tri == 3) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 5);
	}

	if (ActorPiece->PiecePtr->HomeTable_Address.Tri == 4) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 4);
	}

	if (ActorPiece->PiecePtr->HomeTable_Address.Tri == 5) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 3);
	}

	if (ActorPiece->PiecePtr->HomeTable_Address.Tri == 6) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 2);
	}

	//change Material to this new Instance
	ActorPiece->PieceMesh->SetMaterial(0, DynMaterial);

}

void UMeshPieceMaker::SpawnProperGridMesh()
{
	//condense
	TEnumAsByte<E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//get Mesh
	UStaticMesh* GridStaticMesh = Puzzle.GridStaticMesh.Get();

	//spawn params
	FVector Location = GetGridLocationDueToGridSize(Puzzle.GridSize);
	FRotator Rotation = FRotator(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;

	//spawn grid
	ABasicSceneActor* Grid = GetWorld()->SpawnActor<ABasicSceneActor>(Location, Rotation, SpawnParams);
	Grid->SceneComp->SetStaticMesh(GridStaticMesh);

	//set scene comp to GridMesh
	Hub->GridMesh = Grid->SceneComp;
}

FVector UMeshPieceMaker::GetGridLocationDueToGridSize(TEnumAsByte<E_GridSize> GridSize)
{
	FVector Location = FVector(0.f, 0.f, 0.f);

	// Y - 2 rows
	if (GridSize == sz_7x2 || GridSize == sz_6x2 || GridSize == sz_5x2 || GridSize == sz_4x2 || GridSize == sz_3x2 || GridSize == sz_2x2){
		Location.Y = 100.f;   
	}
	// Y - 3 rows
	else if (GridSize == sz_7x3 || GridSize == sz_6x3 || GridSize == sz_5x3 || GridSize == sz_4x3 || GridSize == sz_3x3 || GridSize == sz_2x3){
		Location.Y = 85.f;     
	}
	// Y - 4 rows
	else{
		Location.Y = 70.f;
	}


	// X - 7 cols
	if (GridSize == sz_7x4 || GridSize == sz_7x3 || GridSize == sz_7x2){
		Location.X = 122.f;
	}
	// X - 6 cols
	else if (GridSize == sz_6x4 || GridSize == sz_6x3 || GridSize == sz_6x2){
		Location.X = 134.f;
	}
	// X - 5 cols
	else if (GridSize == sz_5x4 || GridSize == sz_5x3 || GridSize == sz_5x2){
		Location.X = 146.f;
	}
	// X - 4 cols
	else if (GridSize == sz_4x4 || GridSize == sz_4x3 || GridSize == sz_4x2){
		Location.X = 158.f;
	}
	// X - 3 cols
	else if (GridSize == sz_3x4 || GridSize == sz_3x3 || GridSize == sz_3x2){
		Location.X = 170.f;
	}
	// X - 2 cols
	else {
		Location.X = 182.f;
	}


	return Location;
}

void UMeshPieceMaker::SpawnTransferSackDroppedCluster(UCluster* Cluster, float TimeToDelay)
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

//SPAWN CLUSTER

	//build params
	FVector ClusterLocation = Hub->BoardArbiter->GetLocationFromTable_Address(Cluster->Table_Address);

	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;

	//get rotation
	FRotator ClusterRotation = Cluster->Table_Address.ReturnTheRotation();

	//spawn cluster
	AActorCluster* ActorCluster = GetWorld()->SpawnActor<AActorCluster>(ClusterLocation, ClusterRotation, SpawnParams);

	//link meshcluster and cluster
	ActorCluster->ClusterPtr = Cluster;
	Cluster->ActorClusterPtr = ActorCluster;

	//SPAWN EACH PIECE

	for (auto& Piece : Cluster->HeldPieces) {

		//build params
		FVector PieceLocation = Hub->BoardArbiter->GetLocationFromTable_Address(Piece->Table_Address);

		//get rotation
		FRotator PieceRotation = Piece->Table_Address.ReturnTheRotation();

		//spawn ActorPiece
		AActorPiece* ActorPiece = GetWorld()->SpawnActor<AActorPiece>(PieceLocation, PieceRotation, SpawnParams);

		//if not ItemPiece
		if (Piece->bIsItemPiece == false) {

			//set ProperStaticMesh
			UStaticMesh* ProperStaticMesh = StaticMeshMap[Piece->Shape].Get();

			//set StaticMesh
			ActorPiece->PieceMesh->SetStaticMesh(ProperStaticMesh);

			//link meshpiece and piece
			ActorPiece->PiecePtr = Piece;
			Piece->ActorPiecePtr = ActorPiece;

			//set ActorPiece texture for standard piece
			TEnumAsByte <E_PuzzleLetter> ThisPiecesPuzzleLetter = ActorPiece->PiecePtr->HomeTable_Address.PuzzleLetter;
			FPuzzleUnit& ThisPiecesPuzzle = Hub->GameInstance->PuzzleMap[ThisPiecesPuzzleLetter];
			SetActorPieceTexture(ActorPiece, ThisPiecesPuzzle);

			//attach to cluster
			ActorPiece->AttachToComponent(ActorCluster->SceneComp, FAttachmentTransformRules(
				EAttachmentRule::KeepWorld,
				EAttachmentRule::KeepWorld,
				EAttachmentRule::SnapToTarget,
				true));
		}
		else {

			//set ProperSkeletalMesh
			USkeletalMesh* ProperSkeletalMesh = SkeletalMeshMap[Piece->Shape].Get();

			//set mesh
			ActorPiece->ItemPieceMesh->SetSkeletalMesh(ProperSkeletalMesh);

			//reset root component and location
			ActorPiece->SetRootComponent(ActorPiece->ItemPieceMesh);
			ActorPiece->SetActorLocation(PieceLocation);

			//link meshpiece and piece
			ActorPiece->PiecePtr = Piece;
			Piece->ActorPiecePtr = ActorPiece;

			//attach to cluster
			ActorPiece->AttachToComponent(ActorCluster->SceneComp, FAttachmentTransformRules(
				EAttachmentRule::KeepWorld,
				EAttachmentRule::KeepWorld,
				EAttachmentRule::SnapToTarget,
				true));
		}
	}
}


