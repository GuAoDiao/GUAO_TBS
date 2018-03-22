// Fill out your copyright notice in the Description page of Project Settings.

#include "TestDecisionMaker.h"

#include "CoreMinimal.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/AttackAction.h"
#include "Combat/Actions/DoNothingAction.h"

void FTestDecisionMaker::BeginMakeDecision(class ACombatPawn* CombatPawn)
{
	ACombatManager* CombatManager = CombatPawn->GetCombatManager();

	if (CombatManager)
	{
		int32 MinHPTeam = -1;
		int32 MinHPEnemy = -1;
		float MinHP = FLT_MAX;
		for (int32 i = 0; i < CombatManager->AllTeamsInfo.Num(); ++i)
		{
			if (i == CombatPawn->CombatTeam) { continue; }

			for (int32 j = 0; j < CombatManager->AllTeamsInfo[i].AllCombatPawnInfo.Num(); ++j)
			{
				ACombatPawn* TargetCombatPawn = CombatManager->AllTeamsInfo[i].AllCombatPawnInfo[j].CombatPawn;
				if (TargetCombatPawn && !TargetCombatPawn->IsCombatPawnDead())
				{
					if (TargetCombatPawn->Health < MinHP)
					{
						MinHPTeam = i;
						MinHPEnemy = j;
						MinHP = TargetCombatPawn->Health;
					}
				}
			}
		}

		if (MinHPTeam != -1 && MinHPEnemy != -1)
		{
			CombatPawn->SetCombatAction(new FAttackAction(MinHPTeam, MinHPEnemy));
			return;
		}
	}

	CombatPawn->SetCombatAction(new FDoNothingAction());
}
bool FTestDecisionMaker::MakeDecision(float DeltaSeconds)
{
	return true;
}