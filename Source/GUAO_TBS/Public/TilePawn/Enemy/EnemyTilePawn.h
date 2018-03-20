// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn/TilePawn.h"
#include "EnemyTilePawn.generated.h"


class ATBSCharacter;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API AEnemyTilePawn : public ATilePawn
{
	GENERATED_BODY()
	
public:
	AEnemyTilePawn();

	void FightWith(ATBSCharacter* InPlayer);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatPawn> OwnerCombatEnemyClass;
};
