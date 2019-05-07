// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskListWidget.h"


#include "TBSCharacter.h"
#include "UI/Game/GameTask/GameTaskItemWidget.h"
#include "GameTask/GameTaskComponent.h"

void UGameTaskListWidget::InitializeGameTaskList()
{
	APlayerController* OnwerPC = GetOwningPlayer();
	ATBSCharacter* OwnetTBSCharacter = OnwerPC ? Cast<ATBSCharacter>(OnwerPC->GetPawn()) : nullptr;
	OwnerGameTaskComp = OwnetTBSCharacter ? OwnetTBSCharacter->GetGameTaskComp() : nullptr;
	if (OwnerGameTaskComp)
	{

		OwnerGameTaskComp->OnCanAcceptTaskAddDelegate.AddUObject(this, &UGameTaskListWidget::OnCanAcceptTaskAdd);
		OwnerGameTaskComp->OnAcceptTaskDelegate.AddUObject(this, &UGameTaskListWidget::OnAcceptTask);
		OwnerGameTaskComp->OnInterruptTaskDelegate.AddUObject(this, &UGameTaskListWidget::OnInterruptTask);
		OwnerGameTaskComp->OnFinishedTaskDelegate.AddUObject(this, &UGameTaskListWidget::OnFinishedTask);
		
		InitializeAllGameTaskDisplay();
	}
}

void UGameTaskListWidget::InitializeAllGameTaskDisplay()
{
	checkf(OwnerGameTaskComp, TEXT("-_- OwnerGameTaskComp must be exists."));
	
	ClearAllGameTaskItem();
	GameTaskItemList.Empty();

	APlayerController* OwnerPC = GetOwningPlayer();
	TSubclassOf<UGameTaskItemWidget> GameTaskItemClass = LoadClass<UGameTaskItemWidget>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/Game/GameTask/UMG_GameTaskItemWidget.UMG_GameTaskItemWidget_C'"));
	if (OwnerPC && GameTaskItemClass)
	{
		for (TMap<int32, UGameTask*>::TConstIterator It(OwnerGameTaskComp->GetAllCanAcceptTask()); It; ++It)
		{
			UGameTaskItemWidget* GameTaskItem = CreateWidget<UGameTaskItemWidget>(OwnerPC, GameTaskItemClass);
			if (GameTaskItem)
			{
				GameTaskItem->InitializeGameTaskItem(It.Value());
				AddCanAcceptGameTaskItem(GameTaskItem);
				GameTaskItemList.Add(It.Key(), GameTaskItem);
			}
		}

		for (TMap<int32, UGameTask*>::TConstIterator It(OwnerGameTaskComp->GetAllAccpetTasks()); It; ++It)
		{
			UGameTaskItemWidget* GameTaskItem = CreateWidget<UGameTaskItemWidget>(OwnerPC, GameTaskItemClass);
			if (GameTaskItem)
			{
				GameTaskItem->InitializeGameTaskItem(It.Value());
				AddAcceptGameTaskItem(GameTaskItem);
				GameTaskItemList.Add(It.Key(), GameTaskItem);
			}
		}
	}
}

void UGameTaskListWidget::OnCanAcceptTaskAdd(int32 TaskID, UGameTask* GameTask)
{
	checkf(OwnerGameTaskComp, TEXT("-_- OwnerGameTaskComp must be exists."));

	APlayerController* OwnerPC = GetOwningPlayer();
	TSubclassOf<UGameTaskItemWidget> GameTaskItemClass = LoadClass<UGameTaskItemWidget>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/Game/GameTask/UMG_GameTaskItemWidget.UMG_GameTaskItemWidget_C'"));
	if (OwnerPC && GameTaskItemClass && GameTask)
	{
		UGameTaskItemWidget* GameTaskItem = CreateWidget<UGameTaskItemWidget>(OwnerPC, GameTaskItemClass);
		if (GameTaskItem)
		{
			GameTaskItem->InitializeGameTaskItem(GameTask);
			AddCanAcceptGameTaskItem(GameTaskItem);
			GameTaskItemList.Add(TaskID, GameTaskItem);
		}
	}
}

void UGameTaskListWidget::OnAcceptTask(int32 TaskID, UGameTask* GameTask)
{
	if (GameTaskItemList.Contains(TaskID))
	{
		ChangeItemFromCanAcceptToAccept(GameTaskItemList[TaskID]);
	}
}
void UGameTaskListWidget::OnInterruptTask(int32 TaskID, UGameTask* GameTask)
{
	if (GameTaskItemList.Contains(TaskID))
	{
		ChangeItemFromAcceptToCanAccept(GameTaskItemList[TaskID]);
	}
}
void UGameTaskListWidget::OnFinishedTask(int32 TaskID, UGameTask* GameTask)
{
	if (GameTaskItemList.Contains(TaskID))
	{
		ChangeItemFromAcceptToFinished(GameTaskItemList[TaskID]);
	}
}