// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UMenuBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuLayoutWidget(class UMenuLayoutWidget* InMenuLayoutWidget);

protected:
	TWeakObjectPtr<class UMenuLayoutWidget> MenuLayoutWidget;
};
