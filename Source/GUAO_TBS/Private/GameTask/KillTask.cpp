// Fill out your copyright notice in the Description page of Project Settings.

#include "KillTask.h"

#include "TBSGameAssetManager.h"
#include "TBSGameState.h"
#include "CombatPawn.h"
#include "Engine/World.h"


void UKillTask::OnInitializeImplementation(int32 InGameTaskID, FGameTaskInfo* InGameTaskInfo)
{
	const FGameKillTaskInfo* GameKillTaskInfo = FTBSGameAssetManager::GetInstance()->GetGameKillTaskInfo(InGameTaskID);
	checkf(GameKillTaskInfo, TEXT("-_- game kill task info must be exists."));

	EnemyInfo = GameKillTaskInfo->TaskInfo;
}

void UKillTask::OnAcceptImplementation()
{
	for (TMap<int32, int32>::TIterator It(EnemyInfo); It; ++It)
	{
		CurrentKillInfo.Add(It.Key(), 0);
	}

	ATBSGameState* TBSGameState = GetWorld() ? Cast<ATBSGameState>(GetWorld()->GetGameState()) : nullptr;
	if (TBSGameState)
	{
		KillCombatDelegate = TBSGameState->OnKillCombatPawnDelegate.AddUObject(this, &UKillTask::OnKillCombatPawn);
	}
}

void UKillTask::UpdateGameState()
{
	for (TMap<int32, int32>::TIterator It(EnemyInfo); It; ++It)
	{
		checkf(CurrentKillInfo.Contains(It.Key()), TEXT("-_- the current kill info must has target enemy"));

		if (CurrentKillInfo[It.Key()] < It.Value())
		{
			break;
		}
	}

	ATBSGameState* TBSGameState = GetWorld() ? Cast<ATBSGameState>(GetWorld()->GetGameState()) : nullptr;
	if (TBSGameState)
	{
		TBSGameState->OnKillCombatPawnDelegate.Remove(KillCombatDelegate);
	}

	OnCanFinishedTask();
}

void UKillTask::OnKillCombatPawn(ACombatPawn* CombatPawn)
{
	if (CombatPawn)
	{
		int32 CombatPawnID = CombatPawn->GetCombatPawnID();
		for (TMap<int32, int32>::TIterator It(EnemyInfo); It; ++It)
		{
			if (It.Key() == CombatPawnID)
			{
				checkf(EnemyInfo.Contains(CombatPawnID), TEXT("-_- enemy info must be exists."));

				CurrentKillInfo[CombatPawnID] = It.Value() + 1;
				if (CurrentKillInfo[CombatPawnID] > EnemyInfo[CombatPawnID])
				{
					CurrentKillInfo[CombatPawnID] = EnemyInfo[CombatPawnID];
					
					UpdateGameState();
				}

				break;
			}
		}
	}
}