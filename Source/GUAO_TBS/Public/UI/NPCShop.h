// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TBSPropsTypes.h"

#include "NPCShop.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UNPCShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void InitializeNPCShop(class AShopNPCTilePawn* ShopNPC);

	UFUNCTION(BlueprintImplementableEvent)
	void AddShopPropsItem(class UShopPropsItem* ShopPropsItem);

	void AddShopPropsItemFromInfo(const FPropsShopItemInfo& InInfo);
protected:
	UPROPERTY(BlueprintReadOnly)
	class AShopNPCTilePawn* OwnerShopNPC;
	
	TSubclassOf<class UShopPropsItem> ShopPropsItemClass;
};
