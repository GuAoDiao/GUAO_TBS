// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/DecisionMakers/IDecisionMaker.h"

#include "CoreMinimal.h"

class FAutoDecisionMaker : public IDecisionMaker
{
public:
	virtual void BeginMakeDecision(class ACombatPawn* CombatPawn) override;
	virtual bool MakeDecision(float DeltaSeconds) override;


	bool FindMinHPEnemy(int32& OutMinHPTeam, int32& OutMinHPEnemy) const;
	bool FindTargetEnemy(int32& OutTargetTeam, TArray<int32>& OutTargetEnemy) const;


protected:
	class ACombatPawn* OwnerCombatPawn;
	class ACombatManager* CombatManager;

	float RemainingTime;
};
