// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSTypes.h"

/**
 * 
 */
class GUAO_TBS_API FTBSGameAssetManager
{	
protected:
	FTBSGameAssetManager();
	static FTBSGameAssetManager* TBSGameAssetManagerInstance;
public:
	static FTBSGameAssetManager* GetInstance();

	//////////////////////////////////////////////////////////////////////////
	/// _Dialogue
public:
	void LoadAllDialogueClassInfo();
	const FDialogueInfo* GetDialogueInfo(int32 DialogueID) const;
	const FDialogueChoiceInfo* GetDialogueChoiceInfo(int32 DialogueID) const;
	const FDialogueTaskInfo* GetDialogueTaskInfo(int32 DialogueID) const;
	TSubclassOf<class UNPCDialogue> GetDialogueClass(EDialogueType DialogueType);
protected:
	UPROPERTY()
	class UDataTable* DialogueInfoDT;
	UPROPERTY()
	class UDataTable* DialogueChoiceInfoDT;
	UPROPERTY()
	class UDataTable* DialogueTaskInfoDT;

	TMap<EDialogueType, FDialogueClassInfo> AllDialogueClassInfo;
	//////////////////////////////////////////////////////////////////////////
	/// Game Task
public:
	class UDataTable* GetGameTaskInfoDT() const { return GameTaskInfoDT; }
	const FGameTaskInfo* GetGameTaskInfo(int32 GameTaskID) const;
	const FGameKillTaskInfo* GetGameKillTaskInfo(int32 GameTaskID) const;

protected:
	UPROPERTY()
	class UDataTable* GameTaskInfoDT;
	UPROPERTY()
	class UDataTable* GameKillTaskInfoDT;
	
};
