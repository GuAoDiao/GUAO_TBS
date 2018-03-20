// Fill out your copyright notice in the Description page of Project Settings.

#include "DoNothingAction.h"

#include "CoreMinimal.h"

void FDoNothingAction::BeginExecuteAction(class ACombatPawn* Character)
{
}

bool FDoNothingAction::ExecuteAction(float DeltaSeconds)
{
	return true;
}
