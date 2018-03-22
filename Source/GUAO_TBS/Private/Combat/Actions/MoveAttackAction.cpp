// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveAttackAction.h"

#include "CoreMinimal.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatManager.h"
#include "Combat/Actions/MoveAction.h"

void FMoveAttackAction::BeginExecuteAction(class ACombatPawn* CombatPawn)
{
	AttackAnimationTime = 1.f;
	CurrentAttackState = EAttackState::Ready;
	OwnerCombatPawn = CombatPawn;
	CombatManager = OwnerCombatPawn ? OwnerCombatPawn->GetCombatManager() : nullptr;

	checkf(CombatManager, TEXT("-_- the combat manager must exist"));

	OriginLocation = OwnerCombatPawn->GetActorLocation();
	OriginRotatiton = OwnerCombatPawn->GetActorRotation();

	MoveAction = new FMoveAction(GetTargetLocation());
	MoveAction->BeginExecuteAction(OwnerCombatPawn);
	CurrentAttackState = EAttackState::MoveToAttackLocation;
}

bool FMoveAttackAction::ExecuteAction(float DeltaSeconds)
{
	switch (CurrentAttackState)
	{
		case EAttackState::MoveToAttackLocation:
		case EAttackState::MoveToOrigin:
		{
			if (MoveAction && MoveAction->ExecuteAction(DeltaSeconds))
			{
				delete MoveAction;
				MoveAction = nullptr;

				CurrentAttackState = CurrentAttackState == EAttackState::MoveToAttackLocation ? EAttackState::Attack : EAttackState::Finished;
			}
			break;
		}
		case EAttackState::Attack:
		{
			OwnerCombatPawn->ToggleToTargetCombatPawnState(ECombatPawnState::Attack);

			AttackImplementation();

			if (MoveAction) { delete MoveAction; }
			MoveAction = nullptr;

			CurrentAttackState = EAttackState::WaitAttackFinished;

			break;
		}
		case EAttackState::WaitAttackFinished:
		{
			AttackAnimationTime -= DeltaSeconds;
			if (AttackAnimationTime <= 0.f)
			{
				MoveAction = new FMoveAction(OriginLocation);
				MoveAction->BeginExecuteAction(OwnerCombatPawn);

				CurrentAttackState = EAttackState::MoveToOrigin;
			}
			break;
		}
		case EAttackState::Finished:
		{
			if (MoveAction) { delete MoveAction; }
			MoveAction = nullptr;

			OwnerCombatPawn->ToggleToTargetCombatPawnState(ECombatPawnState::Idle);
			OwnerCombatPawn->SetActorLocationAndRotation(OriginLocation, OriginRotatiton);
			return true;
		}
	}

	return false;
}
