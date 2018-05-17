// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TBSPropsAndCapabilitiesTypes.h"

#include "NPCShop.generated.h"

class UShopPropsItem;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UNPCShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeNPCShop(class AShopNPCTilePawn* ShopNPC);

	UFUNCTION(BlueprintImplementableEvent)
	void AddShopPropsItem(UShopPropsItem* ShopPropsItem);

	void AddShopPropsItemFromInfo(const FPropsShopItemInfo& InInfo);

	void OnShopPropsItemNumsChange(int32 PropsIndex, int32 PropsNum);
protected:
	UPROPERTY(BlueprintReadOnly)
	class AShopNPCTilePawn* OwnerShopNPC;
	
	TSubclassOf<class UShopPropsItem> ShopPropsItemClass;

	TArray<UShopPropsItem*> AllShopPropsItem;
};
