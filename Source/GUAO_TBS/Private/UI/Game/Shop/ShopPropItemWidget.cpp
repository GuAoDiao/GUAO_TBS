// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopPropItemWidget.h"

#include "PropAndCapabilitiesManager.h"
#include "TilePawn/NPC/ShopNPCTilePawn.h"

void UShopPropItemWidget::InitializeShopPropsItem(AShopNPCTilePawn* ShopNPC, int32 InID, int32 InNums, int32 InGold)
{
	OwnerShopNPC = ShopNPC;
	ID = InID;

	InitializeShopPropsItemDisplay(InGold);

	UpdatePropsNum(InNums);
}

const FGamePropsInfo& UShopPropItemWidget::GetGamePropsInfo() const
{
	return FPropAndCapabilitiesManager::GetInstance()->GetPropsInfoFormID(ID);
}

void UShopPropItemWidget::BuyItem()
{
	if (OwnerShopNPC) { OwnerShopNPC->BuyItem(ID); }
}