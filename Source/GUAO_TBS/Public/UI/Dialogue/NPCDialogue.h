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

	UFUNCTION(BlueprintImplementableEvent)
	void ResetToEmptyDisplay();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDisplayContent(const FText& Content);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowFinishDialogueButton();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowCommonNextButton(int32 NextID);

	UFUNCTION(BlueprintCallable)
	void FinishDialogue();

	UFUNCTION(BlueprintCallable)
	void ShowNextDialogue(int32 NextID);
};
