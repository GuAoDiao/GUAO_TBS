// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/Actions/ICombatAction.h"

class FDoNothingAction : public ICombatAction
{
public:
	virtual void BeginExecuteAction(class ACombatPawn* CombatPawn) override {}
	virtual bool ExecuteAction(float DeltaSeconds) override { return true; }
};
