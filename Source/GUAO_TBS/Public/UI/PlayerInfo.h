// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfo.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPlayerInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void InitializePlayerInfoDisplay(const FString& PlayerName, int32 Gold);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateGoldDisplay(int32 Gold);
};
