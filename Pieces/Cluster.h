// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Talismans/Structs/FTable_Address.h"					// for Table_Address
#include "Talismans/Enums/E_PieceState.h"						// for PieceState
#include "Cluster.generated.h"

class APiece;
class AMeshCluster;

UCLASS()
class TALISMANS_API ACluster : public AActor
{
	GENERATED_BODY()

public:

	ACluster();

//SETUP


//MEMBERS

	UPROPERTY()
		FTable_Address Table_Address;
	UPROPERTY()
		TArray<APiece*> HeldPieces;
	UPROPERTY()
		AMeshCluster* MeshClusterPtr;
	UPROPERTY()
		FTable_Address PickedUpAddress;

	UPROPERTY()
		TEnumAsByte <E_PieceState> State;

};
