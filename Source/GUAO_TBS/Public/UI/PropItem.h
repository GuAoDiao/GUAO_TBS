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
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePropsItemDisplay();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowEmptyPropsItem();

	UFUNCTION(BlueprintCallable)
	const FGamePropsInfo& GetGamePropsInfo() const;

	UFUNCTION(BlueprintCallable)
	void UseProps();

	void UpdatePropsNum();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePropsNumDisplay();

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPropsID;
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPropsNum;
};
