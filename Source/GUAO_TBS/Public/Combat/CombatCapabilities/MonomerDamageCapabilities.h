// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatCapabilities.h"
#include "MonomerDamageCapabilities.generated.h"

class ACombatPawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UMonomerDamageCapabilities : public UCombatCapabilities
{
	GENERATED_BODY()
	
public :
	void SetOwnerAndAttackTarget(ACombatPawn* InOwnerPawn, ACombatPawn* InAttackTarget);
protected:
	virtual void ParseStringToInfo(const FString& Info);
	virtual void OnUseCombatCapabilities();
	
	float DamagePercent;
	ACombatPawn* OwnerPawn;
	ACombatPawn* AttackTarget;
};
