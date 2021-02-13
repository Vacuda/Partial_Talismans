// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Talismans/Enums/E_PieceState.h"					// for E_PieceState
#include "Talismans/Enums/E_PieceShape.h"					// for E_PieceShape
#include "Talismans/Structs/FTable_Address.h"				// for FTable_Address
#include "Talismans/Structs/FRoom_Address.h"				// for FRoom_Address
#include "Talismans/Pieces/Cluster.h"						// for Cluster
#include "Talismans/Pieces/MeshPiece.h"						// for MeshPiece
#include "Talismans/Enums/E_JoinSite.h"						// for E_JoinSite
#include "Talismans/Structs/FJoinUnit.h"					// for JoinUnit
#include "Piece.generated.h"

UCLASS()
class TALISMANS_API APiece : public AActor
{
	GENERATED_BODY()


public:	



	APiece();



	UPROPERTY()
		FTable_Address HomeTable_Address;
	UPROPERTY()
		FTable_Address Table_Address;
	UPROPERTY()
		FRoom_Address Room_Address;
	UPROPERTY()
		TEnumAsByte <E_PieceState> State;
	UPROPERTY()
		TEnumAsByte <E_PieceShape> Shape;
	UPROPERTY()
		ACluster* ClusterPtr = nullptr;
	UPROPERTY()
		AMeshPiece* MeshPiecePtr = nullptr;
	UPROPERTY()
		TMap<TEnumAsByte <E_JoinSite> , FJoinUnit> JoinMap;


	bool IsAtHome();

};
