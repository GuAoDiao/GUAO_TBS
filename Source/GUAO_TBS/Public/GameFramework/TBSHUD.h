// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TBSHUD.generated.h"

class UGameLayoutWidget;
class UCombatLayoutWidget;

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

	UCombatLayoutWidget* GetCombatLayout() const { return CombatLayout; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCombatLayoutWidget> CombatLayoutClass;

	UPROPERTY(Transient)
	UCombatLayoutWidget* CombatLayout;
	//////////////////////////////////////////////////////////////////////////
	/// Game Layout
public:
	void ShowGameLayout();
	void TogglePlayerBackPackDisplay();
	void ToggleGameTaskListDisplay();
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameLayoutWidget> GameLayoutClass;
	
	UPROPERTY(Transient)
	UGameLayoutWidget* GameLayout;
};
