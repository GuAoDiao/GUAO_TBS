// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn/NPC/NPCTilePawn.h"

#include "TBSPropsTypes.h"

#include "ShopNPCTilePawn.generated.h"

class UNPCShop;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API AShopNPCTilePawn : public ANPCTilePawn
{
	GENERATED_BODY()
	
public:

	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void TalkWith(ATBSCharacter* InPlayer) override;

	void BuyItem(int32 ID);

	const FPropsShopInfo& GetPropsShopInfo() const { return PropsShopInfo; }
	bool GetPropsShopItemInfo(int32 ID, FPropsShopItemInfo& OutPropsShopItemInfo) const;
	int32 GetPropsShopItemIndex(int32 ID) const;
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNPCShop> NPCShopClass;

	UPROPERTY(Transient)
	UNPCShop* NPCShop;
	UPROPERTY()
	FPropsShopInfo PropsShopInfo;
};
