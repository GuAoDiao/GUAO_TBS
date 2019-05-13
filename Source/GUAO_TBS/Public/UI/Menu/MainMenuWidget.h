// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/MenuBaseWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UMainMenuWidget : public UMenuBaseWidget
{
	GENERATED_BODY()
	
		
protected:
	UFUNCTION(BlueprintCallable)
	void OnNewGameButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnLoadArchiveButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnSettingButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();
};
