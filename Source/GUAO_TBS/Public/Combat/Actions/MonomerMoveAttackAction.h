// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/Actions/MoveAttackAction.h"


class FMonomerMoveAttackAction : public FMoveAttackAction
{
public:
	FMonomerMoveAttackAction(int32 InTargetTeam, int32 InTargetIndex);
	virtual ~FMonomerMoveAttackAction() {};

	virtual FVector GetTargetLocation() override;
	virtual void AttackImplementation() override;

protected:
	int32 TargetTeam;
	int32 TargetIndex;
	class ACombatPawn* TargetPawn;
};
