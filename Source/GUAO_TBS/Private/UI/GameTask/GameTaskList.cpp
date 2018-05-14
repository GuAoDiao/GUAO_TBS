// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskList.h"


#include "TBSCharacter.h"
#include "UI/GameTask/GameTaskItem.h"
#include "GameTask/GameTaskComponent.h"

void UGameTaskList::InitializeGameTaskList()
{
	APlayerController* OnwerPC = GetOwningPlayer();
	ATBSCharacter* OwnetTBSCharacter = OnwerPC ? Cast<ATBSCharacter>(OnwerPC->GetPawn()) : nullptr;
	OwnerGameTaskComp = OwnetTBSCharacter ? OwnetTBSCharacter->GetGameTaskComp() : nullptr;
	if (OwnerGameTaskComp)
	{

		OwnerGameTaskComp->OnCanAcceptTaskAddDelegate.AddUObject(this, &UGameTaskList::OnCanAcceptTaskAdd);
		OwnerGameTaskComp->OnAcceptTaskDelegate.AddUObject(this, &UGameTaskList::OnAcceptTask);
		OwnerGameTaskComp->OnInterruptTaskDelegate.AddUObject(this, &UGameTaskList::OnInterruptTask);
		OwnerGameTaskComp->OnFinishedTaskDelegate.AddUObject(this, &UGameTaskList::OnFinishedTask);
		
		InitializeAllGameTaskDisplay();
	}
}

void UGameTaskList::InitializeAllGameTaskDisplay()
{
	checkf(OwnerGameTaskComp, TEXT("-_- OwnerGameTaskComp must be exists."));
	
	ClearAllGameTaskItem();
	GameTaskItemList.Empty();

	APlayerController* OwnerPC = GetOwningPlayer();
	TSubclassOf<UGameTaskItem> GameTaskItemClass = LoadClass<UGameTaskItem>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/GameTask/W_GameTaskItem.W_GameTaskItem_C'"));
	if (OwnerPC && GameTaskItemClass)
	{
		for (TMap<int32, UGameTask*>::TConstIterator It(OwnerGameTaskComp->GetAllCanAcceptTask()); It; ++It)
		{
			UGameTaskItem* GameTaskItem = CreateWidget<UGameTaskItem>(OwnerPC, GameTaskItemClass);
			if (GameTaskItem)
			{
				GameTaskItem->InitializeGameTaskItem(It.Value());
				AddCanAcceptGameTaskItem(GameTaskItem);
				GameTaskItemList.Add(It.Key(), GameTaskItem);
			}
		}

		for (TMap<int32, UGameTask*>::TConstIterator It(OwnerGameTaskComp->GetAllAccpetTasks()); It; ++It)
		{
			UGameTaskItem* GameTaskItem = CreateWidget<UGameTaskItem>(OwnerPC, GameTaskItemClass);
			if (GameTaskItem)
			{
				GameTaskItem->InitializeGameTaskItem(It.Value());
				AddAcceptGameTaskItem(GameTaskItem);
				GameTaskItemList.Add(It.Key(), GameTaskItem);
			}
		}
	}
}

void UGameTaskList::OnCanAcceptTaskAdd(int32 TaskID, UGameTask* GameTask)
{
	checkf(OwnerGameTaskComp, TEXT("-_- OwnerGameTaskComp must be exists."));

	APlayerController* OwnerPC = GetOwningPlayer();
	TSubclassOf<UGameTaskItem> GameTaskItemClass = LoadClass<UGameTaskItem>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/GameTask/W_GameTaskItem.W_GameTaskItem_C'"));
	if (OwnerPC && GameTaskItemClass && GameTask)
	{
		UGameTaskItem* GameTaskItem = CreateWidget<UGameTaskItem>(OwnerPC, GameTaskItemClass);
		if (GameTaskItem)
		{
			GameTaskItem->InitializeGameTaskItem(GameTask);
			AddCanAcceptGameTaskItem(GameTaskItem);
			GameTaskItemList.Add(TaskID, GameTaskItem);
		}
	}
}

void UGameTaskList::OnAcceptTask(int32 TaskID, UGameTask* GameTask)
{
	if (GameTaskItemList.Contains(TaskID))
	{
		ChangeItemFromCanAcceptToAccept(GameTaskItemList[TaskID]);
	}
}
void UGameTaskList::OnInterruptTask(int32 TaskID, UGameTask* GameTask)
{
	if (GameTaskItemList.Contains(TaskID))
	{
		ChangeItemFromAcceptToCanAccept(GameTaskItemList[TaskID]);
	}
}
void UGameTaskList::OnFinishedTask(int32 TaskID, UGameTask* GameTask)
{
	if (GameTaskItemList.Contains(TaskID))
	{
		ChangeItemFromAcceptToFinished(GameTaskItemList[TaskID]);
	}
}