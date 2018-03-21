// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDecisionMaker.h"

#include "Combat/CombatPawn.h"
#include "Combat/PlayerDecisionMakerUI.h"

FPlayerDecisionMaker::FPlayerDecisionMaker()
{
	DecisionMakeUI = nullptr;
	DecisionMakeUIClass = LoadClass<UPlayerDecisionMakerUI>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/Blueprints/Combat/W_PlayerDecisionMakerUI.W_PlayerDecisionMakerUI_C'"));
}

void FPlayerDecisionMaker::BeginMakeDecision(class ACombatPawn* Character)
{
	if (!DecisionMakeUI && DecisionMakeUIClass && Character && Character->GetWorld())
	{
		DecisionMakeUI = CreateWidget<UPlayerDecisionMakerUI>(Character->GetWorld(), DecisionMakeUIClass);
		DecisionMakeUI->BeginMakeDecision(Character);
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


