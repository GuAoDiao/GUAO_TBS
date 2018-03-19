// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/Actions/ICombatAction.h"

class FAttackAction : public ICombatAction
{
public:
	FAttackAction(int32 InTargetTeam, int32 InTargetIndex);

	virtual void BeginExecuteAction(class ACombatPawn* Character) override;
	virtual bool ExecuteAction(float DeltaSeconds) override;

protected:
	float TempTime;
	int32 TargetTeam;
	int32 TargetIndex;
	ACombatPawn* OnwenCombatPawn;
	ACombatPawn* TargetPawn;
	FVector OriginLocation;
	FRotator OriginRotatiton;

	bool bIsMoving;
	bool bIsWaitForAttack;
	bool bIsAttacked;

	class FMoveAction* MoveAction;
};
