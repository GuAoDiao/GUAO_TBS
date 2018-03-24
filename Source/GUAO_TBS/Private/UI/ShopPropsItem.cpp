// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopPropsItem.h"

#include "GameProps/PropsManager.h"
#include "TilePawn/NPC/ShopNPCTilePawn.h"

void UShopPropsItem::InitializeShopPropsItem(AShopNPCTilePawn* ShopNPC, int32 InID, int32 InNums, int32 InGold)
{
	OwnerShopNPC = ShopNPC;
	ID = InID;

	InitializeShopPropsItemDisplay(InGold);

	UpdatePropsNum(InNums);
}

const FGamePropsInfo& UShopPropsItem::GetGamePropsInfo() const
{
	return FPropsManager::GetPropsManagerInstance()->GetPropsInfoFormID(ID);
}

void UShopPropsItem::BuyItem()
{
	if (OwnerShopNPC) { OwnerShopNPC->BuyItem(ID); }
}