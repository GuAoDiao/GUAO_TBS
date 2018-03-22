// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDecisionMakerUI.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MonomerMoveAttackAction.h"
#include "Combat/Actions/MultiMoveAttackAction.h"
#include "Combat/Actions/DoNothingAction.h"
#include "Combat/Actions/RunAwayAction.h"

void UPlayerDecisionMakerUI::BeginMakeDecision(class ACombatPawn* CombatPawn)
{
	OwnerCombatPawn = CombatPawn;

	RemainingTime = 15.f;
	bHasMadeDecision = false;
}

bool UPlayerDecisionMakerUI::MakeDecision(float DeltaSeconds)
{
	RemainingTime -= DeltaSeconds;
	if (RemainingTime <= 0.f)
	{
		MakeDoNothingAction();
		return true;
	}

	UpdateRemainintTimeDisplay((int32)RemainingTime);

	return bHasMadeDecision;
}

void UPlayerDecisionMakerUI::MakeCombatAction(class ICombatAction* CombatAction)
{
	checkf(OwnerCombatPawn, TEXT("-_- Owner Combat Pawn must exists."));
	OwnerCombatPawn->SetCombatAction(CombatAction);
	bHasMadeDecision = true;
}

void UPlayerDecisionMakerUI::MakeDoNothingAction() { MakeCombatAction(new FDoNothingAction()); }

void UPlayerDecisionMakerUI::MakeCommonAttackAction(int32 TargetTeam, int32 TargetEnemy) { MakeCombatAction(new FMonomerMoveAttackAction(TargetTeam, TargetEnemy)); }

void UPlayerDecisionMakerUI::MakeRunAwayAction() { MakeCombatAction(new FRunAwayAction()); }

void UPlayerDecisionMakerUI::MakeTeamAttackAction(int32 TargetTeam)
{
	ACombatManager* CombatManager = OwnerCombatPawn ? OwnerCombatPawn->GetCombatManager() : nullptr;
	checkf(OwnerCombatPawn, TEXT("-_- Owner Combat Manager must exists."));
	checkf(CombatManager->AllTeamsInfo.IsValidIndex(TargetTeam), TEXT("-_- The Attack Team must exists."));
	

	TArray<int32> AttackEnemys;
	for (int32 i = 0; i < CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo.Num(); ++i)
	{
		ACombatPawn* TargetCombatPawn = CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[i].CombatPawn;
		if (TargetCombatPawn && !TargetCombatPawn->IsCombatPawnDead())
		{
			AttackEnemys.Add(i);
		}
	}

	MakeCombatAction(new FMultiMoveAttackAction(TargetTeam, AttackEnemys));
}