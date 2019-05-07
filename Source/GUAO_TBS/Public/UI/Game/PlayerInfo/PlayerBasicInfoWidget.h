// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBasicInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPlayerBasicInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializePlayInfo();
	
	UFUNCTION(BlueprintImplementableEvent)
	void InitializePlayerInfoDisplay(const FString& PlayerName, int32 Gold, int32 Level, int32 Experience, int32 MaxExperience);

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateGoldDisplay(int32 Gold);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateExperienceDisplay(int32 Experience, int32 MaxExperience);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateLevelAndMaxExperienceDisplay(int32 Level, int32 Experience, int32 MaxExperience);

	void OnLevelUp(int32 Level);
};
