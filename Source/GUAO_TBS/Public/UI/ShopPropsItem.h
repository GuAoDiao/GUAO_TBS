// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TBSPropsTypes.h"

#include "ShopPropsItem.generated.h"


class AShopNPCTilePawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UShopPropsItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeShopPropsItem(AShopNPCTilePawn* ShopNPC, int32 InID, int32 InNums, int32 InGold);
	
	UFUNCTION(BlueprintImplementableEvent)
	void InitializeShopPropsItemDisplay(int32 Gold);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePropsNum(int32 Nums);

	UFUNCTION(BlueprintCallable)
	void BuyItem();

	UFUNCTION(BlueprintCallable)
	const FGamePropsInfo& GetGamePropsInfo() const;
protected:
	UPROPERTY(BlueprintReadOnly)
	AShopNPCTilePawn* OwnerShopNPC;
	UPROPERTY(BlueprintReadOnly)
	int32 ID;
};
