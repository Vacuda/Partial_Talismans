// Copyright 2020 Vacuda


#include "LoadManager_Table.h"
#include "Kismet/GameplayStatics.h"							// for GameplayStatics
#include "Engine/World.h"									// for GetLevelScriptActor

#include "Talismans/Admin/TheGameInstance.h"				// for GameInstance
#include "Talismans/Pawns/PawnCursor.h"						// for PawnCursor
#include "Talismans/TableNavigation/Animator.h"				// for Animator
#include "Talismans/TableNavigation/BinArbiter.h"			// for BinArbiter
#include "Talismans/TableNavigation/GridArbiter.h"			// for GridArbiter
#include "Talismans/TableNavigation/PieceArbiter.h"			// for PieceArbiter
#include "Talismans/TableNavigation/RackArbiter.h"			// for RackArbiter
#include "Talismans/TableNavigation/TableNavigator.h"		// for Navigator
#include "Talismans/Pieces/MeshPieceMaker.h"				// for MeshPieceMaker
#include "Talismans/Levels/PuzzleLevel.h"					// for PuzzleLevel
#include "Talismans/Controllers/ThePlayerController.h"		// for ThePlayerController
#include "Talismans/Admin/Hub.h"							// for Hub


void ULoadManager_Table::RunLoadManager()
{
	//create Hub
	FindThePuzzleLevel();
	CreateHub();
	Hub->PuzzleLevel = PuzzleLevel;

	//start pawncursor spawn first
	FindThePlayerController();
	Hub->Controller->CreateAndPossessPawnCursor();

	MakeNewObjects();

	FindTheGameInstance();
	FindThePawnCursor();
	FindTheBinMesh();
	FindTheGridMesh();
	FindTheTableLightMaterial();
	FindThePuzzleGridHeightAndWidth();
	FindTheStartingTable_Address();

	SendTheHubToEveryone();

	//everything should be connected
	Hub->PawnCursor->SetStartPosition();
	Hub->Animator->SetStartCameraPosition();
	Hub->MeshPieceMaker->SpawnGridMeshPieces();
	Hub->MeshPieceMaker->SpawnBinMeshPieces();
	Hub->RackArbiter->SpawnRackAndPortraits(); 

	//@@@@ probably set Bin Orientation here


	

	const TEnumAsByte<E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FString PuzzleLetterString = UEnum::GetValueAsString(PuzzleLetter.GetValue());

	UE_LOG(LogTemp, Warning, TEXT("PuzzleLetter: %s"), *PuzzleLetterString)


}

//create objects

void ULoadManager_Table::CreateHub()
{
	Hub = NewObject<UHub>(PuzzleLevel, UHub::StaticClass());
}

void ULoadManager_Table::MakeNewObjects()
{
	Hub->BinArbiter = NewObject<UBinArbiter>(Hub, UBinArbiter::StaticClass());

	Hub->GridArbiter = NewObject<UGridArbiter>(Hub, UGridArbiter::StaticClass());

	Hub->PieceArbiter = NewObject<UPieceArbiter>(Hub, UPieceArbiter::StaticClass());

	Hub->RackArbiter = NewObject<URackArbiter>(Hub, URackArbiter::StaticClass());

	Hub->Navigator = NewObject<UTableNavigator>(Hub, UTableNavigator::StaticClass());

	Hub->MeshPieceMaker = NewObject<UMeshPieceMaker>(Hub, UMeshPieceMaker::StaticClass());

	Hub->Animator = NewObject<AAnimator>(Hub, AAnimator::StaticClass());
}

//find objects and info
void ULoadManager_Table::FindTheGameInstance()
{
	Hub->GameInstance = Cast<UTheGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ULoadManager_Table::FindThePlayerController()
{
	Hub->Controller = Cast<AThePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ULoadManager_Table::FindThePuzzleLevel()
{
	PuzzleLevel = Cast<APuzzleLevel>(GetWorld()->GetLevelScriptActor());
}

void ULoadManager_Table::FindThePawnCursor()
{
	Hub->PawnCursor = Hub->Controller->GetPawnCursor();
}

void ULoadManager_Table::FindTheBinMesh()
{
	TArray<AActor*> AllActorsWithTagArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Bin", AllActorsWithTagArray);

	//safety check
	if (AllActorsWithTagArray.Num() != 0) {
		AActor* BinActor = AllActorsWithTagArray[0];
		Hub->BinMesh = BinActor->FindComponentByClass<UStaticMeshComponent>();
	}
}

void ULoadManager_Table::FindTheGridMesh()
{
	TArray<AActor*> AllActorsWithTagArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Grid", AllActorsWithTagArray);

	//safety check
	if (AllActorsWithTagArray.Num() != 0) {
		AActor* GridActor = AllActorsWithTagArray[0];
		Hub->GridMesh = GridActor->FindComponentByClass<UStaticMeshComponent>();
	}
}

void ULoadManager_Table::FindTheTableLightMaterial()
{
	TArray<AActor*> AllActorsWithTagArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "TableLight", AllActorsWithTagArray);

	//safety check
	if (AllActorsWithTagArray.Num() != 0) {
		AActor* TableLightActor = AllActorsWithTagArray[0];

		//get staticmesh
		UStaticMeshComponent* TableLightMesh = TableLightActor->FindComponentByClass<UStaticMeshComponent>();

		//get interface
		UMaterialInterface* TableLightMat = TableLightMesh->GetMaterial(0);

		//make new Instance of Material
		Hub->TableLightMaterial = UMaterialInstanceDynamic::Create(TableLightMat, TableLightMesh);
	
		//change Material to this new Instance
		TableLightMesh->SetMaterial(0, Hub->TableLightMaterial);
	}
}

void ULoadManager_Table::FindThePuzzleGridHeightAndWidth()
{
	Hub->PuzzleGridHeight = Hub->GameInstance->PuzzleMap[Hub->GameInstance->CurrentPuzzleLetter].PuzzleGridHeight;
	Hub->PuzzleGridWidth = Hub->GameInstance->PuzzleMap[Hub->GameInstance->CurrentPuzzleLetter].PuzzleGridWidth;
}

void ULoadManager_Table::FindTheStartingTable_Address()
{
	//condense
	TEnumAsByte <E_PuzzleLetter> PuzzleLetter = Hub->GameInstance->CurrentPuzzleLetter;
	FPuzzleUnit& Puzzle = Hub->GameInstance->PuzzleMap[PuzzleLetter];

	//if first time to this board
	if (Puzzle.ExitTable_Address.Col == 0) {
		Hub->StartingTable_Address.Board = GRID;
		Hub->StartingTable_Address.PuzzleLetter = PuzzleLetter;
		Hub->StartingTable_Address.Col = 5;
		Hub->StartingTable_Address.Row = 4;
		Hub->StartingTable_Address.Tri = 1;
	}
	else {
		//set to exit address
		Hub->StartingTable_Address = Puzzle.ExitTable_Address;
	}
}


//send out info
void ULoadManager_Table::SendTheHubToEveryone()
{
	Hub->PuzzleLevel->CatchTheHub(Hub);
	Hub->PawnCursor->CatchTheHub(Hub);
	Hub->Controller->CatchTheHub(Hub);
	Hub->Animator->CatchTheHub(Hub);
	Hub->BinArbiter->CatchTheHub(Hub);
	Hub->GridArbiter->CatchTheHub(Hub);
	Hub->PieceArbiter->CatchTheHub(Hub);
	Hub->RackArbiter->CatchTheHub(Hub);
	Hub->Navigator->CatchTheHub(Hub);
	Hub->MeshPieceMaker->CatchTheHub(Hub);



}

