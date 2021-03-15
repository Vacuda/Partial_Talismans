// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Talismans/Structs/FTable_Address.h"					// for Table_Address
#include "Talismans/Enums/E_PieceState.h"						// for PieceState
#include "Cluster.generated.h"

class UPiece;
class AActorCluster;

UCLASS()
class TALISMANS_API UCluster : public UObject
{
	GENERATED_BODY()

public:

	UCluster();

//SETUP


//MEMBERS

	UPROPERTY()
		int32 cID;

	UPROPERTY()
		FTable_Address Table_Address;
	UPROPERTY()
		TArray<UPiece*> HeldPieces;
	UPROPERTY()
		AActorCluster* ActorClusterPtr;
	UPROPERTY()
		FTable_Address PickedUpAddress;

	UPROPERTY()
		TEnumAsByte <E_PieceState> State;






	//stored to repopulate HeldPieces
	UPROPERTY()
		TArray<int32> HeldPieces_ID;

};
