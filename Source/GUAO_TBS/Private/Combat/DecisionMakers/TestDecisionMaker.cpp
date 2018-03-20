// Fill out your copyright notice in the Description page of Project Settings.

#include "TestDecisionMaker.h"

#include "CoreMinimal.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/AttackAction.h"
#include "Combat/Actions/DoNothingAction.h"

void FTestDecisionMaker::BeginMakeDecision(class ACombatPawn* Character)
{
	ACombatManager* CombatManager =Character->GetCombatManager();

	if (CombatManager)
	{
		for (int32 i = 0; i < CombatManager->AllTeamsInfo.Num(); ++i)
		{
			if (i == Character->CombatTeam) { continue; }

			for (int32 j = 0; j < CombatManager->AllTeamsInfo[i].AllCombatPawnInfo.Num(); ++j)
			{
				if (CombatManager->AllTeamsInfo[i].AllCombatPawnInfo[j].CombatPawn && !CombatManager->AllTeamsInfo[i].AllCombatPawnInfo[j].CombatPawn->bIsDead)
				{
					Character->SetCombatAction(new FAttackAction(i, j));
					return;
				}
			}
		}
	}

	Character->SetCombatAction(new FDoNothingAction());
}
bool FTestDecisionMaker::MakeDecision(float DeltaSeconds)
{
	return true;
}