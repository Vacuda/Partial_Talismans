// Copyright 2020 Vacuda


#include "NewWorldBuild.h"
#include "UObject/ConstructorHelpers.h"						// for ConstructorHelper

#include "Talismans/Admin/TheGameInstance.h"				// for TheGameInstance
#include "Talismans/Puzzles/MuralManager.h"					// for MuralManager
#include "Talismans/NewWorldBuild/RandomGridGeneration.h"	// for RandomGrid
#include "Talismans/Pieces/PieceMaker.h"					// for PieceMaker
#include "Talismans/Rooms/RoomNavigator.h"					// for RoomNavigator

UNewWorldBuild::UNewWorldBuild()
{
	CreatePuzzleLetterLookupMap();

	FindAllGridStaticMeshes();

}

// SETUP

void UNewWorldBuild::Setup(UTheGameInstance* _GameInstance)
{
	GameInstance = _GameInstance;
	TempleSize = GameInstance->TempleSettings.TempleSize;
}

void UNewWorldBuild::CreatePuzzleLetterLookupMap()
{
	PuzzleLetterLookupMap.Emplace(1, p001);
	PuzzleLetterLookupMap.Emplace(2, p002);
	PuzzleLetterLookupMap.Emplace(3, p003);
	PuzzleLetterLookupMap.Emplace(4, p004);
	PuzzleLetterLookupMap.Emplace(5, p005);
	PuzzleLetterLookupMap.Emplace(6, p006);
	PuzzleLetterLookupMap.Emplace(7, p007);
	PuzzleLetterLookupMap.Emplace(8, p008);
	PuzzleLetterLookupMap.Emplace(9, p009);

	PuzzleLetterLookupMap.Emplace(10, p010);
	PuzzleLetterLookupMap.Emplace(11, p011);
	PuzzleLetterLookupMap.Emplace(12, p012);
	PuzzleLetterLookupMap.Emplace(13, p013);
	PuzzleLetterLookupMap.Emplace(14, p014);
	PuzzleLetterLookupMap.Emplace(15, p015);
	PuzzleLetterLookupMap.Emplace(16, p016);
	PuzzleLetterLookupMap.Emplace(17, p017);
	PuzzleLetterLookupMap.Emplace(18, p018);
	PuzzleLetterLookupMap.Emplace(19, p019);

	PuzzleLetterLookupMap.Emplace(20, p020);
	PuzzleLetterLookupMap.Emplace(21, p021);
	PuzzleLetterLookupMap.Emplace(22, p022);
	PuzzleLetterLookupMap.Emplace(23, p023);
	PuzzleLetterLookupMap.Emplace(24, p024);
	PuzzleLetterLookupMap.Emplace(25, p025);
	PuzzleLetterLookupMap.Emplace(26, p026);
	PuzzleLetterLookupMap.Emplace(27, p027);
	PuzzleLetterLookupMap.Emplace(28, p028);
	PuzzleLetterLookupMap.Emplace(29, p029);

	PuzzleLetterLookupMap.Emplace(30, p030);
	PuzzleLetterLookupMap.Emplace(31, p031);
	PuzzleLetterLookupMap.Emplace(32, p032);
	PuzzleLetterLookupMap.Emplace(33, p033);
	PuzzleLetterLookupMap.Emplace(34, p034);
	PuzzleLetterLookupMap.Emplace(35, p035);
	PuzzleLetterLookupMap.Emplace(36, p036);
	PuzzleLetterLookupMap.Emplace(37, p037);
	PuzzleLetterLookupMap.Emplace(38, p038);
	PuzzleLetterLookupMap.Emplace(39, p039);

	PuzzleLetterLookupMap.Emplace(40, p040);
	PuzzleLetterLookupMap.Emplace(41, p041);
	PuzzleLetterLookupMap.Emplace(42, p042);
	PuzzleLetterLookupMap.Emplace(43, p043);
	PuzzleLetterLookupMap.Emplace(44, p044);
	PuzzleLetterLookupMap.Emplace(45, p045);
	PuzzleLetterLookupMap.Emplace(46, p046);
	PuzzleLetterLookupMap.Emplace(47, p047);
	PuzzleLetterLookupMap.Emplace(48, p048);
	PuzzleLetterLookupMap.Emplace(49, p049);

	PuzzleLetterLookupMap.Emplace(50, p050);
	PuzzleLetterLookupMap.Emplace(51, p051);
	PuzzleLetterLookupMap.Emplace(52, p052);
	PuzzleLetterLookupMap.Emplace(53, p053);
	PuzzleLetterLookupMap.Emplace(54, p054);
	PuzzleLetterLookupMap.Emplace(55, p055);
	PuzzleLetterLookupMap.Emplace(56, p056);
	PuzzleLetterLookupMap.Emplace(57, p057);
	PuzzleLetterLookupMap.Emplace(58, p058);
	PuzzleLetterLookupMap.Emplace(59, p059);

	PuzzleLetterLookupMap.Emplace(60, p060);
	PuzzleLetterLookupMap.Emplace(61, p061);
	PuzzleLetterLookupMap.Emplace(62, p062);
	PuzzleLetterLookupMap.Emplace(63, p063);
	PuzzleLetterLookupMap.Emplace(64, p064);
	PuzzleLetterLookupMap.Emplace(65, p065);
	PuzzleLetterLookupMap.Emplace(66, p066);
	PuzzleLetterLookupMap.Emplace(67, p067);
	PuzzleLetterLookupMap.Emplace(68, p068);
	PuzzleLetterLookupMap.Emplace(69, p069);

	PuzzleLetterLookupMap.Emplace(70, p070);
	PuzzleLetterLookupMap.Emplace(71, p071);
	PuzzleLetterLookupMap.Emplace(72, p072);
	PuzzleLetterLookupMap.Emplace(73, p073);
	PuzzleLetterLookupMap.Emplace(74, p074);
	PuzzleLetterLookupMap.Emplace(75, p075);
	PuzzleLetterLookupMap.Emplace(76, p076);
	PuzzleLetterLookupMap.Emplace(77, p077);
	PuzzleLetterLookupMap.Emplace(78, p078);
	PuzzleLetterLookupMap.Emplace(79, p079);

	PuzzleLetterLookupMap.Emplace(80, p080);
	PuzzleLetterLookupMap.Emplace(81, p081);
	PuzzleLetterLookupMap.Emplace(82, p082);
	PuzzleLetterLookupMap.Emplace(83, p083);
	PuzzleLetterLookupMap.Emplace(84, p084);
	PuzzleLetterLookupMap.Emplace(85, p085);
	PuzzleLetterLookupMap.Emplace(86, p086);
	PuzzleLetterLookupMap.Emplace(87, p087);
	PuzzleLetterLookupMap.Emplace(88, p088);
	PuzzleLetterLookupMap.Emplace(89, p089);

	PuzzleLetterLookupMap.Emplace(90, p090);
	PuzzleLetterLookupMap.Emplace(91, p091);
	PuzzleLetterLookupMap.Emplace(92, p092);
	PuzzleLetterLookupMap.Emplace(93, p093);
	PuzzleLetterLookupMap.Emplace(94, p094);
	PuzzleLetterLookupMap.Emplace(95, p095);
	PuzzleLetterLookupMap.Emplace(96, p096);
	PuzzleLetterLookupMap.Emplace(97, p097);
	PuzzleLetterLookupMap.Emplace(98, p098);
	PuzzleLetterLookupMap.Emplace(99, p099);

	PuzzleLetterLookupMap.Emplace(100, p100);
	PuzzleLetterLookupMap.Emplace(101, p101);
	PuzzleLetterLookupMap.Emplace(102, p102);
	PuzzleLetterLookupMap.Emplace(103, p103);
	PuzzleLetterLookupMap.Emplace(104, p104);
	PuzzleLetterLookupMap.Emplace(105, p105);
	PuzzleLetterLookupMap.Emplace(106, p106);
	PuzzleLetterLookupMap.Emplace(107, p107);
	PuzzleLetterLookupMap.Emplace(108, p108);
	PuzzleLetterLookupMap.Emplace(109, p109);

	PuzzleLetterLookupMap.Emplace(110, p110);
	PuzzleLetterLookupMap.Emplace(111, p111);
	PuzzleLetterLookupMap.Emplace(112, p112);
	PuzzleLetterLookupMap.Emplace(113, p113);
	PuzzleLetterLookupMap.Emplace(114, p114);
	PuzzleLetterLookupMap.Emplace(115, p115);
	PuzzleLetterLookupMap.Emplace(116, p116);
	PuzzleLetterLookupMap.Emplace(117, p117);
	PuzzleLetterLookupMap.Emplace(118, p118);
	PuzzleLetterLookupMap.Emplace(119, p119);

	PuzzleLetterLookupMap.Emplace(120, p120);
	PuzzleLetterLookupMap.Emplace(121, p121);
	PuzzleLetterLookupMap.Emplace(122, p122);
	PuzzleLetterLookupMap.Emplace(123, p123);
	PuzzleLetterLookupMap.Emplace(124, p124);
	PuzzleLetterLookupMap.Emplace(125, p125);
	PuzzleLetterLookupMap.Emplace(126, p126);
	PuzzleLetterLookupMap.Emplace(127, p127);
	PuzzleLetterLookupMap.Emplace(128, p128);
	PuzzleLetterLookupMap.Emplace(129, p129);

	PuzzleLetterLookupMap.Emplace(130, p130);
	PuzzleLetterLookupMap.Emplace(131, p131);
	PuzzleLetterLookupMap.Emplace(132, p132);
	PuzzleLetterLookupMap.Emplace(133, p133);
	PuzzleLetterLookupMap.Emplace(134, p134);
	PuzzleLetterLookupMap.Emplace(135, p135);
	PuzzleLetterLookupMap.Emplace(136, p136);
	PuzzleLetterLookupMap.Emplace(137, p137);
	PuzzleLetterLookupMap.Emplace(138, p138);
	PuzzleLetterLookupMap.Emplace(139, p139);

	PuzzleLetterLookupMap.Emplace(140, p140);
	PuzzleLetterLookupMap.Emplace(141, p141);
	PuzzleLetterLookupMap.Emplace(142, p142);
	PuzzleLetterLookupMap.Emplace(143, p143);
	PuzzleLetterLookupMap.Emplace(144, p144);
	PuzzleLetterLookupMap.Emplace(145, p145);
	PuzzleLetterLookupMap.Emplace(146, p146);
	PuzzleLetterLookupMap.Emplace(147, p147);
	PuzzleLetterLookupMap.Emplace(148, p148);
	PuzzleLetterLookupMap.Emplace(149, p149);

	PuzzleLetterLookupMap.Emplace(150, p150);
	PuzzleLetterLookupMap.Emplace(151, p151);
	PuzzleLetterLookupMap.Emplace(152, p152);
	PuzzleLetterLookupMap.Emplace(153, p153);
	PuzzleLetterLookupMap.Emplace(154, p154);
	PuzzleLetterLookupMap.Emplace(155, p155);
	PuzzleLetterLookupMap.Emplace(156, p156);
	PuzzleLetterLookupMap.Emplace(157, p157);
	PuzzleLetterLookupMap.Emplace(158, p158);
	PuzzleLetterLookupMap.Emplace(159, p159);

	PuzzleLetterLookupMap.Emplace(160, p160);
	PuzzleLetterLookupMap.Emplace(161, p161);
	PuzzleLetterLookupMap.Emplace(162, p162);
	PuzzleLetterLookupMap.Emplace(163, p163);
	PuzzleLetterLookupMap.Emplace(164, p164);
	PuzzleLetterLookupMap.Emplace(165, p165);
	PuzzleLetterLookupMap.Emplace(166, p166);
	PuzzleLetterLookupMap.Emplace(167, p167);
	PuzzleLetterLookupMap.Emplace(168, p168);
	PuzzleLetterLookupMap.Emplace(169, p169);

	PuzzleLetterLookupMap.Emplace(170, p170);
	PuzzleLetterLookupMap.Emplace(171, p171);
	PuzzleLetterLookupMap.Emplace(172, p172);
	PuzzleLetterLookupMap.Emplace(173, p173);
	PuzzleLetterLookupMap.Emplace(174, p174);
	PuzzleLetterLookupMap.Emplace(175, p175);
	PuzzleLetterLookupMap.Emplace(176, p176);
	PuzzleLetterLookupMap.Emplace(177, p177);
	PuzzleLetterLookupMap.Emplace(178, p178);
	PuzzleLetterLookupMap.Emplace(179, p179);

	PuzzleLetterLookupMap.Emplace(180, p180);
	PuzzleLetterLookupMap.Emplace(181, p181);
	PuzzleLetterLookupMap.Emplace(182, p182);
	PuzzleLetterLookupMap.Emplace(183, p183);
	PuzzleLetterLookupMap.Emplace(184, p184);
	PuzzleLetterLookupMap.Emplace(185, p185);
	PuzzleLetterLookupMap.Emplace(186, p186);
	PuzzleLetterLookupMap.Emplace(187, p187);
	PuzzleLetterLookupMap.Emplace(188, p188);
	PuzzleLetterLookupMap.Emplace(189, p189);

	PuzzleLetterLookupMap.Emplace(190, p190);
	PuzzleLetterLookupMap.Emplace(191, p191);
	PuzzleLetterLookupMap.Emplace(192, p192);
	PuzzleLetterLookupMap.Emplace(193, p193);
	PuzzleLetterLookupMap.Emplace(194, p194);
	PuzzleLetterLookupMap.Emplace(195, p195);
	PuzzleLetterLookupMap.Emplace(196, p196);
	PuzzleLetterLookupMap.Emplace(197, p197);
	PuzzleLetterLookupMap.Emplace(198, p198);
	PuzzleLetterLookupMap.Emplace(199, p199);

	PuzzleLetterLookupMap.Emplace(200, p200);

}

