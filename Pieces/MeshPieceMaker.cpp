// Copyright 2020 Vacuda


#include "MeshPieceMaker.h"
#include "UObject/ConstructorHelpers.h"					// for Helpers
#include "Materials/MaterialInterface.h"				// for MaterialInterface
#include "Materials/MaterialInstanceDynamic.h"			// for MatericalInstanceDynamic
#include "Engine/Texture.h"								// for Utexture
#include "Components/StaticMeshComponent.h"				// for GetMaterialIndex

#include "Talismans/Admin/Hub.h"						// for Hub
#include "Talismans/Admin/TheGameInstance.h"			// for TheGameInstance
#include "Talismans/TableNavigation/TableNavigator.h"	// for TableNavigator
#include "Talismans/Structs/FTable_Address.h"			// for FTable_Address
#include "Talismans/Pieces/MeshPiece.h"					// for MeshPiece
#include "Talismans/Pieces/MeshCluster.h"				// for MeshCluster

UMeshPieceMaker::UMeshPieceMaker()
{
	FindMeshPieceStaticMeshes();
}


// SETUP

void UMeshPieceMaker::CatchTheHub(UHub* _Hub)
{
	Hub = _Hub;
}

void UMeshPieceMaker::FindMeshPieceStaticMeshes()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_tri1(
		TEXT("StaticMesh'/Game/Meshes/Pieces/SM_tri1.SM_tri1'"));
	if (StaticMesh_tri1.Succeeded()) {
		SM_tri1 = StaticMesh_tri1.Object;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_tri2(
		TEXT("StaticMesh'/Game/Meshes/Pieces/SM_tri2.SM_tri2'"));
	if (StaticMesh_tri2.Succeeded()) {
		SM_tri2 = StaticMesh_tri2.Object;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_tri3(
		TEXT("StaticMesh'/Game/Meshes/Pieces/SM_tri3.SM_tri3'"));
	if (StaticMesh_tri3.Succeeded()) {
		SM_tri3 = StaticMesh_tri3.Object;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_tri4(
		TEXT("StaticMesh'/Game/Meshes/Pieces/SM_tri4.SM_tri4'"));
	if (StaticMesh_tri4.Succeeded()) {
		SM_tri4 = StaticMesh_tri4.Object;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_tri5(
		TEXT("StaticMesh'/Game/Meshes/Pieces/SM_tri5.SM_tri5'"));
	if (StaticMesh_tri5.Succeeded()) {
		SM_tri5 = StaticMesh_tri5.Object;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh_tri6(
		TEXT("StaticMesh'/Game/Meshes/Pieces/SM_tri6.SM_tri6'"));
	if (StaticMesh_tri6.Succeeded()) {
		SM_tri6 = StaticMesh_tri6.Object;
	}


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

UStaticMesh* UMeshPieceMaker::GetProperStaticMesh(TEnumAsByte <E_PieceShape> Shape)
{
	if (Shape == TRI1) {
		return SM_tri1;
	}
	else if (Shape == TRI2) {
		return SM_tri2;
	}
	else if (Shape == TRI3) {
		return SM_tri3;
	}
	else if (Shape == TRI4) {
		return SM_tri4;
	}
	else if (Shape == TRI5) {
		return SM_tri5;
	}
	else if (Shape == TRI6) {
		return SM_tri6;
	}
	else {
		//default
		return SM_tri1;
	}
}

FVector UMeshPieceMaker::GetLocationFromBinSocketCode(FName SocketCode)
{
	if (Hub->BinMesh) {
		FVector Location = Hub->BinMesh->GetSocketLocation(SocketCode);
		UE_LOG(LogTemp, Warning, TEXT("|||||||||||||||YES bin location"))
			UE_LOG(LogTemp, Warning, TEXT("||||||||||||||| %s"), *SocketCode.ToString())
			UE_LOG(LogTemp, Warning, TEXT("||||||||||||||| %s"), *Location.ToString())
			return Location;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("didn't get a good bin location|||||||||||||||"))
			return { 0.f, 0.f, 0.f };
	}
}

FVector UMeshPieceMaker::GetLocationFromGridSocketCode(FName SocketCode)
{
	if (Hub->GridMesh) {
		FVector Location = Hub->GridMesh->GetSocketLocation(SocketCode);
		UE_LOG(LogTemp, Warning, TEXT("|||||||||||||||YES GRID location"))
			UE_LOG(LogTemp, Warning, TEXT("||||||||||||||| %s"), *SocketCode.ToString())
			UE_LOG(LogTemp, Warning, TEXT("||||||||||||||| %s"), *Location.ToString())
			return Location;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("didn't get a good grid location||||||||||||||||||||"))
			return { 0.f, 0.f, 0.f };
	}
}


//CHANGE INFO

void UMeshPieceMaker::SpawnGridMeshPieces()
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	TArray<ACluster*> ClustersToSpawn;

	//loop cols
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
			FVector ClusterLocation = Hub->Navigator->GetLocationFromTable_Address(Cluster->Table_Address);

			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;

			//get rotation
			FRotator ClusterRotation = Cluster->Table_Address.ReturnTheRotation();

			//spawn cluster
			AMeshCluster* MeshCluster = GetWorld()->SpawnActor<AMeshCluster>(ClusterLocation, ClusterRotation, SpawnParams);

			//link meshcluster and cluster
			MeshCluster->ClusterPtr = Cluster;
			Cluster->MeshClusterPtr = MeshCluster;

		//SPAWN EACH PIECE

			for (auto& Piece : Cluster->HeldPieces) {

				//build params
				FVector PieceLocation = Hub->Navigator->GetLocationFromTable_Address(Piece->Table_Address);

				//get rotation
				FRotator PieceRotation = Piece->Table_Address.ReturnTheRotation();

				//spawn MeshPiece
				AMeshPiece* MeshPiece = GetWorld()->SpawnActor<AMeshPiece>(PieceLocation, PieceRotation, SpawnParams);

				//set ProperStaticMesh
				UStaticMesh* ProperStaticMesh = GetProperStaticMesh(Piece->Shape);

				//set StaticMesh
				MeshPiece->PieceMesh->SetStaticMesh(ProperStaticMesh);

				//link meshpiece and piece
				MeshPiece->PiecePtr = Piece;
				Piece->MeshPiecePtr = MeshPiece;

				//set MeshPiece texture
				SetMeshPieceTexture(MeshPiece, Puzzle);

				//attach to cluster
				MeshPiece->AttachToComponent(MeshCluster->SceneComp, FAttachmentTransformRules(
					EAttachmentRule::KeepWorld,
					EAttachmentRule::KeepWorld,
					EAttachmentRule::SnapToTarget,
					true));
			}
	}			
}

void UMeshPieceMaker::SpawnBinMeshPieces()
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	TArray<ACluster*> ClustersToSpawn;

	//loop cols
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

	//loop ClustersToSpawn
	for (auto& Cluster : ClustersToSpawn) {

		//SPAWN CLUSTER

			//build params
			FVector ClusterLocation = Hub->Navigator->GetLocationFromTable_Address(Cluster->Table_Address);
			
			//UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *ClusterLocation.ToString())
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;

			//get rotation
			FRotator ClusterRotation = Cluster->Table_Address.ReturnTheRotation();

			//spawn cluster
			AMeshCluster* MeshCluster = GetWorld()->SpawnActor<AMeshCluster>(ClusterLocation, ClusterRotation, SpawnParams);

			//link meshcluster and cluster
			MeshCluster->ClusterPtr = Cluster;
			Cluster->MeshClusterPtr = MeshCluster;

		//SPAWN EACH PIECE

			for (auto& Piece : Cluster->HeldPieces) {

				//build params
				FVector PieceLocation = Hub->Navigator->GetLocationFromTable_Address(Piece->Table_Address);

				//UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *PieceLocation.ToString())

				//get rotation
				FRotator PieceRotation = Piece->Table_Address.ReturnTheRotation();

				//spawn MeshPiece
				AMeshPiece* MeshPiece = GetWorld()->SpawnActor<AMeshPiece>(PieceLocation, PieceRotation, SpawnParams);

				//set ProperStaticMesh
				UStaticMesh* ProperStaticMesh = GetProperStaticMesh(Piece->Shape);

				//set StaticMesh
				MeshPiece->PieceMesh->SetStaticMesh(ProperStaticMesh);

				//link meshpiece and piece
				MeshPiece->PiecePtr = Piece;
				Piece->MeshPiecePtr = MeshPiece;

				//set MeshPiece texture
				TEnumAsByte <E_PuzzleLetter> ThisPiecesPuzzleLetter = MeshPiece->PiecePtr->HomeTable_Address.PuzzleLetter;
				FPuzzleUnit& ThisPiecesPuzzle = Hub->GameInstance->PuzzleMap[ThisPiecesPuzzleLetter];
				SetMeshPieceTexture(MeshPiece, ThisPiecesPuzzle);

				//attach to cluster
				MeshPiece->AttachToComponent(MeshCluster->SceneComp, FAttachmentTransformRules(
					EAttachmentRule::KeepWorld,
					EAttachmentRule::KeepWorld,
					EAttachmentRule::SnapToTarget,
						true));
			}
	}
}

