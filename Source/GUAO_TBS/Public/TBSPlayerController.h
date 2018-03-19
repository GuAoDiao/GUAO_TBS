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
	/// Adjust Viewport Position
public:
	void GetViewportRightBottomPosition();
protected:
	void MoveViewportFromMouse();
private:
	float ViewportRightPosition;
	float ViewportBottomPosition;	
};
