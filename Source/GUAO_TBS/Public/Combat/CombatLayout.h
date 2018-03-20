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
	void OnChangeTeam(int32 NewTeam);
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangePawn(int32 NewPawn);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameOver(int32 WinTeam, bool bIsPlayerWin);

	UPROPERTY(BlueprintReadOnly)
	class ACombatManager* CombatManager;
};
