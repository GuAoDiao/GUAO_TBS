// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiMoveAttackAction.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MoveAction.h"

FMultiMoveAttackAction::FMultiMoveAttackAction(int32 InTargetTeam, TArray<int32> InTargetIndex)
{
	TargetTeam = InTargetTeam;
	TargetIndex = InTargetIndex;
}

FVector FMultiMoveAttackAction::GetTargetLocation()
{
	checkf(CombatManager->AllTeamsInfo.IsValidIndex(TargetTeam), TEXT("-_- the attack target team must exist"));

	return CombatManager->AllTeamsInfo[TargetTeam].TeamCommonAttackLocation;
}

void FMultiMoveAttackAction::AttackImplementation()
{
	for (int32 TargetPawnIndex : TargetIndex)
	{
		ACombatPawn* TargetPawn = CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetPawnIndex].CombatPawn;
		if (TargetPawn)
		{
			float Damage = (OwnerCombatPawn->Attack - TargetPawn->Defence) * 0.7f;

			float Luck = OwnerCombatPawn->Luck - TargetPawn->Luck;
			if (FMath::RandRange(0.f, 1000.f) / 10.f < Luck)
			{
				Damage *= 2.f;
				UE_LOG(LogTemp, Warning, TEXT("-_- good luck, critical attack"));
			}

			TargetPawn->AcceptDamage(Damage, OwnerCombatPawn);
		}
	}
}