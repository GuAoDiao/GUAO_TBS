// Fill out your copyright notice in the Description page of Project Settings.

#include "CollictionTask.h"

#include "TBSGameAssetManager.h"
#include "TBSCharacter.h"
#include "GameProps/GamePropsComponent.h"

void UCollictionTask::OnWaitForAcceptImplementation()
{
	const FGameCollectionTaskInfo* GameCollectionTaskInfo = FTBSGameAssetManager::GetInstance()->GetGameCollectionTaskInfo(GameTaskID);
	checkf(GameCollectionTaskInfo, TEXT("-_- game collection task info must be exists."));

	CollictionInfo = GameCollectionTaskInfo->TaskInfo;
}

void UCollictionTask::OnAcceptImplementation()
{
	checkf(CurrentExcuteCharacter, TEXT("-_- character must be exists."));

	UGamePropsComponent* GamePropsComp = CurrentExcuteCharacter->GetGamePropsComponent();

	checkf(GamePropsComp, TEXT("-_- GamePropsComp must be exists."));

	CollictionDelegate = GamePropsComp->OnPropsStoreItemChangeDelegate.AddUObject(this, &UCollictionTask::OnPropsStoreItemChange);

	for (TMap<int32, int32>::TIterator It(CollictionInfo); It; ++It)
	{		
		CurrentCollictionInfo.Add(It.Key(), GamePropsComp->GetPropsNum(It.Key()));
	}
}

void UCollictionTask::OnFinishedTaskImplementation()
{
	checkf(CurrentExcuteCharacter, TEXT("-_- character must be exists."));

	UGamePropsComponent* GamePropsComp = CurrentExcuteCharacter->GetGamePropsComponent();

	checkf(GamePropsComp, TEXT("-_- GamePropsComp must be exists."));

	GamePropsComp->OnPropsStoreItemChangeDelegate.Remove(CollictionDelegate);

	for (TMap<int32, int32>::TIterator It(CollictionInfo); It; ++It)
	{
		GamePropsComp->RemoveProps(It.Key(), It.Value());
	}
}

void UCollictionTask::UpdateGameState()
{
	bool bFinished = true;
	
	for (TMap<int32, int32>::TIterator It(CollictionInfo); It; ++It)
	{
		checkf(CurrentCollictionInfo.Contains(It.Key()), TEXT("-_- the task props id must be exists."));
		if (CurrentCollictionInfo[It.Key()] < CollictionInfo[It.Key()])
		{
			bFinished = false;
			break;
		}
	}

	if (bFinished) { OnWaitForCommitTask(); } else { OnWaitForCompleteTask(); }
}

void UCollictionTask::OnPropsStoreItemChange(int32 PropsIndex, int32 PropsID, int32 PropsNum)
{
	for (TMap<int32, int32>::TIterator It(CollictionInfo); It; ++It)
	{
		if (It.Key() == PropsID)
		{
			checkf(CurrentCollictionInfo.Contains(PropsID), TEXT("-_- the task props id must be exists."));

			CurrentCollictionInfo[PropsID] = PropsNum;
		}
	}

	UpdateGameState();
}
