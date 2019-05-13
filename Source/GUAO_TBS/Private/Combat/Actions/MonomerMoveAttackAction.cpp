// Fill out your copyright notice in the Description page of Project Settings.

#include "MonomerMoveAttackAction.h"

#include "CoreMinimal.h"

#include "GameFramework/TBSGameAssetManager.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MoveAction.h"

#include "Combat/CombatCapabilities/MonomerDamageCapabilities.h"

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
		UMonomerDamageCapabilities* MonomerAttackCapabilities = Cast<UMonomerDamageCapabilities>(FTBSGameAssetManager::GetInstance()->GetCombatCapabilities(ECombatCapabilitiesType::MonomerDamage));
		if (MonomerAttackCapabilities)
		{
			MonomerAttackCapabilities->InitializeCombatCapabilities(OwnerCombatPawn->GetWorld(), TEXT("1"));
			MonomerAttackCapabilities->SetOwnerAndAttackTarget(OwnerCombatPawn, TargetPawn);
			MonomerAttackCapabilities->UseCombatCapabilities();
		}
	}
}