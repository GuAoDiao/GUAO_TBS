// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/DecisionMakers/IDecisionMaker.h"

#include "CoreMinimal.h"
#include "Combat/PlayerDecisionMakerUI.h"


class UPlayerDecisionMakerUI;

/**
 * 
 */
class FPlayerDecisionMaker : public IDecisionMaker
{
public:
	FPlayerDecisionMaker();

	void InterruptMakeDecision();

	virtual void BeginMakeDecision(class ACombatPawn* CombatPawn) override;
	virtual bool MakeDecision(float DeltaSeconds) override;
	
protected:
	TSubclassOf<UPlayerDecisionMakerUI> DecisionMakeUIClass;
	UPlayerDecisionMakerUI* DecisionMakeUI;
};
