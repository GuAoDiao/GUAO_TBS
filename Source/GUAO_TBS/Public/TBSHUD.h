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
	
	//////////////////////////////////////////////////////////////////////////
	/// Combat Layout
public:
	void ShowCombatLayout();

	UCombatLayout* GetCombatLayout() const { return CombatLayout; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCombatLayout> CombatLayoutClass;

	UPROPERTY(Transient)
	UCombatLayout* CombatLayout;
	//////////////////////////////////////////////////////////////////////////
	/// Game Layout
public:
	void ShowGameLayout();
	void TogglePlayerBackPackDisplay();
	void ToggleGameTaskListDisplay();
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameLayout> GameLayoutClass;
	
	UPROPERTY(Transient)
	UGameLayout* GameLayout;
};
