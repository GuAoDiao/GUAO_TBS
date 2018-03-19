// Fill out your copyright notice in the Description page of Project Settings.

#include "TestDecisionMaker.h"

#include "CoreMinimal.h"

#include "Combat/CombatPawn.h"
#include "Combat/Actions/AttackAction.h"


void FTestDecisionMaker::BeginMakeDecision(class ACombatPawn* Character)
{
	UE_LOG(LogTemp, Log, TEXT("-_- Begin Make Decision"));

	Character->SetCombatAction(new FAttackAction());
}
bool FTestDecisionMaker::MakeDecision(float DeltaSeconds)
{
	UE_LOG(LogTemp, Log, TEXT("-_- Finished Make Decision"));
	return true;
}