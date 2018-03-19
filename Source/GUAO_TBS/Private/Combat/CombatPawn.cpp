// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawn.h"

#include "Components/SkeletalMeshComponent.h"

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
	UE_LOG(LogTemp, Log, TEXT("-_- Begin Make Decision"));
}

bool ACombatPawn::MakeDecision(float DeltaSeconds)
{
	UE_LOG(LogTemp, Log, TEXT("-_- Waiting for Make Decision"));
	return true;
}

void ACombatPawn::BeginExecuteAction()
{
	UE_LOG(LogTemp, Log, TEXT("-_- Begin action"));
	CountTime = 1.f;
}

bool ACombatPawn::ExecuteAction(float DeltaSeconds)
{
	CountTime -= DeltaSeconds;
	if (CountTime <= 0.f)
	{
		return true;
	}

	// UE_LOG(LogTemp, Log, TEXT("-_- Waiting for action"));
	return false;
}
