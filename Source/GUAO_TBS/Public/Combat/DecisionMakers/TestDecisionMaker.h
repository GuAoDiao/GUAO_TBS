// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/DecisionMakers/IDecisionMaker.h"

class FTestDecisionMaker : public IDecisionMaker
{
public:
	virtual void BeginMakeDecision(class ACombatPawn* CombatPawn) override;
	virtual bool MakeDecision(float DeltaSeconds) override;
};
