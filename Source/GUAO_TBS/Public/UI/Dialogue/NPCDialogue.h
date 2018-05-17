// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TBSTypes.h"
#include "NPCDialogue.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UNPCDialogue : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void DisplayDialogue(int32 DialogueID);
	
	virtual void InitializeDialogue(const FDialogueInfo* DialogueInfo);

	//////////////////////////////////////////////////////////////////////////
	/// Dispaly
	UFUNCTION(BlueprintImplementableEvent)
	void ResetToEmptyDisplay();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDisplayContent(const FText& Content);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowChoiceOptionList();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowAcceptTaskList(int32 TaskID);


	UFUNCTION(BlueprintImplementableEvent)
	void ShowCompleteTaskList(int32 TaskID);

	UFUNCTION(BlueprintImplementableEvent)
	void AddChoiceOption(const FText& Option, int32 NextID);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowFinishDialogueButton();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowCommonNextButton(int32 NextID);

	//////////////////////////////////////////////////////////////////////////
	/// Action
	UFUNCTION(BlueprintCallable)
	void FinishDialogue();

	UFUNCTION(BlueprintCallable)
	void ShowNextDialogue(int32 NextID);

	UFUNCTION(BlueprintCallable)
	void AcceptTask(int32 TaskID);

	UFUNCTION(BlueprintCallable)
	void CompleteTask(int32 TaskID);
};
