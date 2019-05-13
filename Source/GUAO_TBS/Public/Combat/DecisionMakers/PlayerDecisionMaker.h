// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Combat/DecisionMakers/IDecisionMaker.h"

#include "CoreMinimal.h"
#include "UI/Combat/PlayerDecisionMakerWidget.h"


class UPlayerDecisionMakerWidget;

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
	TSubclassOf<UPlayerDecisionMakerWidget> DecisionMakeUIClass;
	UPlayerDecisionMakerWidget* DecisionMakeUI;
};
