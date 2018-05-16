// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskItem.h"

#include "GameTask/GameTask.h"
#include "TilePawn/TilePawnManager.h"
#include "TBSGameAssetManager.h"

void UGameTaskItem::InitializeGameTaskItem(UGameTask* GameTask)
{
	checkf(GameTask, TEXT("-_- the game task must exists."));

	int32 GameTaskID = GameTask->GetGameTaskID();
	const FGameTaskInfo* GameTaskInfo = FTBSGameAssetManager::GetInstance()->GetGameTaskInfo(GameTaskID);
	checkf(GameTaskInfo, TEXT("-_- the game task info must exists."));

	const FTilePawnInfo* AcceptTilePawnInfo = FTilePawnManager::GetInstance()->GetTilePawnInfo(GameTaskInfo->AcceptFromNPCID);
	const FTilePawnInfo* FinishedTilePawnInfo = FTilePawnManager::GetInstance()->GetTilePawnInfo(GameTaskInfo->AcceptFromNPCID);

	checkf(AcceptTilePawnInfo && FinishedTilePawnInfo, TEXT("-_- the accept tile pawn and finished pawn info must exists."));
	
	UpdateGameTaskInfo(GameTaskInfo->Title, GameTaskInfo->Description, FText::FromName(AcceptTilePawnInfo->Name), FText::FromName(FinishedTilePawnInfo->Name),GameTaskInfo->Type);
	
	UpdateGameTaskFlow(GameTask->GetGameTaskFlow());
	GameTask->OnToggleToNewGameTaskFlowDelegate.AddUObject(this, &UGameTaskItem::UpdateGameTaskFlow);
}
