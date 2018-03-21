// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "TBSTypes.h"

#include "TBSGameState.generated.h"

class ACombatManager;
class ACombatPawn;
class AEnemyTilePawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATBSGameState();

	UFUNCTION(BlueprintCallable)
	void BeginCombat(FCombatTeam& EnemyTeam);
	UFUNCTION(BlueprintCallable)
	void BeginCombatFromEnemyTilePawn(AEnemyTilePawn* EnemyTilePawn);

	UFUNCTION(BlueprintCallable)
	void CloseCombat(int32 WinTeam, bool bIsPlayerWin);
	

protected:
	UPROPERTY(EditDefaultsOnly)
	FVector CombatLocation;
	
	TArray<FCombatTeam> AllCombatTeam;
	int32 PlayerTeamNum;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatManager> CombatManagerClass;
	UPROPERTY(Transient)
	ACombatManager* CombatManager;
	UPROPERTY(Transient)
	AEnemyTilePawn* CurrentFightWithEnemyTilePawn;
};
