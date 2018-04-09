// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTask.h"

#include "Engine/World.h"
#include "EngineUtils.h"

#include "TBSCharacter.h"
#include "TilePawn/NPC/NPCTilePawn.h"

void UGameTask::Initilaize(int32 InGameTaskID, FGameTaskInfo* InGameTaskInfo)
{
	GameTaskID = InGameTaskID;
	checkf(InGameTaskInfo, TEXT("-_- Game Task Info must exists."));
	GameTaskInfo = *InGameTaskInfo;

	if (GameTaskInfo.AcceptFromNPCID)
	{
		for (TActorIterator<ANPCTilePawn> It(GetWorld()); It; ++It)
		{
			if (It->GetTilePawnID() == GameTaskInfo.AcceptFromNPCID)
			{
				It->SetTaskDialogueID(GameTaskInfo.AcceptFromDialogueID);
			}
		}
	}
}

bool UGameTask::CanAccpet(class ATBSCharacter* Character)
{
	return true;
}
void UGameTask::BeAccpeted(class ATBSCharacter* Character)
{
	if (GameTaskInfo.FinishedNPCID)
	{
		for (TActorIterator<ANPCTilePawn> It(GetWorld()); It; ++It)
		{
			if (It->GetTilePawnID() == GameTaskInfo.FinishedNPCID)
			{
				It->SetTaskDialogueID(GameTaskInfo.FinishedDialogueID);
			}
		}
	}
}


bool UGameTask::CanFinished()
{
	return true;
}

void UGameTask::BeFinished()
{
	if (GameTaskInfo.FinishedNPCID)
	{
		for (TActorIterator<ANPCTilePawn> It(GetWorld()); It; ++It)
		{
			if (It->GetTilePawnID() == GameTaskInfo.FinishedNPCID)
			{
				It->SetTaskDialogueID(0);
			}
		}
	}
}