// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatCapabilities.h"
#include "MultiDamageCapabilities.generated.h"

class ACombatPawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UMultiDamageCapabilities : public UCombatCapabilities
{
	GENERATED_BODY()
	
	
public:
	void SetOwnerAndAttackTarget(ACombatPawn* InOwnerPawn, const TArray<ACombatPawn*>& InAttackTarget);
protected:
	virtual void ParseStringToInfo(const FString& Info);
	virtual void OnUseCombatCapabilities();

	float DamagePercent;
	ACombatPawn* OwnerPawn;
	TArray<ACombatPawn*> AttackTarget;
	
};
