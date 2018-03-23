// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TBSHUD.generated.h"

class UGameLayout;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	


public:
	void TogglePlayerBackPackDisplay();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameLayout> GameLayoutClass;
	UPROPERTY(Transient)
	UGameLayout* GameLayout;
};
