// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskComponent.h"

#include "GameFramework/Controller.h"

#include "TBSCharacter.h"
#include "TBSPlayerState.h"
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

	AController* OwnerC = OwnerCharacter->GetController();
	ATBSPlayerState* OwnerTBSPS = OwnerC ? Cast<ATBSPlayerState>(OwnerC->PlayerState) : nullptr;
	checkf(OwnerTBSPS, TEXT("-_- Owner Player State must be exists."));
	OwnerTBSPS->OnLevelUpDelegate.AddUObject(this, &UGameTaskComponent::OnLevelUp);

	UpdateAllCanAcceptTask();
}

void UGameTaskComponent::OnLevelUp(int32 Level)
{
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
			checkf(GameTaskInfo, TEXT("-_- Game Task Info muse be exists."));
						
			if (AllCanAcceptTask.Contains(GameTaskInfo->ID) || AllAcceptTask.Contains(GameTaskInfo->ID) || AllFinishedTask.Contains(GameTaskInfo->ID)) { continue; }
				
			UGameTask* GameTask = GameTaskInfo->TaskClass ? NewObject<UGameTask>(this, GameTaskInfo->TaskClass) : nullptr;
			if (GameTask)
			{
				GameTask->Initilaize(GameTaskInfo->ID, GameTaskInfo);
				if (GameTask->CanAccpet(OwnerCharacter))
				{
					GameTask->WaitForAccept();
					AllCanAcceptTask.Add(GameTaskInfo->ID, GameTask);
					
					OnCanAcceptTaskAddDelegate.Broadcast(GameTaskInfo->ID, GameTask);
				}
				else
				{
					GameTask->ConditionalBeginDestroy();
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

			OnAcceptTaskDelegate.Broadcast(TaskID, AllAcceptTask[TaskID]);
		}
	}
}

void UGameTaskComponent::InterruptTask(int32 TaskID)
{
	if (AllAcceptTask.Contains(TaskID))
	{
		OnInterruptTaskDelegate.Broadcast(TaskID, AllAcceptTask[TaskID]);

		AllAcceptTask[TaskID]->ConditionalBeginDestroy();
		AllAcceptTask.Remove(TaskID);
	}
}

void UGameTaskComponent::CompleteGameTask(int32 TaskID)
{
	if (AllAcceptTask.Contains(TaskID))
	{
		if (AllAcceptTask[TaskID] && AllAcceptTask[TaskID]->IsFinished())
		{
			AllAcceptTask[TaskID]->OnFinishedTask();

			AllFinishedTask.Add(TaskID);
			OnFinishedTaskDelegate.Broadcast(TaskID, AllAcceptTask[TaskID]);
			
			AllAcceptTask[TaskID]->ConditionalBeginDestroy();
			AllAcceptTask.Remove(TaskID);
		}

		UpdateAllCanAcceptTask();
	}
}

bool UGameTaskComponent::TargetTaskIsFinished(int32 TaskID)
{
	return AllFinishedTask.Contains(TaskID);
}
