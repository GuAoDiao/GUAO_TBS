// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/Actions/MoveAttackAction.h"

#include "CoreMinimal.h"

class FMultiMoveAttackAction : public FMoveAttackAction
{
public:
	FMultiMoveAttackAction(int32 InTargetTeam, TArray<int32> InTargetIndex);
	virtual ~FMultiMoveAttackAction() {};

	virtual FVector GetTargetLocation() override;
	virtual void AttackImplementation() override;

protected:
	int32 TargetTeam;
	TArray<int32> TargetIndex;
};
