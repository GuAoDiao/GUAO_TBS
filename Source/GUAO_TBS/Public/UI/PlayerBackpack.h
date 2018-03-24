// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TBSPropsTypes.h"

#include "PlayerBackpack.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPlayerBackpack : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	void OnPropsStoreInfoUpdate(const TArray<FPropsStoreItemInfo>& PropsStoreBag);
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayerBackpackDisplay(const TArray<FPropsStoreItemInfo>& PropsStoreBag);

	UFUNCTION(BlueprintImplementableEvent)
	void AddPropsItem(class UPropsItem* PropsItem);
};
