// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDecisionMakerUI.h"

#include "Combat/CombatPawn.h"
#include "Combat/Actions/AttackAction.h"
#include "Combat/Actions/DoNothingAction.h"
#include "Combat/Actions/RunAwayAction.h"

void UPlayerDecisionMakerUI::BeginMakeDecision(class ACombatPawn* CombatPawn)
{
	OwnerCombatPawn = CombatPawn;

	RemainingTime = 30.f;
	bHasMadeDecision = false;
}

bool UPlayerDecisionMakerUI::MakeDecision(float DeltaSeconds)
{
	RemainingTime -= DeltaSeconds;
	if (RemainingTime <= 0.f)
	{
		return true;
	}

	UpdateRemainintTimeDisplay((int32)RemainingTime);

	return bHasMadeDecision;
}

void UPlayerDecisionMakerUI::MakeDoNothingAction()
{
	if (OwnerCombatPawn)
	{
		OwnerCombatPawn->SetCombatAction(new FDoNothingAction());
		bHasMadeDecision = true;
	}
}

void UPlayerDecisionMakerUI::MakeCommonAttackAction(int32 TargetTeam, int32 TargetEnemy)
{
	if (OwnerCombatPawn)
	{
		OwnerCombatPawn->SetCombatAction(new FAttackAction(TargetTeam, TargetEnemy));
		bHasMadeDecision = true;
	}
}

void UPlayerDecisionMakerUI::MakeRunAwayAction()
{
	if (OwnerCombatPawn)
	{
		OwnerCombatPawn->SetCombatAction(new FRunAwayAction());
		bHasMadeDecision = true;
	}
}