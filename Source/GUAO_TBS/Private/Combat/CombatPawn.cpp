// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawn.h"

#include "Components/SkeletalMeshComponent.h"

#include "Combat/DecisionMakers/TestDecisionMaker.h"
#include "Combat/Actions/ICombatAction.h"

ACombatPawn::ACombatPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	bIsDead = false;
}

void ACombatPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Health = MaxHealth;
}

void ACombatPawn::BeginMakeDecision()
{
	DecisionMaker = new FTestDecisionMaker();
	if (DecisionMaker) { DecisionMaker->BeginMakeDecision(this); }
}

bool ACombatPawn::MakeDecision(float DeltaSeconds)
{
	if (DecisionMaker)
	{
		if (DecisionMaker->MakeDecision(DeltaSeconds))
		{
			delete DecisionMaker;
			return true;
		}
		return false;
	}
	return true;
}

void ACombatPawn::BeginExecuteAction()
{
	if (CombatAction) { CombatAction->BeginExecuteAction(this); }
}

bool ACombatPawn::ExecuteAction(float DeltaSeconds)
{
	if (CombatAction)
	{
		if (CombatAction->ExecuteAction(DeltaSeconds))
		{
			delete CombatAction;
			return true;
		}
		return false;
	}
	return false;
}
