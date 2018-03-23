// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatLeadingRolePawn.h"

#include "Combat/DecisionMakers/PlayerDecisionMaker.h"
#include "Combat/CombatManager.h"

void ACombatLeadingRolePawn::BeginMakeDecision()
{
	if (CombatManager && CombatManager->IsAutoAttack())
	{
		Super::BeginMakeDecision();
	}
	else
	{
		DecisionMaker = new FPlayerDecisionMaker();
		if (DecisionMaker) { DecisionMaker->BeginMakeDecision(this); }
	}
}