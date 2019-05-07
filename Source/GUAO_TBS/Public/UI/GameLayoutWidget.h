// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLayoutWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameLayoutWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void InitializeGameLayoutWidget();

	UFUNCTION(BlueprintCallable)
	void TogglePlayerBackPackDisplay();

	UFUNCTION(BlueprintCallable)
	void ToggleGameTaskListDisplay();
protected:
	UPROPERTY(BlueprintReadWrite)
	class UPlayerBasicInfoWidget* PlayerInfo;
	UPROPERTY(BlueprintReadWrite)
	class UPlayerBackpackWidget* PlayerBackPack;
	UPROPERTY(BlueprintReadWrite)
	class UGameTaskListWidget* GameTaskList;
};
