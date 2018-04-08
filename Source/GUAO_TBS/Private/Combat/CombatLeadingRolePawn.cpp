// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatLeadingRolePawn.h"

#include "Combat/DecisionMakers/PlayerDecisionMaker.h"
#include "Combat/DecisionMakers/AutoDecisionMaker.h"
#include "Combat/CombatManager.h"

ACombatLeadingRolePawn::ACombatLeadingRolePawn()
{
	PlayerDecisionMaker = nullptr;
}

void ACombatLeadingRolePawn::MakeDecisionImplementation()
{
	if (CombatManager && CombatManager->IsAutoAttack())
	{
		Super::MakeDecisionImplementation();
	}
	else
	{
		PlayerDecisionMaker = new FPlayerDecisionMaker();
		if (PlayerDecisionMaker)
		{
			PlayerDecisionMaker->BeginMakeDecision(this);
			DecisionMaker = PlayerDecisionMaker;
		}
	}
}

void ACombatLeadingRolePawn::ToggleCurentDecisionToAutoAttack()
{
	// create auto decision maker
	FAutoDecisionMaker* AutoDecisionMaker = new FAutoDecisionMaker();
	if (AutoDecisionMaker)
	{
		AutoDecisionMaker->BeginMakeDecision(this);

		// Interrupt and destroy old player decision maker
		if (DecisionMaker)
		{
			if (PlayerDecisionMaker)
			{
				PlayerDecisionMaker->InterruptMakeDecision();
				PlayerDecisionMaker = nullptr;
			}

			delete DecisionMaker;
		}

		DecisionMaker = AutoDecisionMaker;
	}
}
