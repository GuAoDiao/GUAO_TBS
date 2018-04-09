// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCDialogue.h"

#include "TBSGameAssetManager.h"
#include "TBSCharacter.h"
#include "GameTask/GameTaskComponent.h"

void UNPCDialogue::DisplayDialogue(int32 DialogueID)
{
	const FDialogueInfo* DialogueInfo = FTBSGameAssetManager::GetInstance()->GetDialogueInfo(DialogueID);
	
	checkf(DialogueInfo, TEXT("-_- the DialogueInfo must exists.")); 
	
	TSubclassOf<UNPCDialogue> DialogueClass = FTBSGameAssetManager::GetInstance()->GetDialogueClass(DialogueInfo->Type);
	if (DialogueClass && GetClass()->IsChildOf(DialogueClass))
	{
		InitializeDialogue(DialogueInfo);
	}
	else
	{
		FinishDialogue();
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
		case EDialogueType::Choice:
		{
			ShowChoiceOptionList();

			const FDialogueChoiceInfo* ChoiceInfo = FTBSGameAssetManager::GetInstance()->GetDialogueChoiceInfo(DialogueInfo->ID);
			checkf(ChoiceInfo, TEXT("-_- the dialogue choice info must exists."));
			for (TMap<int32, FText>::TConstIterator It(ChoiceInfo->SelectOptions); It; ++It)
			{
				AddChoiceOption(It.Value(), It.Key());
			}
			break;
		}
		case EDialogueType::AcceptTask:
		{
			const FDialogueTaskInfo* TaskInfo = FTBSGameAssetManager::GetInstance()->GetDialogueTaskInfo(DialogueInfo->ID);
			checkf(TaskInfo, TEXT("-_- the dialogue task info must exists."));
			ShowAcceptTaskList(TaskInfo->TaskID);
			break;
		}
		case EDialogueType::CompleteTask:
		{
			const FDialogueTaskInfo* TaskInfo = FTBSGameAssetManager::GetInstance()->GetDialogueTaskInfo(DialogueInfo->ID);
			checkf(TaskInfo, TEXT("-_- the dialogue task info must exists."));
			ShowCompleteTaskList(TaskInfo->TaskID);
			break;
		}
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

void UNPCDialogue::AcceptTask(int32 TaskID)
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSCharacter* OwnerTBSCharacter = OwnerPC ? Cast<ATBSCharacter>(OwnerPC->GetPawn()) : nullptr;
	UGameTaskComponent* OwnerGameTaskComp = OwnerTBSCharacter ? OwnerTBSCharacter->GetGameTaskComp() : nullptr;
	if(OwnerGameTaskComp)
	{
		OwnerGameTaskComp->AccpetGameTask(TaskID);
	}
	FinishDialogue();
}

void UNPCDialogue::CompleteTask(int32 TaskID)
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSCharacter* OwnerTBSCharacter = OwnerPC ? Cast<ATBSCharacter>(OwnerPC->GetPawn()) : nullptr;
	UGameTaskComponent* OwnerGameTaskComp = OwnerTBSCharacter ? OwnerTBSCharacter->GetGameTaskComp() : nullptr;
	if (OwnerGameTaskComp)
	{
		OwnerGameTaskComp->CompleteGameTask(TaskID);
	}
	FinishDialogue();
}