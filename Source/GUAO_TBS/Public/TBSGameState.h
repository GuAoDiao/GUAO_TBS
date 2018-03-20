// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "TBSTypes.h"

#include "TBSGameState.generated.h"

class ACombatManager;
class ACombatPawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATBSGameState();

	UFUNCTION(BlueprintCallable, Exec)
	void BeginCombat(FCombatTeam& EnemyTeam);
	UFUNCTION(BlueprintCallable)
	void CloseCombat();
	

protected:
	UPROPERTY(EditDefaultsOnly)
	FVector CombatLocation;
	
	TArray<FCombatTeam> AllCombatTeam;
	int32 PlayerTeamNum;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatManager> CombatManagerClass;
	UPROPERTY(Transient)
	ACombatManager* CombatManager;
};
