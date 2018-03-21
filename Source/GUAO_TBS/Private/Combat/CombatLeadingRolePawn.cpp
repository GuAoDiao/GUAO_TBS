// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatLeadingRolePawn.h"

#include "Combat/DecisionMakers/PlayerDecisionMaker.h"

void ACombatLeadingRolePawn::BeginMakeDecision()
{
	DecisionMaker = new FPlayerDecisionMaker();
	if (DecisionMaker) { DecisionMaker->BeginMakeDecision(this); }
}

