// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Talismans/Structs/FTable_Address.h"  					// for Table_Address
#include "Talismans/Enums/E_Direction.h"						// for Direction
#include "PawnCursor.generated.h"

class AMeshPiece;
class ACluster;
class UHub;

UCLASS()
class TALISMANS_API APawnCursor : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	APawnCursor();
	virtual void Tick(float DeltaTime) override;
	

// SETUP
	
	void SetStartPosition();
	void CatchTheHub(UHub* _Hub);
	
// CONTROL
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void CalculateLeftRight(float Value);
	void CalculateUpDown(float Value);
	void GrabRelease();
	void Rotate();
	void Flip();

// CHANGE INFO

	void DeterminePerformMovement();
	void PerformMovement();
	void GivePermissionToMove();
	void RunRadialChoiceModeChecks();
	void ExitRadialChoiceMode();
	TEnumAsByte<E_Direction> CombineCardinalDirections();
	void HandlePickingUpCluster(ACluster* GrabbedCluster);
	void HandleDroppingCluster(ACluster* DroppedCluster);
	void ExitChecks();
	void MoveToElement_Right();
	void MoveToElement_Left();
	void SendCursorToThisCoordinate(int32 col, int32 row, TEnumAsByte<E_Board> Board);

// MEMBERS - SETUP

	UPROPERTY()
		UHub* Hub;
	UPROPERTY()
		UStaticMeshComponent* CursorMesh;


// MEMBERS - CONTROL

	UPROPERTY()
		bool bHasPermissionToMove = true;
	UPROPERTY()
		bool bIsRadialChoiceMode = false;
	UPROPERTY()
		bool bEndingRadialChoiceModeTrigger = false;
	UPROPERTY()
		FTimerHandle MoveDelayTimerHandle;
	UPROPERTY()
		bool bIsMoveDelayFuzeActive = false;
	UPROPERTY()
		float MoveDelay = 0.16f;
	UPROPERTY()
		float UpDownValue;
	UPROPERTY()
		TEnumAsByte<E_Direction> UpDown = d_NONE;
	UPROPERTY()
		TEnumAsByte<E_Direction> LeftRight = d_NONE;
	UPROPERTY()
		float AxisThreshold = 0.5f;
	UPROPERTY()
		int32 TriPick = 0;
	UPROPERTY()
		float HoverAmount = 5.f;


// MEMBERS - DYNAMIC INFO

	UPROPERTY()
		TArray<ACluster*> InHand;
	UPROPERTY()
		TEnumAsByte<E_Direction> ProposedDirection = d_NONE;
	UPROPERTY()
		FTable_Address Table_Address;
	UPROPERTY()
		FVector CurrentLocation;
	UPROPERTY()
		TArray<ACluster*> AllMovableClusters;
	UPROPERTY()
		ACluster* SelectedClusterPtr = nullptr;


};
