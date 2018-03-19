// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAction.h"

#include "CoreMinimal.h"

void FAttackAction::BeginExecuteAction(class ACombatPawn* Character)
{
	TempTime = 1.f;

	UE_LOG(LogTemp, Log, TEXT("-_- Begin Excute Action"));
}

bool FAttackAction::ExecuteAction(float DeltaSeconds)
{
	TempTime -= DeltaSeconds;
	if (TempTime <= 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("-_- Finished Excute Action"));

		return true;
	}
	else
	{
		return false;
	}
}