void UNewWorldBuild::FindAllGridStaticMeshes()
{
	GridsMap.Emplace(sz_7x4, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_7x4.SM_grid_7x4'"));
	GridsMap.Emplace(sz_7x3, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_7x3.SM_grid_7x3'"));
	GridsMap.Emplace(sz_7x2, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_7x2.SM_grid_7x2'"));

	GridsMap.Emplace(sz_6x4, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_6x4.SM_grid_6x4'"));
	GridsMap.Emplace(sz_6x3, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_6x3.SM_grid_6x3'"));
	GridsMap.Emplace(sz_6x2, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_6x2.SM_grid_6x2'"));

	GridsMap.Emplace(sz_5x4, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_5x4.SM_grid_5x4'"));
	GridsMap.Emplace(sz_5x3, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_5x3.SM_grid_5x3'"));
	GridsMap.Emplace(sz_5x2, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_5x2.SM_grid_5x2'"));

	GridsMap.Emplace(sz_4x4, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_4x4.SM_grid_4x4'"));
	GridsMap.Emplace(sz_4x3, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_4x3.SM_grid_4x3'"));
	GridsMap.Emplace(sz_4x2, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_4x2.SM_grid_4x2'"));

	GridsMap.Emplace(sz_3x4, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_3x4.SM_grid_3x4'"));
	GridsMap.Emplace(sz_3x3, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_3x3.SM_grid_3x3'"));
	GridsMap.Emplace(sz_3x2, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_3x2.SM_grid_3x2'"));

	GridsMap.Emplace(sz_2x4, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_2x4.SM_grid_2x4'"));
	GridsMap.Emplace(sz_2x3, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_2x3.SM_grid_2x3'"));
	GridsMap.Emplace(sz_2x2, FindAsset("StaticMesh'/Game/Meshes/Grids/SM_grid_2x2.SM_grid_2x2'"));
}

UStaticMesh* UNewWorldBuild::FindAsset(FString Name)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset((TEXT("%s"), *Name));
	return Asset.Object;
}

void UNewWorldBuild::CreateRoomLetterArrayForRandomRoomLetters()
{
	//loop rooms
	for (auto& Room : GameInstance->RoomMap) {

		////skip oD
		//if (Room.Key == oD) {
		//	continue;
		//}

		RoomLetterArray.Emplace(Room.Key);
	}
}



// GATHER INFO

TEnumAsByte <E_RoomLetter> UNewWorldBuild::GetRandomRoomLetter()
{
	int32 RandIndex = FMath::RandRange(0, RoomLetterArray.Num() - 1);

	return RoomLetterArray[RandIndex];
}

bool UNewWorldBuild::bIsTablePlacementPossible(TEnumAsByte <E_RoomLetter> RoomLetter, int32 Col, int32 Row)
{
	//condense
	TMap<TEnumAsByte <E_RoomLetter>, FRoomUnit>& RoomMap = GameInstance->RoomMap;

	//if these four adjacent squares are vacant
	if (RoomMap[RoomLetter].ColMap[Col].RowMap[Row].TotMap[1].TotemType == tVACANT) {
		if (RoomMap[RoomLetter].ColMap[Col + 1].RowMap[Row].TotMap[1].TotemType == tVACANT) {
			if (RoomMap[RoomLetter].ColMap[Col].RowMap[Row + 1].TotMap[1].TotemType == tVACANT) {
				if (RoomMap[RoomLetter].ColMap[Col + 1].RowMap[Row + 1].TotMap[1].TotemType == tVACANT) {
					return true;
				}
			}
		}
	}

	return false;
}

// BUILD

void UNewWorldBuild::BuildANewWorld(UTheGameInstance* _GameInstance)
{
	Setup(_GameInstance);

//Build Random Grid Configuration

	URandomGridGeneration* RandomGrid = NewObject<URandomGridGeneration>(this, URandomGridGeneration::StaticClass());

	RandomGrid->CatchTheBuilder(this);
	RandomGrid->CatchTheGameInstance(_GameInstance);
	RandomGrid->BuildAllPossibleGridArray();
	RandomGrid->BuildPuzzleSizeArray();


//Build Rooms

	Build_Rooms();
	Build_TotemPoles();
	Build_DoorInformation();

	Build_Puzzles();
	Set_PuzzleGridHeightAndWidths();
	Set_GridStaticMeshes();
	Set_MuralTextures();
	Set_BordersOnMurals();

	Build_PuzzleGridMaps();
	Build_PuzzleBinMaps();

	CreateRoomLetterArrayForRandomRoomLetters();
	Place_PuzzlesIntoRooms();


	Populate_FloorTotems();
	Populate_FinaleTotems();
	Populate_DoorTotems();
	Populate_VesselTotems();

//Build Pieces

	//build pieces
	UPieceMaker* PieceMaker = NewObject<UPieceMaker>(this, UPieceMaker::StaticClass());
	PieceMaker->CatchTheGameInstance(GameInstance);
	PieceMaker->BuildFullAndRandomlyCutPieces();
	PieceMaker->CreateClusters();
	PieceMaker->FillJoinMaps();

	//if start in bin
	if (GameInstance->DebugSettings.WherePiecesWillStart == INBIN) {
		PieceMaker->PiecesWillStartInBin();

		//put pieces into containers
		PieceMaker->PlacePiecesIntoRespectiveContainers();
	}
	//if start in vessels
	else if (GameInstance->DebugSettings.WherePiecesWillStart == INVESSEL) {
		PieceMaker->PiecesWillStartInVessels();
	}
	//if start in grid
	else if (GameInstance->DebugSettings.WherePiecesWillStart == ONGRID) {

		PieceMaker->PiecesWillStartInGrid();

		//put pieces into containers
		PieceMaker->PlacePiecesIntoRespectiveContainers();
	}
	else {
		//shouldn't need
	} 
}


void UNewWorldBuild::Build_Rooms()
{
	//condense
	TMap<TEnumAsByte <E_RoomLetter>, FRoomUnit>& RoomMap = GameInstance->RoomMap;

	// gen
	if (TempleSize == GEN) {

		RoomMap.Emplace(oD, FRoomUnit());

		RoomMap[oD].RoomLetter = oD;
	}

	// genya
	if (TempleSize == GENYA) {
		RoomMap.Emplace(oA, FRoomUnit());
		RoomMap.Emplace(oB, FRoomUnit());
		RoomMap.Emplace(oC, FRoomUnit());
		RoomMap.Emplace(oD, FRoomUnit());
		RoomMap.Emplace(oE, FRoomUnit());
		RoomMap.Emplace(oF, FRoomUnit());
		RoomMap.Emplace(oG, FRoomUnit());

		RoomMap[oA].RoomLetter = oA;
		RoomMap[oB].RoomLetter = oB;
		RoomMap[oC].RoomLetter = oC;
		RoomMap[oD].RoomLetter = oD;
		RoomMap[oE].RoomLetter = oE;
		RoomMap[oF].RoomLetter = oF;
		RoomMap[oG].RoomLetter = oG;
	}

	// genyati
	if (TempleSize == GENYATI) {
		RoomMap.Emplace(oA, FRoomUnit());
		RoomMap.Emplace(oB, FRoomUnit());
		RoomMap.Emplace(oC, FRoomUnit());
		RoomMap.Emplace(oD, FRoomUnit());
		RoomMap.Emplace(oE, FRoomUnit());
		RoomMap.Emplace(oF, FRoomUnit());
		RoomMap.Emplace(oG, FRoomUnit());
		RoomMap.Emplace(oH, FRoomUnit());
		RoomMap.Emplace(oI, FRoomUnit());
		RoomMap.Emplace(oJ, FRoomUnit());
		RoomMap.Emplace(oK, FRoomUnit());
		RoomMap.Emplace(oL, FRoomUnit());
		RoomMap.Emplace(oM, FRoomUnit());
		RoomMap.Emplace(oN, FRoomUnit());
		RoomMap.Emplace(oO, FRoomUnit());
		RoomMap.Emplace(oP, FRoomUnit());
		RoomMap.Emplace(oQ, FRoomUnit());
		RoomMap.Emplace(oR, FRoomUnit());
		RoomMap.Emplace(oS, FRoomUnit());


		RoomMap[oA].RoomLetter = oA;
		RoomMap[oB].RoomLetter = oB;
		RoomMap[oC].RoomLetter = oC;
		RoomMap[oD].RoomLetter = oD;
		RoomMap[oE].RoomLetter = oE;
		RoomMap[oF].RoomLetter = oF;
		RoomMap[oG].RoomLetter = oG;
		RoomMap[oH].RoomLetter = oH;
		RoomMap[oI].RoomLetter = oI;
		RoomMap[oJ].RoomLetter = oJ;
		RoomMap[oK].RoomLetter = oK;
		RoomMap[oL].RoomLetter = oL;
		RoomMap[oM].RoomLetter = oM;
		RoomMap[oN].RoomLetter = oN;
		RoomMap[oO].RoomLetter = oO;
		RoomMap[oP].RoomLetter = oP;
		RoomMap[oQ].RoomLetter = oQ;
		RoomMap[oR].RoomLetter = oR;
		RoomMap[oS].RoomLetter = oS;
	}

	// genyatium
	if (TempleSize == GENYATIUM) {
		RoomMap.Emplace(oA, FRoomUnit());
		RoomMap.Emplace(oB, FRoomUnit());
		RoomMap.Emplace(oC, FRoomUnit());
		RoomMap.Emplace(oD, FRoomUnit());
		RoomMap.Emplace(oE, FRoomUnit());
		RoomMap.Emplace(oF, FRoomUnit());
		RoomMap.Emplace(oG, FRoomUnit());
		RoomMap.Emplace(oH, FRoomUnit());
		RoomMap.Emplace(oI, FRoomUnit());
		RoomMap.Emplace(oJ, FRoomUnit());
		RoomMap.Emplace(oK, FRoomUnit());
		RoomMap.Emplace(oL, FRoomUnit());
		RoomMap.Emplace(oM, FRoomUnit());
		RoomMap.Emplace(oN, FRoomUnit());
		RoomMap.Emplace(oO, FRoomUnit());
		RoomMap.Emplace(oP, FRoomUnit());
		RoomMap.Emplace(oQ, FRoomUnit());
		RoomMap.Emplace(oR, FRoomUnit());
		RoomMap.Emplace(oS, FRoomUnit());
		RoomMap.Emplace(o1, FRoomUnit());
		RoomMap.Emplace(o2, FRoomUnit());
		RoomMap.Emplace(o3, FRoomUnit());
		RoomMap.Emplace(o4, FRoomUnit());
		RoomMap.Emplace(o5, FRoomUnit());
		RoomMap.Emplace(o6, FRoomUnit());
		RoomMap.Emplace(o7, FRoomUnit());
		RoomMap.Emplace(o8, FRoomUnit());
		RoomMap.Emplace(o9, FRoomUnit());
		RoomMap.Emplace(o10, FRoomUnit());
		RoomMap.Emplace(o11, FRoomUnit());
		RoomMap.Emplace(o12, FRoomUnit());
		RoomMap.Emplace(o13, FRoomUnit());
		RoomMap.Emplace(o14, FRoomUnit());
		RoomMap.Emplace(o15, FRoomUnit());
		RoomMap.Emplace(o16, FRoomUnit());
		RoomMap.Emplace(o17, FRoomUnit());
		RoomMap.Emplace(o18, FRoomUnit());


		RoomMap[oA].RoomLetter = oA;
		RoomMap[oB].RoomLetter = oB;
		RoomMap[oC].RoomLetter = oC;
		RoomMap[oD].RoomLetter = oD;
		RoomMap[oE].RoomLetter = oE;
		RoomMap[oF].RoomLetter = oF;
		RoomMap[oG].RoomLetter = oG;
		RoomMap[oH].RoomLetter = oH;
		RoomMap[oI].RoomLetter = oI;
		RoomMap[oJ].RoomLetter = oJ;
		RoomMap[oK].RoomLetter = oK;
		RoomMap[oL].RoomLetter = oL;
		RoomMap[oM].RoomLetter = oM;
		RoomMap[oN].RoomLetter = oN;
		RoomMap[oO].RoomLetter = oO;
		RoomMap[oP].RoomLetter = oP;
		RoomMap[oQ].RoomLetter = oQ;
		RoomMap[oR].RoomLetter = oR;
		RoomMap[oS].RoomLetter = oS;
		RoomMap[o1].RoomLetter = o1;
		RoomMap[o2].RoomLetter = o2;
		RoomMap[o3].RoomLetter = o3;
		RoomMap[o4].RoomLetter = o4;
		RoomMap[o5].RoomLetter = o5;
		RoomMap[o6].RoomLetter = o6;
		RoomMap[o7].RoomLetter = o7;
		RoomMap[o8].RoomLetter = o8;
		RoomMap[o9].RoomLetter = o9;
		RoomMap[o10].RoomLetter = o10;
		RoomMap[o11].RoomLetter = o11;
		RoomMap[o12].RoomLetter = o12;
		RoomMap[o13].RoomLetter = o13;
		RoomMap[o14].RoomLetter = o14;
		RoomMap[o15].RoomLetter = o15;
		RoomMap[o16].RoomLetter = o16;
		RoomMap[o17].RoomLetter = o17;
		RoomMap[o18].RoomLetter = o18;
	}
}

void UNewWorldBuild::Build_TotemPoles()
{
	//condense
	TMap<TEnumAsByte <E_RoomLetter>, FRoomUnit>& RoomMap = GameInstance->RoomMap;

	//loop rooms
	for (auto& Room : RoomMap) {

		//build 40 ColTots
		for (int32 col = 1; col <= 40; col++) {

			FColTot NewColTot = FColTot();

			//build 20 RowTots
			for (int32 row = 1; row <= 20; row++) {

				FRowTot NewRowTot = FRowTot();

				//set RowTot Room_Address
				NewRowTot.Room_Address.RoomLetter = Room.Value.RoomLetter;
				NewRowTot.Room_Address.Col = col;
				NewRowTot.Room_Address.Row = row;
				NewRowTot.Room_Address.Tot = 0;

				//build 6 Tots  -1, 0(floor), 1, 2, 3, 4, 5
				for (int32 tot = -1; tot <= 5; tot++) {

					FTotemUnit NewTotemUnit = FTotemUnit();

					//set Totem Room_Address
					NewTotemUnit.Room_Address.RoomLetter = Room.Value.RoomLetter;
					NewTotemUnit.Room_Address.Col = col;
					NewTotemUnit.Room_Address.Row = row;
					NewTotemUnit.Room_Address.Tot = tot;

					//add
					NewRowTot.TotMap.Emplace(tot, NewTotemUnit);
				}

				//add
				NewColTot.RowMap.Emplace(row, NewRowTot);
			}

			//add
			Room.Value.ColMap.Emplace(col, NewColTot);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("should be 40: %i"), RoomMap[oA].ColMap.Num())
	//UE_LOG(LogTemp, Warning, TEXT("should be 20: %i"), RoomMap[oB].ColMap[1].RowMap.Num())
	//UE_LOG(LogTemp, Warning, TEXT("should be 7: %i"), RoomMap[oC].ColMap[1].RowMap[1].TotMap.Num())
} 

void UNewWorldBuild::Build_DoorInformation()
{
	//condense
	TMap<TEnumAsByte <E_RoomLetter>, FRoomUnit>& RoomMap = GameInstance->RoomMap;

	if (TempleSize == GEN) {
		//no doors
	}
	if (TempleSize == GENYA) {

		for (auto& Room : RoomMap) {
			
			if (Room.Key == oA) {
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oB) {
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oC) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oD) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oE) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
			}
			else if (Room.Key == oF) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
			}
			else if (Room.Key == oG) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
			}
		}
	}
	if (TempleSize == GENYATI) {
		
		for (auto& Room : RoomMap) {

			if (Room.Key == oH) {
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oI) {
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oJ) {
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oK) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oL) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oM) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oN) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
			}
			else if (Room.Key == oO) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == oP) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
			}
			else if (Room.Key == oQ) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
			}
			else if (Room.Key == oR) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
			}
			else if (Room.Key == oS) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
			}
			//middle rooms
			else {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
		}
	}
	if (TempleSize == GENYATIUM) {

		for (auto& Room : RoomMap) {

			if (Room.Key == o1) {
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o2) {
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o3) {
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o4) {
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o5) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o6) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o7) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o8) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o9) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o10) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
			}
			else if (Room.Key == o11) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o12) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
			}
			else if (Room.Key == o13) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
			else if (Room.Key == o14) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
			}
			else if (Room.Key == o15) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
			}
			else if (Room.Key == o16) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
			}
			else if (Room.Key == o17) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
			}
			else if (Room.Key == o18) {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
			}
			//middle rooms
			else {
				PlaceDoorAtThisPosition(Room.Key, dd_TopLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_TopRight);
				PlaceDoorAtThisPosition(Room.Key, dd_Left);
				PlaceDoorAtThisPosition(Room.Key, dd_Right);
				PlaceDoorAtThisPosition(Room.Key, dd_BotLeft);
				PlaceDoorAtThisPosition(Room.Key, dd_BotRight);
			}
		}
	}
}

