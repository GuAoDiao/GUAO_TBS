// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn/NPC/NPCTilePawn.h"

#include "TBSPropsAndCapabilitiesTypes.h"

#include "ShopNPCTilePawn.generated.h"

class UShopWidget;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API AShopNPCTilePawn : public ANPCTilePawn
{
	GENERATED_BODY()
	
public:

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void OnTalkWithImplementation(ATBSCharacter* InPlayer) override;

	void BuyItem(int32 ID);

	const FPropsShopInfo& GetPropsShopInfo() const { return PropsShopInfo; }
	bool GetPropsShopItemInfo(int32 ID, FPropsShopItemInfo& OutPropsShopItemInfo) const;
	int32 GetPropsShopItemIndex(int32 ID) const;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnShopPropsItemNumsChangeDelegate, int32 /* PropsIndex */, int32 /* PropsNums */);
	FOnShopPropsItemNumsChangeDelegate OnShopPropsItemNumsChangeDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShopWidget> NPCShopClass;
	UPROPERTY(Transient)
	UShopWidget* NPCShop;
	UPROPERTY()
	FPropsShopInfo PropsShopInfo;
};
