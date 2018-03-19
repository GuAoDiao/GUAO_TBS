// Fill out your copyright notice in the Description page of Project Settings.

#include "DoNothingAction.h"

#include "CoreMinimal.h"

void FDoNothingAction::BeginExecuteAction(class ACombatPawn* Character)
{
	UE_LOG(LogTemp, Log, TEXT("-_- Begin Excute DoNothingAction"));
}

bool FDoNothingAction::ExecuteAction(float DeltaSeconds)
{
	UE_LOG(LogTemp, Log, TEXT("-_- Finished Excute DoNothingAction"));
	return true;
}