void UNewWorldBuild::PlaceDoorAtThisPosition(TEnumAsByte<E_RoomLetter> RoomLetter, TEnumAsByte<E_DoorDirection> DoorDirection)
{
	//condense
	TMap<TEnumAsByte <E_RoomLetter>, FRoomUnit>& RoomMap = GameInstance->RoomMap;

	//build struct
	RoomMap[RoomLetter].DoorLayout.Emplace(DoorDirection, FDoorInformation());

	//condense
	FDoorInformation& DoorInfo = RoomMap[RoomLetter].DoorLayout[DoorDirection];

	//build appendages
	DoorInfo.AppendageTri2 = FMath::RandRange(0, 1);
	DoorInfo.AppendageTri3 = FMath::RandRange(0, 2);
	DoorInfo.AppendageTri4 = FMath::RandRange(0, 1);
	DoorInfo.AppendageTri5 = FMath::RandRange(0, 2);
	DoorInfo.AppendageTri6 = FMath::RandRange(0, 1);

	//get door destination
	URoomNavigator* RoomNavigator = NewObject<URoomNavigator>(this, URoomNavigator::StaticClass());
	DoorInfo.DoorDestination = RoomNavigator->DetermineTheNewRoomLetter(RoomLetter, DoorDirection);
}



//POPULATE ROOMS

