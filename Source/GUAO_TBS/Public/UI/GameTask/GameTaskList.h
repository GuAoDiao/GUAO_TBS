// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTaskList.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameTaskList : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	
	void OnAcceptTaskListUpdate();

	UFUNCTION(BlueprintImplementableEvent)
	void ClearAllGameTaskItem();

	UFUNCTION(BlueprintImplementableEvent)
	void AddGameTaskItem(class UGameTaskItem* GameTaskItem);
protected:
	class UGameTaskComponent* OwnerGameTaskComp;
};
