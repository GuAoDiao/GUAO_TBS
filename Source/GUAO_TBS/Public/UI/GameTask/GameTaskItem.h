// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TBSTypes.h"
#include "GameTaskItem.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameTaskItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeGameTaskItem(class UGameTask* GameTask);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateGameTaskInfo(const FText& Tile, const FText& Description, const FText& Publisher, const FText& Submission, EGameTaskType Type);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateGameTaskFlow(EGameTaskFlow TaskFlow);
};
