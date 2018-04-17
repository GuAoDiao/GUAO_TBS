// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTaskList.generated.h"

class UGameTask;
class UGameTaskItem;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameTaskList : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ClearAllGameTaskItem();

	UFUNCTION(BlueprintImplementableEvent)
	void AddCanAcceptGameTaskItem(UGameTaskItem* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void AddAcceptGameTaskItem(UGameTaskItem* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemFromAcceptToCanAccept(UGameTaskItem* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemFromCanAcceptToAccept(UGameTaskItem* GameTaskItem);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemFromAcceptToFinished(UGameTaskItem* GameTaskItem);

	void InitializeGameTaskList();
	void OnCanAcceptTaskAdd(int32 TaskID, UGameTask* GameTask);
	void OnAcceptTask(int32 TaskID, UGameTask* GameTask);
	void OnInterruptTask(int32 TaskID, UGameTask* GameTask);
	void OnFinishedTask(int32 TaskID, UGameTask* GameTask);
protected:
	class UGameTaskComponent* OwnerGameTaskComp;
	TMap<int32, UGameTaskItem*> GameTaskItemList;
};
