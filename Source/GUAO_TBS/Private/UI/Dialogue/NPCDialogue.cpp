// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCDialogue.h"

#include "TBSGameAssetManager.h"

void UNPCDialogue::DisplayDialogue(int32 DialogueID)
{
	const FDialogueInfo* DialogueInfo = FTBSGameAssetManager::GetInstance()->GetDialogueInfo(DialogueID);
	
	checkf(DialogueInfo, TEXT("-_- the DialogueInfo must exists.")); 
	
	TSubclassOf<UNPCDialogue> DialogueClass = FTBSGameAssetManager::GetInstance()->GetDialogueClass(DialogueInfo->Type);
	if (DialogueClass && GetClass()->IsChildOf(DialogueClass))
	{
		InitializeDialogue(DialogueInfo);
	}
}


void UNPCDialogue::InitializeDialogue(const FDialogueInfo* DialogueInfo)
{
	checkf(DialogueInfo, TEXT("-_- the DialogueInfo must exists."));

	ResetToEmptyDisplay();

	UpdateDisplayContent(DialogueInfo->Content);

	switch (DialogueInfo->Type)
	{
		case EDialogueType::Common:
			ShowCommonNextButton(DialogueInfo->NextID);
			break;
		case EDialogueType::Final:
			ShowFinishDialogueButton();
			break;
	}
}

void UNPCDialogue::FinishDialogue()
{
	RemoveFromParent();
}

void UNPCDialogue::ShowNextDialogue(int32 NextID)
{
	DisplayDialogue(NextID);
}
