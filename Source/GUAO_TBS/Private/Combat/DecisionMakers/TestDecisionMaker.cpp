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
		int32 MinHPTeam = -1;
		int32 MinHPEnemy = -1;
		float MinHP = FLT_MAX;
		for (int32 i = 0; i < CombatManager->AllTeamsInfo.Num(); ++i)
		{
			if (i == Character->CombatTeam) { continue; }

			for (int32 j = 0; j < CombatManager->AllTeamsInfo[i].AllCombatPawnInfo.Num(); ++j)
			{
				ACombatPawn* CombatPawn = CombatManager->AllTeamsInfo[i].AllCombatPawnInfo[j].CombatPawn;
				if (CombatPawn && !CombatPawn->bIsDead)
				{
					if (CombatPawn->Health < MinHP)
					{
						MinHPTeam = i;
						MinHPEnemy = j;
						MinHP = CombatPawn->Health;
					}
				}
			}
		}

		if (MinHPTeam != -1 && MinHPEnemy != -1)
		{
			Character->SetCombatAction(new FAttackAction(MinHPTeam, MinHPEnemy));
			return;
		}
	}

	Character->SetCombatAction(new FDoNothingAction());
}
bool FTestDecisionMaker::MakeDecision(float DeltaSeconds)
{
	return true;
}