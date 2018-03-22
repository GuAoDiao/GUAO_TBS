// Fill out your copyright notice in the Description page of Project Settings.

#include "RunAwayAction.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"

void FRunAwayAction::BeginExecuteAction(class ACombatPawn* CombatPawn)
{
	OwnerCombatPawn = CombatPawn;
}

bool FRunAwayAction::ExecuteAction(float DeltaSeconds)
{
	ACombatManager* CombatManager = OwnerCombatPawn ? OwnerCombatPawn->GetCombatManager() : nullptr;
	if (CombatManager)
	{
		return CombatManager->TryToRunAway(OwnerCombatPawn);
	}

	return true;
}