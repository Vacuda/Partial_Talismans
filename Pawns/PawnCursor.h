// Copyright 2020 Vacuda

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Talismans/Structs/FTable_Address.h"  					// for Table_Address
#include "Talismans/Enums/E_Direction.h"						// for Direction
#include "PawnCursor.generated.h"

class AActorPiece;
class UCluster;
class UPiece;
class UHub;
class UPaperSpriteComponent;

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
	void D_Pad_Left();
	void D_Pad_Right();

	void GrabReleaseConfirm();
	void Rotate();
	void ToggleTransferSackMode();


// CHANGE INFO

	void DeterminePerformMovement();
	void PerformMovement();
	void GivePermissionToMove();
	void RunRadialChoiceModeChecks();
	void ExitRadialChoiceMode();
	TEnumAsByte<E_Direction> CombineCardinalDirections();
	void HandlePickingUpCluster(UCluster* GrabbedCluster);
	void HandleDroppingCluster(UCluster* DroppedCluster);
	void ExitChecks();
	void MoveToElement_Right();
	void MoveToElement_Left();
	void SendCursorToThisCoordinate(int32 col, int32 row, TEnumAsByte<E_Board> Board);
	void ArmDisarmItemPiece(UPiece* ItemPiece);

// MEMBERS - SETUP

	UPROPERTY()
		UHub* Hub;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SceneCursor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* CursorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperSpriteComponent* TransferSack;


// MEMBERS - CONTROL

	UPROPERTY()
		bool bHasPermissionToMove = true;
	UPROPERTY()
		bool bIsRadialChoiceMode = false;
	UPROPERTY()
		bool bIsTransferSackMode = false;
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
		float LeftRightValue;
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
		TArray<UCluster*> InHand;
	UPROPERTY()
		TArray<UCluster*> InSack;
	UPROPERTY()
		TEnumAsByte<E_Direction> ProposedDirection = d_NONE;
	UPROPERTY()
		FTable_Address Table_Address;
	UPROPERTY()
		FVector CurrentLocation;
	UPROPERTY()
		TArray<UCluster*> AllMovableClusters;
	UPROPERTY()
		UCluster* SelectedClusterPtr = nullptr;
	UPROPERTY()
		bool bSkipLeftRightTick = false;

};
