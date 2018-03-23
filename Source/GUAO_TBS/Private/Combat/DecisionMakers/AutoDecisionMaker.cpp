// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoDecisionMaker.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MonomerMoveAttackAction.h"
#include "Combat/Actions/MultiMoveAttackAction.h"
#include "Combat/Actions/DoNothingAction.h"

void FAutoDecisionMaker::BeginMakeDecision(class ACombatPawn* CombatPawn)
{
	RemainingTime = 1.f;

	OwnerCombatPawn = CombatPawn;
	CombatManager = CombatPawn->GetCombatManager();

	checkf(CombatManager, TEXT("-_- the combat manager must exist"));
	
	if (FMath::RandRange(0.f, 1000.f) / 10.f < 20.f)
	{
		int32 TargetTeam = -1;
		TArray<int32> TargetEnemy;
		if (FindTargetEnemy(TargetTeam, TargetEnemy))
		{
			CombatPawn->SetCombatAction(new FMultiMoveAttackAction(TargetTeam, TargetEnemy));
			return;
		}
	}
	else
	{
		int32 MinHPTeam = -1;
		int32 MinHPEnemy = -1;
		if (FindMinHPEnemy(MinHPTeam, MinHPEnemy))
		{
			CombatPawn->SetCombatAction(new FMonomerMoveAttackAction(MinHPTeam, MinHPEnemy));
			return;
		}
	}

	CombatPawn->SetCombatAction(new FDoNothingAction());
}
bool FAutoDecisionMaker::MakeDecision(float DeltaSeconds)
{
	RemainingTime -= DeltaSeconds;
	if (RemainingTime <= 0.f)
	{
		return true;
	}

	return false;
}

bool FAutoDecisionMaker::FindMinHPEnemy(int32& OutMinHPTeam, int32& OutMinHPEnemy) const
{
	if (!CombatManager) { return false; }

	float MinHP = FLT_MAX;
	for (int32 i = 0; i < CombatManager->AllTeamsInfo.Num(); ++i)
	{
		if (OwnerCombatPawn && i == OwnerCombatPawn->CombatTeam) { continue; }

		for (int32 j = 0; j < CombatManager->AllTeamsInfo[i].AllCombatPawnInfo.Num(); ++j)
		{
			ACombatPawn* TargetCombatPawn = CombatManager->AllTeamsInfo[i].AllCombatPawnInfo[j].CombatPawn;
			if (TargetCombatPawn && !TargetCombatPawn->IsCombatPawnDead() && TargetCombatPawn->Health < MinHP)
			{
				OutMinHPTeam = i;
				OutMinHPEnemy = j;
				MinHP = TargetCombatPawn->Health;
			}
		}
	}

	return MinHP != FLT_MAX;
}

bool FAutoDecisionMaker::FindTargetEnemy(int32& OutTargetTeam, TArray<int32>& OutTargetEnemy) const
{
	if (!CombatManager) { return false; }

	for (int32 i = 0; i < CombatManager->AllTeamsInfo.Num(); ++i)
	{
		if (OwnerCombatPawn && i == OwnerCombatPawn->CombatTeam) { continue; }

		for (int32 j = 0; j < CombatManager->AllTeamsInfo[i].AllCombatPawnInfo.Num(); ++j)
		{
			ACombatPawn* TargetCombatPawn = CombatManager->AllTeamsInfo[i].AllCombatPawnInfo[j].CombatPawn;
			if (TargetCombatPawn && !TargetCombatPawn->IsCombatPawnDead())
			{
				OutTargetEnemy.Add(j);
			}
		}

		if (OutTargetEnemy.Num() > 0)
		{
			OutTargetTeam = i;
			return true;
		}
	}

	return false;
}