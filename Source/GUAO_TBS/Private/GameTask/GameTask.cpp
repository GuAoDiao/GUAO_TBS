// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTask.h"

#include "Engine/World.h"
#include "EngineUtils.h"

#include "TBSGameAssetManager.h"
#include "TBSCharacter.h"
#include "TilePawn/NPC/NPCTilePawn.h"
#include "TBSPlayerState.h"
#include "GameTask/GameTaskComponent.h"

void UGameTask::Initilaize(int32 InGameTaskID, FGameTaskInfo* InGameTaskInfo)
{
	GameTaskID = InGameTaskID;
	checkf(InGameTaskInfo, TEXT("-_- Game Task Info must exists."));
	GameTaskInfo = *InGameTaskInfo;
	
	OnInitializeImplementation(InGameTaskID, InGameTaskInfo);

	GameTaskFlow = EGameTaskFlow::Initialize;
}

void UGameTask::WaitForAccept()
{
	GameTaskFlow = EGameTaskFlow::WaitForAccept;

	if (GameTaskInfo.AcceptFromNPCID != -1)
	{
		for (TActorIterator<ANPCTilePawn> It(GetWorld()); It; ++It)
		{
			if (It->GetTilePawnID() == GameTaskInfo.AcceptFromNPCID)
			{
				It->SetTaskDialogueID(GameTaskInfo.AcceptFromDialogueID);
			}
		}
	}

	OnWaitForAcceptImplementation();
}

bool UGameTask::CanAccpet(class ATBSCharacter* Character)
{
	const FGameTaskAcceptableConditions* GameTaskAcceptableConditions = FTBSGameAssetManager::GetInstance()->GetGameTaskAcceptableConditions(GameTaskID);
	if (GameTaskAcceptableConditions)
	{
		AController* OwnerC = Character ? Character->GetController() : nullptr;
		ATBSPlayerState* OwnerTBSPS = OwnerC ? Cast<ATBSPlayerState>(OwnerC->PlayerState) : nullptr;
		checkf(OwnerTBSPS, TEXT("-_- Player State Must be exists."));

		// Level limit
		if (GameTaskAcceptableConditions->Level > OwnerTBSPS->GetLevel()) { return false; }

		// Predecessor task not finished
		if (GameTaskAcceptableConditions->PredecessorTask != -1)
		{
			if (!Character->GetGameTaskComp()->TargetTaskIsFinished(GameTaskAcceptableConditions->PredecessorTask)) { return false; }
		}
	}

	return true;
}

void UGameTask::BeAccpeted(class ATBSCharacter* Character)
{
	CurrentExcuteCharacter = Character;

	OnAcceptImplementation();

	UpdateGameState();
}

void UGameTask::OnWaitForCompleteTask()
{
	if (GameTaskFlow == EGameTaskFlow::WaitForComplete) { return; }

	GameTaskFlow = EGameTaskFlow::WaitForComplete;

	if (GameTaskInfo.FinishedNPCID > 0 && GameTaskInfo.WaitingDialogueID > 0)
	{
		for (TActorIterator<ANPCTilePawn> It(GetWorld()); It; ++It)
		{
			if (It->GetTilePawnID() == GameTaskInfo.FinishedNPCID)
			{
				It->SetTaskDialogueID(GameTaskInfo.WaitingDialogueID);
			}
		}
	}
}
void UGameTask::OnWaitForCommitTask()
{
	GameTaskFlow = EGameTaskFlow::WaitForCommit;

	if (GameTaskInfo.FinishedNPCID > 0 && GameTaskInfo.FinishedDialogueID > 0)
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

void UGameTask::OnFinishedTask()
{
	if (GameTaskInfo.FinishedNPCID > 0)
	{
		for (TActorIterator<ANPCTilePawn> It(GetWorld()); It; ++It)
		{
			if (It->GetTilePawnID() == GameTaskInfo.FinishedNPCID)
			{
				It->SetTaskDialogueID(-1);
			}
		}
	}

	OnFinishedTaskImplementation();
}