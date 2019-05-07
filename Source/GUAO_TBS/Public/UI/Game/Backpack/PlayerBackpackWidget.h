// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TBSPropsAndCapabilitiesTypes.h"

#include "PlayerBackpackWidget.generated.h"


class UPropItemWidget;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPlayerBackpackWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializePlayerBackPack();
	
	void OnPropsStoreInfoUpdate(const TArray<FPropsStoreItemInfo>& PropsStoreBag);
	void OnPropsStoreItemChange(int32  PropsIndex, int32  PropsID, int32  PropsNum);


	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayerBackpackDisplay(const TArray<FPropsStoreItemInfo>& PropsStoreBag);

	UFUNCTION(BlueprintImplementableEvent)
	void AddPropsItem(UPropItemWidget* PropsItem);

	TArray<UPropItemWidget*> AllPropsItem;
};
