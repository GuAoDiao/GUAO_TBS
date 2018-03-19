// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn/TilePawn.h"
#include "EnemyPawn.generated.h"


class ATBSCharacter;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API AEnemyPawn : public ATilePawn
{
	GENERATED_BODY()
	
public:
	AEnemyPawn();

	void FightWith(ATBSCharacter* InPlayer);
	
	
};
