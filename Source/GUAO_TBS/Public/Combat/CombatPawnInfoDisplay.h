// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatPawnInfoDisplay.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UCombatPawnInfoDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitializeCombatPawnInfoDisplay(int32 Level, const FString& CombatPawnName, float MaxHealth, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateHealthBarPercent(float CurrentHealth, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateManaBarPercent(float CurrentMana, float MaxMana);
};
