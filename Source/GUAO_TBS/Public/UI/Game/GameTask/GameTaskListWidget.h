// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTaskListWidget.generated.h"

class UGameTask;
class UGameTaskItemWidget;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameTaskListWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	void InitializeGameTaskList();
	
	void InitializeAllGameTaskDisplay();

	UFUNCTION(BlueprintImplementableEvent)
	void ClearAllGameTaskItem();

	UFUNCTION(BlueprintImplementableEvent)
	void AddCanAcceptGameTaskItem(UGameTaskItemWidget* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void AddAcceptGameTaskItem(UGameTaskItemWidget* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemFromAcceptToCanAccept(UGameTaskItemWidget* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemFromCanAcceptToAccept(UGameTaskItemWidget* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemFromAcceptToFinished(UGameTaskItemWidget* GameTaskItem);


	void OnCanAcceptTaskAdd(int32 TaskID, UGameTask* GameTask);
	void OnAcceptTask(int32 TaskID, UGameTask* GameTask);
	void OnInterruptTask(int32 TaskID, UGameTask* GameTask);
	void OnFinishedTask(int32 TaskID, UGameTask* GameTask);
protected:
	class UGameTaskComponent* OwnerGameTaskComp;
	TMap<int32, UGameTaskItemWidget*> GameTaskItemList;
};
