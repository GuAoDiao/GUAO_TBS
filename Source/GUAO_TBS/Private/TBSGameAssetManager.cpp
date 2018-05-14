// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSGameAssetManager.h"


#include "Dialogue/NPCDialogue.h"




FTBSGameAssetManager* FTBSGameAssetManager::TBSGameAssetManagerInstance = nullptr;

FTBSGameAssetManager* FTBSGameAssetManager::GetInstance()
{
	if (!TBSGameAssetManagerInstance)
	{
		TBSGameAssetManagerInstance = new FTBSGameAssetManager();
	}

	checkf(TBSGameAssetManagerInstance, TEXT("The TBS Game Asset Manager must be exists."));

	return TBSGameAssetManagerInstance;
}


FTBSGameAssetManager::FTBSGameAssetManager()
{
	DialogueInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_DialogueInfo.DT_DialogueInfo'"));
	DialogueChoiceInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_DialogueChoiceInfo.DT_DialogueChoiceInfo'"));
	DialogueTaskInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_DialogueTaskInfo.DT_DialogueTaskInfo'"));

	GameTaskInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GameTaskInfo.DT_GameTaskInfo'"));
	GameKillTaskInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GameKillTaskInfo.DT_GameKillTaskInfo'"));
	GameCollectionTaskInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GameCollectionTaskInfo.DT_GameCollectionTaskInfo'"));
	GameTaskAcceptableConditionsDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GameTaskAcceptableConditions.DT_GameTaskAcceptableConditions'"));

	LoadAllDialogueClassInfo();
}

//////////////////////////////////////////////////////////////////////////
/// _Dialogue

void FTBSGameAssetManager::LoadAllDialogueClassInfo()
{
	UDataTable* DialogueClassInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_DialogueClassInfo.DT_DialogueClassInfo'"));
	if (DialogueClassInfoDT)
	{
		TArray<FDialogueClassInfo*> AllDialogueClassInfoInDT;
		DialogueClassInfoDT->GetAllRows<FDialogueClassInfo>(TEXT("Find all Dialogue Class Info"), AllDialogueClassInfoInDT);
		for (FDialogueClassInfo* DialogueClassInfo : AllDialogueClassInfoInDT)
		{
			if (DialogueClassInfo)
			{
				AllDialogueClassInfo.Add(DialogueClassInfo->Type, *DialogueClassInfo);
			}
		}
	}
}


const FDialogueInfo* FTBSGameAssetManager::GetDialogueInfo(int32 DialogueID) const
{
	if (DialogueInfoDT)
	{
		return DialogueInfoDT->FindRow<FDialogueInfo>(FName(*FString::FromInt(DialogueID)), TEXT("-_- Find Dialogue Info From DT"));
	}
	return nullptr;
}

const FDialogueChoiceInfo* FTBSGameAssetManager::GetDialogueChoiceInfo(int32 DialogueID) const
{
	if (DialogueChoiceInfoDT)
	{
		return DialogueChoiceInfoDT->FindRow<FDialogueChoiceInfo>(FName(*FString::FromInt(DialogueID)), TEXT("-_- Find Dialogue Choice Info From DT"));
	}
	return nullptr;
}
const FDialogueTaskInfo* FTBSGameAssetManager::GetDialogueTaskInfo(int32 DialogueID) const
{
	if (DialogueTaskInfoDT)
	{
		return DialogueTaskInfoDT->FindRow<FDialogueTaskInfo>(FName(*FString::FromInt(DialogueID)), TEXT("-_- Find Dialogue Task Info From DT"));
	}
	return nullptr;
}

TSubclassOf<UNPCDialogue> FTBSGameAssetManager::GetDialogueClass(EDialogueType DialogueType)
{
	if (AllDialogueClassInfo.Contains(DialogueType))
	{
		return AllDialogueClassInfo[DialogueType].DialogueClass;
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
/// Game Task
const FGameTaskInfo* FTBSGameAssetManager::GetGameTaskInfo(int32 GameTaskID) const
{
	if (GameTaskInfoDT)
	{
		return GameTaskInfoDT->FindRow<FGameTaskInfo>(FName(*FString::FromInt(GameTaskID)), TEXT("-_- Find Game Task Info From DT"));
	}
	return nullptr;
}
const FGameKillTaskInfo* FTBSGameAssetManager::GetGameKillTaskInfo(int32 GameTaskID) const
{
	if (GameKillTaskInfoDT)
	{
		return GameKillTaskInfoDT->FindRow<FGameKillTaskInfo>(FName(*FString::FromInt(GameTaskID)), TEXT("-_- Find Game Kill Task Info From DT"));
	}
	return nullptr;
}

const FGameCollectionTaskInfo* FTBSGameAssetManager::GetGameCollectionTaskInfo(int32 GameTaskID) const
{
	if (GameCollectionTaskInfoDT)
	{
		return GameCollectionTaskInfoDT->FindRow<FGameCollectionTaskInfo>(FName(*FString::FromInt(GameTaskID)), TEXT("-_- find game collection task info from DT."));
	}
	return nullptr;
}

const FGameTaskAcceptableConditions* FTBSGameAssetManager::GetGameTaskAcceptableConditions(int32 GameTaskID) const
{
	if (GameTaskAcceptableConditionsDT)
	{
		uint8* Result = GameTaskAcceptableConditionsDT->FindRowUnchecked(FName(*FString::FromInt(GameTaskID)));
		if (Result)
		{
			return reinterpret_cast<FGameTaskAcceptableConditions*>(Result);
		}
	}
	return nullptr;
}
