// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/Actions/ICombatAction.h"
#include "CoreMinimal.h"

class FMoveAction : public ICombatAction
{
public:
	FMoveAction(const FVector& InTargetLocation);

	virtual void BeginExecuteAction(class ACombatPawn* CombatPawn) override;
	virtual bool ExecuteAction(float DeltaSeconds) override;

protected:
	ACombatPawn* OwnerCombatPawn;
	FVector TargetLocation;
	FVector MoveDirection;
	float MoveSpeed;
};
