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
	CurrentAttackState = EAttackState::Ready;

	ACombatManager* CombatManager = Character ? Character->GetCombatManager() : nullptr;
	if (CombatManager)
	{
		ACombatPawn* CombatPawn = 
			CombatManager->AllTeamsInfo.IsValidIndex(TargetTeam) && CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo.IsValidIndex(TargetIndex)
			? CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetIndex].CombatPawn : nullptr;
		
		if (CombatPawn)
		{
			TargetPawn = CombatPawn;
			

			OwnerCombatPawn = Character;
			OriginLocation = OwnerCombatPawn->GetActorLocation();
			OriginRotatiton = OwnerCombatPawn->GetActorRotation();
			
			MoveAction = new FMoveAction(CombatManager->AllTeamsInfo[TargetTeam].AllCombatPawnInfo[TargetIndex].CommonAttackLocation);
			MoveAction->BeginExecuteAction(OwnerCombatPawn);
			CurrentAttackState = EAttackState::MoveToAttackLocation;
		}
	}
}

bool FAttackAction::ExecuteAction(float DeltaSeconds)
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

			float Damage = OwnerCombatPawn->Attack - TargetPawn->Defence;

			float Luck = OwnerCombatPawn->Luck - TargetPawn->Luck;
			if (FMath::RandRange(0.f, 1000.f) / 10.f < Luck)
			{
				Damage *= 2.f;
				UE_LOG(LogTemp, Warning, TEXT("-_- good luck, critical attack"));
			}
			
			TargetPawn->AcceptDamage(Damage, OwnerCombatPawn);

			if (MoveAction) { delete MoveAction; }
			MoveAction = nullptr;

			CurrentAttackState = EAttackState::WaitAttackFinished;

			break;
		}
		case EAttackState::WaitAttackFinished:
		{
			TempTime -= DeltaSeconds;
			if (TempTime <= 0.f)
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
