// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTask.h"

#include "TBSCharacter.h"

void UGameTask::Initilaize(int32 InGameTaskID)
{
	GameTaskID = InGameTaskID;
}

bool UGameTask::CanAccpet(class ATBSCharacter* Character)
{
	return true;
}
void UGameTask::BeAccpeted(class ATBSCharacter* Character)
{
	UE_LOG(LogTemp, Log, TEXT("-_- the task be accepted."));
}