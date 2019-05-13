// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TBSHUD_Menu.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSHUD_Menu : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	void ShowMenuLayoutWidget();

protected:
	UPROPERTY(Transient)
	class UMenuLayoutWidget* MenuLayoutWidget;
};