void UMeshPieceMaker::SetMeshPieceTexture(AMeshPiece* MeshPiece, FPuzzleUnit& Puzzle)
{
	//find current Material
	UMaterialInterface* BaseMat = MeshPiece->PieceMesh->GetMaterial(0);

	//make new Instance of Material
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BaseMat, MeshPiece->PieceMesh);

	//set MuralTexture
	DynMaterial->SetTextureParameterValue(TEXT("MuralTexture"), Puzzle.MuralTexture);

	//set Border on
	if (Puzzle.bIsBordered) {
		DynMaterial->SetScalarParameterValue(TEXT("BorderSwitch"), 1.0f);
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
	DynMaterial->SetScalarParameterValue(TEXT("Col"), MeshPiece->PiecePtr->HomeTable_Address.Col);

	//set Row Position
	DynMaterial->SetScalarParameterValue(TEXT("Row"), MeshPiece->PiecePtr->HomeTable_Address.Row - 1);

	//numbers off because rotation goes clockwise, not counter-clockwise
	if (MeshPiece->PiecePtr->HomeTable_Address.Tri == 1) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 1);
	}

	if (MeshPiece->PiecePtr->HomeTable_Address.Tri == 2) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 6);
	}

	if (MeshPiece->PiecePtr->HomeTable_Address.Tri == 3) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 5);
	}

	if (MeshPiece->PiecePtr->HomeTable_Address.Tri == 4) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 4);
	}

	if (MeshPiece->PiecePtr->HomeTable_Address.Tri == 5) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 3);
	}

	if (MeshPiece->PiecePtr->HomeTable_Address.Tri == 6) {
		DynMaterial->SetScalarParameterValue(TEXT("Tri"), 2);
	}

	////set Row position if Col is odd
	//if (MeshPiece->PiecePtr->HomeTable_Address.Col % 2 == 1) {
	//	int32 NewParam = 2 * (MeshPiece->PiecePtr->HomeTable_Address.Row) - 1;
	//	DynMaterial->SetScalarParameterValue(TEXT("Row"), NewParam);
	//}

	//// set Row position if Col is even
	//if (MeshPiece->PiecePtr->HomeTable_Address.Col % 2 == 0) {
	//	int32 NewParam = 2 * (MeshPiece->PiecePtr->HomeTable_Address.Row) - 2;
	//	DynMaterial->SetScalarParameterValue(TEXT("Row"), NewParam);
	//}

	//change Material to this new Instance
	MeshPiece->PieceMesh->SetMaterial(0, DynMaterial);

}
						




 


