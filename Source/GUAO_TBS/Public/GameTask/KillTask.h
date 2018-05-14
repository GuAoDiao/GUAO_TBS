// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTask/GameTask.h"
#include "KillTask.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UKillTask : public UGameTask
{
	GENERATED_BODY()
	
public:
	virtual void OnWaitForAcceptImplementation() override;
	virtual void OnAcceptImplementation() override;

	virtual void UpdateGameState() override;

	void OnKillCombatPawn(ACombatPawn* CombatPawn);
	
protected:
	TMap<int32, int32> EnemyInfo;
	TMap<int32, int32> CurrentKillInfo;

	FDelegateHandle KillCombatDelegate;
};
