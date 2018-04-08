// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDecisionMaker.h"

#include "Combat/CombatPawn.h"

FPlayerDecisionMaker::FPlayerDecisionMaker()
{
	DecisionMakeUI = nullptr;
	DecisionMakeUIClass = LoadClass<UPlayerDecisionMakerUI>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/Blueprints/Combat/W_PlayerDecisionMakerUI.W_PlayerDecisionMakerUI_C'"));
}

void FPlayerDecisionMaker::BeginMakeDecision(class ACombatPawn* CombatPawn)
{
	if (!DecisionMakeUI && DecisionMakeUIClass && CombatPawn && CombatPawn->GetWorld())
	{
		DecisionMakeUI = CreateWidget<UPlayerDecisionMakerUI>(CombatPawn->GetWorld(), DecisionMakeUIClass);
		DecisionMakeUI->BeginMakeDecision(CombatPawn);
		DecisionMakeUI->AddToViewport();
	}
}

bool FPlayerDecisionMaker::MakeDecision(float DeltaSeconds)
{
	if (DecisionMakeUI)
	{
		if (DecisionMakeUI->MakeDecision(DeltaSeconds))
		{
			DecisionMakeUI->RemoveFromParent();
			return true;
		}
	}

	return false;
}

void FPlayerDecisionMaker::InterruptMakeDecision()
{
	if (DecisionMakeUI) { DecisionMakeUI->RemoveFromParent(); }
}

