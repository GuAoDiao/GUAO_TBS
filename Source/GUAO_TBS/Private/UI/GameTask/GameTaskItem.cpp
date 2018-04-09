// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskItem.h"

#include "GameTask/GameTask.h"
#include "TBSGameAssetManager.h"


void UGameTaskItem::InitializeGameTaskItem(UGameTask* GameTask)
{
	checkf(GameTask, TEXT("-_- the game task must exists."));

	int32 GameTaskID = GameTask->GetGameTaskID();
	const FGameTaskInfo* GameTaskInfo = FTBSGameAssetManager::GetInstance()->GetGameTaskInfo(GameTaskID);
	checkf(GameTaskInfo, TEXT("-_- the game task info must exists."));

	UpdateGameTaskInfo(GameTaskInfo->Title, GameTaskInfo->Description, GameTaskInfo->Type);
}
