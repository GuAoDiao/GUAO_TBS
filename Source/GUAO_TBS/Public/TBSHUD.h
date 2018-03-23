// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TBSHUD.generated.h"

class UGameLayout;
class UCombatLayout;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	void ShowGameLayout();
	void ShowCombatLayout();

	UCombatLayout* GetCombatLayout() const { return CombatLayout; }
public:
	void TogglePlayerBackPackDisplay();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameLayout> GameLayoutClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCombatLayout> CombatLayoutClass;

	UPROPERTY(Transient)
	UCombatLayout* CombatLayout;
	UPROPERTY(Transient)
	UGameLayout* GameLayout;
};
