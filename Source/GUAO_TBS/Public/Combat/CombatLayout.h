// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatLayout.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UCombatLayout : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeBount(int32 NewBount);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeTeam(const FString& TeamName);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangePawn(const FString& PawnName);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateAutoAttackToggleDisplay(bool bIsAutoAttack);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameOver(const FString& WinTeamName, bool bIsPlayerWin);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRunAwayFailured();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRunAwaySuccess();

	UPROPERTY(BlueprintReadOnly)
	class ACombatManager* CombatManager;
};
