// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TBSPlayerController.generated.h"

class ATBSCharacter;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATBSPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//////////////////////////////////////////////////////////////////////////
	/// Set Pawn And Rebind Input
public:
	virtual void SetPawn(APawn* InPawn) override;
protected:
	void RebindInputComponent(UInputComponent* InInputComp);
	ATBSCharacter* OwnerTBSCharacter;

	//////////////////////////////////////////////////////////////////////////
	/// Viewport
public:
	/// Toggle View
	void TurnViewportToCombat(class ACombatManager* CombatManager);
	void TurnViewportToCharacter();

	/// Adjust Viewport Position
protected:
	void GetViewportRightBottomPosition();
	void MoveViewportFromMouse();
private:
	bool bCanMoveViewport;
	float ViewportRightPosition;
	float ViewportBottomPosition;	
};
