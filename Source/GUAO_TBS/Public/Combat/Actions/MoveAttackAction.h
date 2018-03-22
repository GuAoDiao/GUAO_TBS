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

class FMoveAttackAction : public ICombatAction
{
public:
	virtual void BeginExecuteAction(class ACombatPawn* CombatPawn) override final;
	virtual bool ExecuteAction(float DeltaSeconds) override final;


	virtual FVector GetTargetLocation() = 0;
	virtual void AttackImplementation() = 0;
protected:
	float AttackAnimationTime;
	
	FVector OriginLocation;
	FRotator OriginRotatiton;

	EAttackState::Type CurrentAttackState;
	class ACombatPawn* OwnerCombatPawn;
	class FMoveAction* MoveAction;
	class ACombatManager* CombatManager;
};
