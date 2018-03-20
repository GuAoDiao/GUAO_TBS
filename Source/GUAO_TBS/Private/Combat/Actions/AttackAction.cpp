// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAction.h"

#include "CoreMinimal.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MoveAction.h"

FAttackAction::FAttackAction(int32 InTargetTeam, int32 InTargetIndex)
{
	TargetTeam = InTargetTeam;
	TargetIndex = InTargetIndex;
}


void FAttackAction::BeginExecuteAction(class ACombatPawn* Character)
{
	TempTime = 1.f;

	ACombatManager* CombatManager = Character ? Character->GetCombatManager() : nullptr;
	if (CombatManager)
	{
		ACombatPawn* CombatPawn = 
			CombatManager->AllTeamsInfo.IsValidIndex(TargetTeam) && CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo.IsValidIndex(TargetIndex)
			? CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetIndex].CombatPawn : nullptr;
		
		if (CombatPawn)
		{
			TargetPawn = CombatPawn;
			

			OnwenCombatPawn = Character;
			OriginLocation = OnwenCombatPawn->GetActorLocation();
			OriginRotatiton = OnwenCombatPawn->GetActorRotation();
			
			MoveAction = new FMoveAction(CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetIndex].CommonAttackLocation);
			MoveAction->BeginExecuteAction(OnwenCombatPawn);
			bIsMoving = true;
			bIsAttacked = false;
			bIsWaitForAttack = false;
		}
	}
}

bool FAttackAction::ExecuteAction(float DeltaSeconds)
{
	if (MoveAction && bIsMoving)
	{
		if (MoveAction->ExecuteAction(DeltaSeconds))
		{
			delete MoveAction;
			MoveAction = nullptr;
			
			bIsMoving = false;
		}
	}
	else if (bIsWaitForAttack)
	{
		TempTime -= DeltaSeconds;
		if (TempTime <= 0.f)
		{
			MoveAction = new FMoveAction(OriginLocation);
			MoveAction->BeginExecuteAction(OnwenCombatPawn);

			bIsAttacked = true;
			bIsMoving = true;
			bIsWaitForAttack = false;
		}
	}
	else
	{
		if (bIsAttacked)
		{
			delete MoveAction;
			MoveAction = nullptr;

			OnwenCombatPawn->BeginIdleAnimation();
			OnwenCombatPawn->SetActorLocationAndRotation(OriginLocation, OriginRotatiton);
			return true;
		}
		else
		{
			OnwenCombatPawn->BeginAttackAnimation();
			TargetPawn->AcceptDamage(OnwenCombatPawn->Attack - TargetPawn->Defence, OnwenCombatPawn);

			delete MoveAction;
			MoveAction = nullptr;
			bIsMoving = false;

			bIsWaitForAttack = true;
		}
	}

	return false;
}
