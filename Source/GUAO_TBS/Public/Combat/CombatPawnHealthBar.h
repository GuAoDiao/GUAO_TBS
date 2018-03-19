// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatPawnHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UCombatPawnHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBarPercent(float CurrentHealth, float MaxHealth);
};
