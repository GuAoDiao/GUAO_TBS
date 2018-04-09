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

void UGameTaskComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateAllCanAcceptTask();
}

void UGameTaskComponent::UpdateAllCanAcceptTask()
{
	UDataTable* GameTaskInfoDT = FTBSGameAssetManager::GetInstance()->GetGameTaskInfoDT();
	if (GameTaskInfoDT)
	{
		TArray<FGameTaskInfo*> AllGameTaskInfo;
		GameTaskInfoDT->GetAllRows<FGameTaskInfo>(TEXT("-_- find all game task info"), AllGameTaskInfo);
		for (FGameTaskInfo* GameTaskInfo : AllGameTaskInfo)
		{
			if (GameTaskInfo)
			{
				if (AllCanAcceptTask.Contains(GameTaskInfo->ID)) { continue; }

				UGameTask* GameTask = GameTaskInfo->TaskClass ? NewObject<UGameTask>(this, GameTaskInfo->TaskClass) : nullptr;
				if (GameTask)
				{
					GameTask->Initilaize(GameTaskInfo->ID, GameTaskInfo);
					AllCanAcceptTask.Add(GameTaskInfo->ID, GameTask);
				}
			}
		}
	}
}

void UGameTaskComponent::AccpetGameTask(int32 TaskID)
{
	if (AllCanAcceptTask.Contains(TaskID))
	{
		if (AllCanAcceptTask[TaskID] && AllCanAcceptTask[TaskID]->CanAccpet(OwnerCharacter))
		{
			AllCanAcceptTask[TaskID]->BeAccpeted(OwnerCharacter);
			AllAcceptTask.Add(TaskID, AllCanAcceptTask[TaskID]);
			AllCanAcceptTask.Remove(TaskID);
			OnAcceptTaskListUpdateDelegate.Broadcast();
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

void UGameTaskComponent::CompleteGameTask(int32 TaskID)
{
	if (AllAcceptTask.Contains(TaskID))
	{
		if (AllAcceptTask[TaskID] && AllAcceptTask[TaskID]->CanFinished())
		{
			AllAcceptTask[TaskID]->BeFinished();

			AllFinishedTask.Add(TaskID);
			AllAcceptTask.Remove(TaskID);
			OnAcceptTaskListUpdateDelegate.Broadcast();
		}
	}
}
