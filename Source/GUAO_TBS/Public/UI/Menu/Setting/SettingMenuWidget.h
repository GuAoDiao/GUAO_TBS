// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/MenuBaseWidget.h"
#include "SettingMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API USettingMenuWidget : public UMenuBaseWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();

};
