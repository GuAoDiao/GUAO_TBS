// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLayout.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameLayout : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void InitializeGameLayoutWidget();

	UFUNCTION(BlueprintCallable)
	void TogglePlayerBackPackDisplay();
protected:
	UPROPERTY(BlueprintReadWrite)
	class UPlayerInfo* PlayerInfo;
	UPROPERTY(BlueprintReadWrite)
	class UPlayerBackpack* PlayerBackPack;
};
