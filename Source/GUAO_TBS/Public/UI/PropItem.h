// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TBSPropsTypes.h"

#include "PropItem.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPropsItem : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	void InitializePropsItemDisplay(int32 PropsID, int32 PropsNum);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePropsItemDisplay(const FGamePropsInfo& GamePropsInfo, int32 PropsNum);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEmptyPropsItem();
protected:
	int32 CurrentPropsID;
};
