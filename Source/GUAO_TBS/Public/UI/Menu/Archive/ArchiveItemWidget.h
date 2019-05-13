// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArchiveItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UArchiveItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeArchiveItemWidget(class UTBSArchiveItem* InTBSArchiveItem);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateArchiveItemWidgetDisplay(const FName& InArchiveName, const FString& InPlayerName, int32 InPlayerLevel, const FName& InLevelName);

	UFUNCTION(BlueprintCallable)
	void OnLoadArchiveItemButtonClicked();

protected:
	FName ArchiveName;
};