void UNewWorldBuild::Populate_FloorTotems()
{
	//loop rooms
	for (auto& Room : GameInstance->RoomMap) {

		//loop cols
		for (auto& Col : Room.Value.ColMap) {

			//loop rows
			for (auto& Row : Col.Value.RowMap) {
				Row.Value.TotMap[0].TotemType = tFLOOR;
			}
		}
	}
}

void UNewWorldBuild::Populate_FinaleTotems()
{
	//loop relevant rows
	for (int32 row = 1; row <= 4; row++) {

		if (row == 1 || row == 2) {
			//loop relevant cols
			for (int32 col = 15; col <= 26; col++) {
				//loop tots
				for (int32 tot = 1; tot <= 5; tot++) {
					GameInstance->RoomMap[oD].ColMap[col].RowMap[row].TotMap[tot].TotemType = tFINALE;
				}
			}
		}
		if (row == 3) {
			//loop relevant cols
			for (int32 col = 18; col <= 23; col++) {
				//loop tots
				for (int32 tot = 1; tot <= 5; tot++) {
					GameInstance->RoomMap[oD].ColMap[col].RowMap[row].TotMap[tot].TotemType = tFINALE;
				}
			}
		}
		if (row == 4) {
			//loop relevant cols
			for (int32 col = 19; col <= 22; col++) {
				//loop tots
				for (int32 tot = 1; tot <= 5; tot++) {
					GameInstance->RoomMap[oD].ColMap[col].RowMap[row].TotMap[tot].TotemType = tFINALE;
				}
			}
		}
	}
}

