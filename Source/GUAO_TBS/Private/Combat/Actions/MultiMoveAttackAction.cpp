// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiMoveAttackAction.h"

#include "GameFramework/TBSGameAssetManager.h"
#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MoveAction.h"

#include "Combat/CombatCapabilities/MultiDamageCapabilities.h"

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
	if (OwnerCombatPawn)
	{
		TArray<ACombatPawn*> AttackTargetPawn;
		for (int32 TargetPawnIndex : TargetIndex)
		{
			AttackTargetPawn.Add(CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetPawnIndex].CombatPawn);
		}

		UMultiDamageCapabilities* MultiMoveAttackCapabilities = Cast<UMultiDamageCapabilities>(FTBSGameAssetManager::GetInstance()->GetCombatCapabilities(ECombatCapabilitiesType::MultiDamage));
		if (MultiMoveAttackCapabilities)
		{
			MultiMoveAttackCapabilities->InitializeCombatCapabilities(OwnerCombatPawn->GetWorld(), TEXT("1"));
			MultiMoveAttackCapabilities->SetOwnerAndAttackTarget(OwnerCombatPawn, AttackTargetPawn);
			MultiMoveAttackCapabilities->UseCombatCapabilities();
		}
	}
}