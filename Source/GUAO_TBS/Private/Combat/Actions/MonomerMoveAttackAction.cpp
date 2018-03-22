// Fill out your copyright notice in the Description page of Project Settings.

#include "MonomerMoveAttackAction.h"

#include "CoreMinimal.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MoveAction.h"

FMonomerMoveAttackAction::FMonomerMoveAttackAction(int32 InTargetTeam, int32 InTargetIndex)
{
	TargetTeam = InTargetTeam;
	TargetIndex = InTargetIndex;
}

FVector FMonomerMoveAttackAction::GetTargetLocation()
{
	TargetPawn =
		CombatManager->AllTeamsInfo.IsValidIndex(TargetTeam) && CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo.IsValidIndex(TargetIndex)
		? CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetIndex].CombatPawn : nullptr;

	checkf(TargetPawn, TEXT("-_- the attack target pawn must exist"));

	return CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetIndex].CommonAttackLocation;
}


void FMonomerMoveAttackAction::AttackImplementation()
{
	if (OwnerCombatPawn && TargetPawn)
	{
		float Damage = OwnerCombatPawn->Attack - TargetPawn->Defence;

		float Luck = OwnerCombatPawn->Luck - TargetPawn->Luck;
		if (FMath::RandRange(0.f, 1000.f) / 10.f < Luck)
		{
			Damage *= 2.f;
			UE_LOG(LogTemp, Warning, TEXT("-_- good luck, critical attack"));
		}

		TargetPawn->AcceptDamage(Damage, OwnerCombatPawn);
	}
}