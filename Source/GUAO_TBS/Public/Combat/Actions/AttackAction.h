// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/Actions/ICombatAction.h"

namespace EAttackState
{
	enum Type
	{
		Ready,
		MoveToAttackLocation,
		Attack,
		WaitAttackFinished,
		MoveToOrigin,
		Finished
	};
}

class FAttackAction : public ICombatAction
{
public:
	FAttackAction(int32 InTargetTeam, int32 InTargetIndex);

	virtual void BeginExecuteAction(class ACombatPawn* CombatPawn) override;
	virtual bool ExecuteAction(float DeltaSeconds) override;

protected:
	float TempTime;
	int32 TargetTeam;
	int32 TargetIndex;
	ACombatPawn* OwnerCombatPawn;
	ACombatPawn* TargetPawn;
	FVector OriginLocation;
	FRotator OriginRotatiton;

	EAttackState::Type CurrentAttackState;

	class FMoveAction* MoveAction;
};
