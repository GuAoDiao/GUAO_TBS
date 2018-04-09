// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskComponent.h"

#include "TBSCharacter.h"
#include "TBSGameAssetManager.h"
#include "GameTask/GameTask.h"

UGameTaskComponent::UGameTaskComponent()
{
	OwnerCharacter = Cast<ATBSCharacter>(GetOwner());
	
	
	if (!HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
	{
		checkf(OwnerCharacter, TEXT("The Owner must be TBSCharacter"));
	}
}

void UGameTaskComponent::AccpetGameTask(int32 TaskID)
{
	const FGameTaskInfo* GameTaskInfo = FTBSGameAssetManager::GetInstance()->GetGameTaskInfo(TaskID);
	if (GameTaskInfo && GameTaskInfo->TaskClass)
	{
		UGameTask* GameTask = NewObject<UGameTask>(this, GameTaskInfo->TaskClass);
		if (GameTask)
		{
			GameTask->BeAccpeted(OwnerCharacter);

			AllAcceptTask.Add(TaskID, GameTask);
		}
	}
}

void UGameTaskComponent::InterruptTask(int32 TaskID)
{
	if (AllAcceptTask.Contains(TaskID))
	{
		// AllAcceptTask[TaskID];
	}
	AllAcceptTask.Remove(TaskID);
}