void UNewWorldBuild::Populate_DoorTotems()
{
	//loop rooms
	for (auto& Room : GameInstance->RoomMap) {
		//loop layout
		for (auto& DoorInfo : Room.Value.DoorLayout) {

			//TopLeft
			if (DoorInfo.Key == dd_TopLeft) {

				//loop relevant rows
				for (int32 row = 1; row <= 3; row++) {

					//first row
					if (row == 1) {

						//loop relevant cols
						for (int32 col = 6; col <= 13; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
					//next two rows
					else {

						//loop relevant cols
						for (int32 col = 8; col <= 11; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
				}
			}

			//TopRight
			if (DoorInfo.Key == dd_TopRight) {

				//loop relevant rows
				for (int32 row = 1; row <= 3; row++) {

					//first row
					if (row == 1) {

						//loop relevant cols
						for (int32 col = 28; col <= 35; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
					//next two rows
					else {

						//loop relevant cols
						for (int32 col = 30; col <= 33; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
				}
			}

			//Left
			if (DoorInfo.Key == dd_Left) {

				//loop relevant cols
				for (int32 col = 1; col <= 3; col++) {

					//first col
					if (col == 1) {

						//loop relevant rows
						for (int32 row = 7; row <= 14; row++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
					//next two cols
					else {

						//loop relevant rows
						for (int32 row = 9; row <= 12; row++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
				}
			}

			//Right
			if (DoorInfo.Key == dd_Right) {

				//loop relevant cols
				for (int32 col = 40; col >= 38; col--) {

					//first col
					if (col == 40) {

						//loop relevant rows
						for (int32 row = 7; row <= 14; row++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
					//next two cols
					else {

						//loop relevant rows
						for (int32 row = 9; row <= 12; row++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
				}
			}

			//BotLeft
			if (DoorInfo.Key == dd_BotLeft) {

				//loop relevant rows
				for (int32 row = 20; row >= 18; row--) {

					//first row
					if (row == 20) {

						//loop relevant cols
						for (int32 col = 6; col <= 13; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
					//next two rows
					else {

						//loop relevant cols
						for (int32 col = 8; col <= 11; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
				}
			}

			//BotRight
			if (DoorInfo.Key == dd_BotRight) {

				//loop relevant rows
				for (int32 row = 20; row >= 18; row--) {

					//first row
					if (row == 20) {

						//loop relevant cols
						for (int32 col = 28; col <= 35; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
					//next two rows
					else {

						//loop relevant cols
						for (int32 col = 30; col <= 33; col++) {
							//loop tots
							for (int32 tot = 1; tot <= 5; tot++) {
								GameInstance->RoomMap[Room.Key].ColMap[col].RowMap[row].TotMap[tot].TotemType = tDOOR;
							}
						}
					}
				}
			}
		}
	}
}

void UNewWorldBuild::Populate_VesselTotems()
{
	//loop rooms
	for (auto& Room : GameInstance->RoomMap) {

		//loop 2000 times
		for (int32 i = 1; i <= 2000; i++) {

			//if Totem is stacked full, it will not place a Vessel.  That means less than 2000 will show up.

			//get random Col and Row
			int32 RandCol = FMath::RandRange(1, 40);
			int32 RandRow = FMath::RandRange(1, 20);

			//condense
			TMap<int32, FTotemUnit>& TotMap= Room.Value.ColMap[RandCol].RowMap[RandRow].TotMap;

			//loop TotMap, minus floor
			for (int32 tot = 0; tot <= 5; tot++) {

				//nothing above these items
				if (
					TotMap[tot].TotemType == tJUNCTION	||
					TotMap[tot].TotemType == tTABLE		||
					TotMap[tot].TotemType == tFINALE	||
					TotMap[tot].TotemType == tDOOR
					) 
				{
					//this will break early instead of going up totem
					break;
				}

				//eligible to place a vessel
				if (TotMap[tot].TotemType == tVACANT) {

					//place only one vessel
					TotMap[tot].TotemType = tVESSEL;
					TotMap[tot].VesselType = GetRandomVessel();

					//exit early
					break;
				}
			}
		}
	}
}

TEnumAsByte<E_VesselType> UNewWorldBuild::GetRandomVessel()
{
	int32 RandNum = FMath::RandRange(1, 6);

	switch (RandNum) {
		case 1:		return v_VASE;
		case 2:		return v_SUITCASE_NEW;
		case 3:		return v_BARREL;
		case 4:		return v_CHEST;
		case 5:		return v_CRATE;
		case 6:		return v_CARDBOARDBOX;
		default:	return v_VASE;
	}
}

void UNewWorldBuild::Build_Puzzles()
{
	//condense
	TMap<TEnumAsByte <E_PuzzleLetter>, FPuzzleUnit>& PuzzleMap = GameInstance->PuzzleMap;

	//build junction
	PuzzleMap.Emplace(pJUNCTION, FPuzzleUnit());
	PuzzleMap[pJUNCTION].PuzzleLetter = pJUNCTION;
	PuzzleMap[pJUNCTION].Room_Address = FRoom_Address();
	PuzzleMap[pJUNCTION].bIsDiscovered = true;
	GameInstance->DiscoveredPuzzlesArr.Emplace(pJUNCTION);

	UE_LOG(LogTemp, Warning, TEXT("puzzle size array = %i"), PuzzleSizeArray.Num())

	//build each puzzle
	for (int32 i = 0; i < PuzzleSizeArray.Num(); i++) {

		TEnumAsByte <E_PuzzleLetter> PuzzleLetter = PuzzleLetterLookupMap[i+1];

		PuzzleMap.Emplace(PuzzleLetter, FPuzzleUnit());
		PuzzleMap[PuzzleLetter].PuzzleLetter = PuzzleLetter;
		PuzzleMap[PuzzleLetter].Room_Address = FRoom_Address();
		PuzzleMap[PuzzleLetter].GridSize = PuzzleSizeArray[i];

		//debug check
		if (GameInstance->DebugSettings.bEveryPuzzleAlreadyDiscovered == true) {
			PuzzleMap[PuzzleLetter].bIsDiscovered = true;
			GameInstance->DiscoveredPuzzlesArr.Emplace(PuzzleLetter);
		}
	}
}

void UNewWorldBuild::Build_PuzzleGridMaps()
{
	//condense
	TMap<TEnumAsByte <E_PuzzleLetter>, FPuzzleUnit>& PuzzleMap = GameInstance->PuzzleMap;

	//loop puzzles
	for (auto& Puzzle : PuzzleMap) {

		//condense
		int32 PuzzleGridWidth = Puzzle.Value.PuzzleGridWidth;
		int32 RowHeight = Puzzle.Value.PuzzleGridHeight * 2;

		//build ColHexs
		for (int32 col = 1; col <= PuzzleGridWidth; col++) {

			FColHex NewColHex = FColHex();

			//if odd, rows should be 2,4,6, etc.
			if (col % 2 == 1) {

				//build RowHexes, start at 2, iterate by 2
				for (int32 row = 2; row <= RowHeight; row += 2) {

					FRowHex NewRowHex = FRowHex();

					//set RowHex Table_Address
					NewRowHex.Table_Address.PuzzleLetter = Puzzle.Value.PuzzleLetter;
					NewRowHex.Table_Address.Board = GRID;
					NewRowHex.Table_Address.Col = col;
					NewRowHex.Table_Address.Row = row;
					NewRowHex.Table_Address.Tri = 0;

					//build 6 Tris
					for (int32 tri = 1; tri <= 6; tri++) {

						FTriangleUnit NewTriUnit = FTriangleUnit();

						//set Tri Table_Address
						NewTriUnit.Table_Address.PuzzleLetter = Puzzle.Value.PuzzleLetter;
						NewTriUnit.Table_Address.Board = GRID;
						NewTriUnit.Table_Address.Col = col;
						NewTriUnit.Table_Address.Row = row;
						NewTriUnit.Table_Address.Tri = tri;

						//add
						NewRowHex.TriMap.Emplace(tri, NewTriUnit);
					}

					//add
					NewColHex.RowMap.Emplace(row, NewRowHex);
				}
			}

			//if even, rows should be 1,3,5, etc.
			if (col % 2 == 0) {

				//build RowHexes, start at 1, iterate by 2
				for (int32 row = 1; row <= RowHeight; row += 2) {

					FRowHex NewRowHex = FRowHex();

					//set RowHex Table_Address
					NewRowHex.Table_Address.PuzzleLetter = Puzzle.Value.PuzzleLetter;
					NewRowHex.Table_Address.Board = GRID;
					NewRowHex.Table_Address.Col = col;
					NewRowHex.Table_Address.Row = row;
					NewRowHex.Table_Address.Tri = 0;

					//build 6 Tris
					for (int32 tri = 1; tri <= 6; tri++) {

						FTriangleUnit NewTriUnit = FTriangleUnit();

						//set Tri Table_Address
						NewTriUnit.Table_Address.PuzzleLetter = Puzzle.Value.PuzzleLetter;
						NewTriUnit.Table_Address.Board = GRID;
						NewTriUnit.Table_Address.Col = col;
						NewTriUnit.Table_Address.Row = row;
						NewTriUnit.Table_Address.Tri = tri;

						//add
						NewRowHex.TriMap.Emplace(tri, NewTriUnit);
					}

					//add
					NewColHex.RowMap.Emplace(row, NewRowHex);
				}
			}

			//add
			Puzzle.Value.ColMapGrid.Emplace(col, NewColHex);
		}
	}


	
}

void UNewWorldBuild::Build_PuzzleBinMaps()
{
	//condense
	TMap<TEnumAsByte <E_PuzzleLetter>, FPuzzleUnit>& PuzzleMap = GameInstance->PuzzleMap;

	//loop puzzles
	for (auto& Puzzle : PuzzleMap) {

		//set ColAmount and RowAmount
		int32 ColAmount;
		int32 RowAmount;

		//if junction
		if (Puzzle.Key == pJUNCTION) {
			ColAmount = 25; //24 columns
			RowAmount = 24; //12 rows
		}
		//if standard puzzle
		else {
			ColAmount = 15; //14 columns
			RowAmount = 12; //6 rows
		}

		//build ColHexs - Start at 2 to keep alignment of even cols being higher
		for (int32 col = 2; col <= ColAmount; col++) {

			FColHex NewColHex = FColHex();

			//set StartRow
			int32 StartRow;

			//if odd, 2,4,6, etc.
			if (col % 2 == 1) {
				StartRow = 2;
			}
			//if even, 1,3,5, etc.
			else {
				StartRow = 1;
			}

			//build RowHexes, start at 2, iterate by 2
			for (int32 row = StartRow; row <= RowAmount; row += 2) {

				FRowHex NewRowHex = FRowHex();

				//set RowHex Table_Address
				NewRowHex.Table_Address.PuzzleLetter = Puzzle.Value.PuzzleLetter;
				NewRowHex.Table_Address.Board = BIN;
				NewRowHex.Table_Address.Col = col;
				NewRowHex.Table_Address.Row = row;
				NewRowHex.Table_Address.Tri = 0;

				//build 6 Tris
				for (int32 tri = 1; tri <= 6; tri++) {

					FTriangleUnit NewTriUnit = FTriangleUnit();

					//set Tri Table_Address
					NewTriUnit.Table_Address.PuzzleLetter = Puzzle.Value.PuzzleLetter;
					NewTriUnit.Table_Address.Board = BIN;
					NewTriUnit.Table_Address.Col = col;
					NewTriUnit.Table_Address.Row = row;
					NewTriUnit.Table_Address.Tri = tri;

					//add
					NewRowHex.TriMap.Emplace(tri, NewTriUnit);
				}

				//add
				NewColHex.RowMap.Emplace(row, NewRowHex);
			}
			
			//add
			Puzzle.Value.ColMapBin.Emplace(col, NewColHex);
		}
	}
}

// SET FURTHER

void UNewWorldBuild::Set_PuzzleGridHeightAndWidths()
{
	//loop puzzles
	for (auto& Puzzle : GameInstance->PuzzleMap) {

		if (Puzzle.Value.GridSize == sz_7x4) {
			Puzzle.Value.PuzzleGridWidth = 7;
			Puzzle.Value.PuzzleGridHeight = 4;
		}
		else if (Puzzle.Value.GridSize == sz_7x3) {
			Puzzle.Value.PuzzleGridWidth = 7;
			Puzzle.Value.PuzzleGridHeight = 3;
		}
		else if (Puzzle.Value.GridSize == sz_7x2) {
			Puzzle.Value.PuzzleGridWidth = 7;
			Puzzle.Value.PuzzleGridHeight = 2;
		}

		else if (Puzzle.Value.GridSize == sz_6x4) {
			Puzzle.Value.PuzzleGridWidth = 6;
			Puzzle.Value.PuzzleGridHeight = 4;
		}
		else if (Puzzle.Value.GridSize == sz_6x3) {
			Puzzle.Value.PuzzleGridWidth = 6;
			Puzzle.Value.PuzzleGridHeight = 3;
		}
		else if (Puzzle.Value.GridSize == sz_6x2) {
			Puzzle.Value.PuzzleGridWidth = 6;
			Puzzle.Value.PuzzleGridHeight = 2;
		}

		else if (Puzzle.Value.GridSize == sz_5x4) {
			Puzzle.Value.PuzzleGridWidth = 5;
			Puzzle.Value.PuzzleGridHeight = 4;
		}
		else if (Puzzle.Value.GridSize == sz_5x3) {
			Puzzle.Value.PuzzleGridWidth = 5;
			Puzzle.Value.PuzzleGridHeight = 3;
		}
		else if (Puzzle.Value.GridSize == sz_5x2) {
			Puzzle.Value.PuzzleGridWidth = 5;
			Puzzle.Value.PuzzleGridHeight = 2;
		}

		else if (Puzzle.Value.GridSize == sz_4x4) {
			Puzzle.Value.PuzzleGridWidth = 4;
			Puzzle.Value.PuzzleGridHeight = 4;
		}
		else if (Puzzle.Value.GridSize == sz_4x3) {
			Puzzle.Value.PuzzleGridWidth = 4;
			Puzzle.Value.PuzzleGridHeight = 3;
		}
		else if (Puzzle.Value.GridSize == sz_4x2) {
			Puzzle.Value.PuzzleGridWidth = 4;
			Puzzle.Value.PuzzleGridHeight = 2;
		}

		else if (Puzzle.Value.GridSize == sz_3x4) {
			Puzzle.Value.PuzzleGridWidth = 3;
			Puzzle.Value.PuzzleGridHeight = 4;
		}
		else if (Puzzle.Value.GridSize == sz_3x3) {
			Puzzle.Value.PuzzleGridWidth = 3;
			Puzzle.Value.PuzzleGridHeight = 3;
		}
		else if (Puzzle.Value.GridSize == sz_3x2) {
			Puzzle.Value.PuzzleGridWidth = 3;
			Puzzle.Value.PuzzleGridHeight = 2;
		}

		else if (Puzzle.Value.GridSize == sz_2x4) {
			Puzzle.Value.PuzzleGridWidth = 2;
			Puzzle.Value.PuzzleGridHeight = 4;
		}
		else if (Puzzle.Value.GridSize == sz_2x3) {
			Puzzle.Value.PuzzleGridWidth = 2;
			Puzzle.Value.PuzzleGridHeight = 3;
		}
		else if (Puzzle.Value.GridSize == sz_2x2) {
			Puzzle.Value.PuzzleGridWidth = 2;
			Puzzle.Value.PuzzleGridHeight = 2;
		}

	}
}

void UNewWorldBuild::Set_GridStaticMeshes()
{
	//loop puzzles
	for (auto& Puzzle : GameInstance->PuzzleMap) {

		//fetch mesh for gridmap
		Puzzle.Value.GridStaticMesh = GridsMap[Puzzle.Value.GridSize];
	}
}

void UNewWorldBuild::Set_MuralTextures()
{
	UMuralManager* MuralManager = NewObject<UMuralManager>(GameInstance, UMuralManager::StaticClass());

	//loop puzzles
	for (auto& MapObject : GameInstance->PuzzleMap) {

		//condense
		FPuzzleUnit* Puzzle = &MapObject.Value;

		//set border pointers
		Puzzle->BorderTexture = MuralManager->GetProperBorderTexture(Puzzle->GridSize);
		Puzzle->BorderMask = MuralManager->GetProperBorderMask(Puzzle->GridSize);

		//set mural info
		Puzzle->MuralTexture_ID = MuralManager->GetProperTexture_ID(Puzzle->GridSize, GameInstance->DebugSettings.bUseDebugTexture);
		Puzzle->MuralTexture = MuralManager->GetProperTexture(Puzzle->MuralTexture_ID);
	}
}

void UNewWorldBuild::Set_BordersOnMurals()
{
	//store border percentage
	float b_percentage = GameInstance->TempleSettings.PercentageOfPuzzlesWithBorders;

	//debug setting
	if (GameInstance->DebugSettings.bAllBorders == true) {
		b_percentage = 1.f;
	}

	//total number of puzzles, convert to float
	float total = float(GameInstance->PuzzleMap.Num());

	//percentage * total, round
	int32 BorderCount = FMath::RoundHalfFromZero(total * b_percentage);

	//loop puzzles
	for (auto& Puzzle : GameInstance->PuzzleMap) {
		if (BorderCount > 0) {

			UE_LOG(LogTemp, Warning, TEXT("BORDERED!!!!"))
			Puzzle.Value.bIsBordered = true;
			BorderCount--;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("------ NOT BORDERED!!!!"))
			Puzzle.Value.bIsBordered = false;
		}
	}
}

void UNewWorldBuild::Place_PuzzlesIntoRooms()
{
	//condense
	TMap<TEnumAsByte <E_PuzzleLetter>, FPuzzleUnit>& PuzzleMap = GameInstance->PuzzleMap;
	TMap<TEnumAsByte <E_RoomLetter>, FRoomUnit>& RoomMap = GameInstance->RoomMap;

	//create array to house puzzles that need to be placed
	TArray<TEnumAsByte <E_PuzzleLetter>> PuzzlesToPlaceArray;

	//loop puzzles
	for (auto& Puzzle : PuzzleMap) {

		//skip pJUNCTION
		if (Puzzle.Key == pJUNCTION) {
			continue;
		}

		PuzzlesToPlaceArray.Emplace(Puzzle.Key);
	}

	//PUT JUNCTION TABLE DOWN

		//origin spot
		RoomMap[oD].ColMap[19].RowMap[9].TotMap[1].bIsOrigin = true;

		//adjacent spots
		for (int32 col = 18; col <= 23; col++) {
			for (int32 row = 9; row <= 12; row++) {

				if (col == 18 && (row == 9 || row == 12)) {
					continue;
				}

				if (col == 23 && (row == 9 || row == 12)) {
					continue;
				}

				RoomMap[oD].ColMap[col].RowMap[row].TotMap[1].TotemType = tJUNCTION;
				RoomMap[oD].ColMap[col].RowMap[row].TotMap[1].PuzzleLetter = pJUNCTION;
			}
		}

		//change puzzle info Room_Address
		PuzzleMap[pJUNCTION].Room_Address.RoomLetter = oD;
		PuzzleMap[pJUNCTION].Room_Address.Col = 19;
		PuzzleMap[pJUNCTION].Room_Address.Row = 9;
		PuzzleMap[pJUNCTION].Room_Address.Tot = 1;

	//PUT THREE PUZZLES INTO ROOM oD
		for (int32 i = 0; i < 3; /* No Iteration Here */) {
			int32 col = FMath::RandRange(3, 37);
			int32 row = FMath::RandRange(3, 18);
	
			if (bIsTablePlacementPossible(oD, col, row)) {
			
				UE_LOG(LogTemp, Warning, TEXT("Placement possible"))

				//safety
				if (PuzzlesToPlaceArray.Num() == 0) {
					break;
				}

				//take random puzzle
				int32 RandIndex = FMath::RandRange(0, PuzzlesToPlaceArray.Num() - 1);
				TEnumAsByte <E_PuzzleLetter> PuzzleLetter = PuzzlesToPlaceArray[RandIndex];
				PuzzlesToPlaceArray.RemoveAt(RandIndex);
	
				//origin spot
				RoomMap[oD].ColMap[col].RowMap[row].TotMap[1].bIsOrigin = true;
	
				//adjacent spots
				RoomMap[oD].ColMap[col].RowMap[row].TotMap[1].TotemType = tTABLE;
				RoomMap[oD].ColMap[col].RowMap[row].TotMap[1].PuzzleLetter = PuzzleLetter;
				RoomMap[oD].ColMap[col + 1].RowMap[row].TotMap[1].TotemType = tTABLE;
				RoomMap[oD].ColMap[col + 1].RowMap[row].TotMap[1].PuzzleLetter = PuzzleLetter;
				RoomMap[oD].ColMap[col].RowMap[row + 1].TotMap[1].TotemType = tTABLE;
				RoomMap[oD].ColMap[col].RowMap[row + 1].TotMap[1].PuzzleLetter = PuzzleLetter;
				RoomMap[oD].ColMap[col + 1].RowMap[row + 1].TotMap[1].TotemType = tTABLE;
				RoomMap[oD].ColMap[col + 1].RowMap[row + 1].TotMap[1].PuzzleLetter = PuzzleLetter;

				//change puzzle info Room_Address
				PuzzleMap[PuzzleLetter].Room_Address.RoomLetter = oD;
				PuzzleMap[PuzzleLetter].Room_Address.Col = col;
				PuzzleMap[PuzzleLetter].Room_Address.Row = row;
				PuzzleMap[PuzzleLetter].Room_Address.Tot = 1;
	
				//iterate i
				i++;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Placement NOT POSSIBLE"))
			}
			//if its not possible, don't iterate and try again
	
		}

		int32 AmountOfPuzzlesLeft = PuzzlesToPlaceArray.Num();

	//PUT REST OF PUZZLES IN RANDOM ROOMS, EXCEPT oD
		for (int32 i = 0; i < AmountOfPuzzlesLeft; /* No Iteration Here */) {
			int32 col = FMath::RandRange(3, 37);
			int32 row = FMath::RandRange(3, 18);
			TEnumAsByte <E_RoomLetter> RoomLetter = GetRandomRoomLetter();

			if (bIsTablePlacementPossible(RoomLetter, col, row)) {

				UE_LOG(LogTemp, Warning, TEXT("Placement possible"))

				//take random puzzle
				int32 RandIndex = FMath::RandRange(0, PuzzlesToPlaceArray.Num() - 1);
				TEnumAsByte <E_PuzzleLetter> PuzzleLetter = PuzzlesToPlaceArray[RandIndex];
				PuzzlesToPlaceArray.RemoveAt(RandIndex);

				//origin spot
				RoomMap[RoomLetter].ColMap[col].RowMap[row].TotMap[1].bIsOrigin = true;

				//adjacent spots
				RoomMap[RoomLetter].ColMap[col].RowMap[row].TotMap[1].TotemType = tTABLE;
				RoomMap[RoomLetter].ColMap[col].RowMap[row].TotMap[1].PuzzleLetter = PuzzleLetter;
				RoomMap[RoomLetter].ColMap[col + 1].RowMap[row].TotMap[1].TotemType = tTABLE;
				RoomMap[RoomLetter].ColMap[col + 1].RowMap[row].TotMap[1].PuzzleLetter = PuzzleLetter;
				RoomMap[RoomLetter].ColMap[col].RowMap[row + 1].TotMap[1].TotemType = tTABLE;
				RoomMap[RoomLetter].ColMap[col].RowMap[row + 1].TotMap[1].PuzzleLetter = PuzzleLetter;
				RoomMap[RoomLetter].ColMap[col + 1].RowMap[row + 1].TotMap[1].TotemType = tTABLE;
				RoomMap[RoomLetter].ColMap[col + 1].RowMap[row + 1].TotMap[1].PuzzleLetter = PuzzleLetter;

				//change puzzle info Room_Address
				PuzzleMap[PuzzleLetter].Room_Address.RoomLetter = RoomLetter;
				PuzzleMap[PuzzleLetter].Room_Address.Col = col;
				PuzzleMap[PuzzleLetter].Room_Address.Row = row;
				PuzzleMap[PuzzleLetter].Room_Address.Tot = 1;

				//iterate i
				i++;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Placement NOT POSSIBLE"))
			}
			//if its not possible, don't iterate and try again
		}
}