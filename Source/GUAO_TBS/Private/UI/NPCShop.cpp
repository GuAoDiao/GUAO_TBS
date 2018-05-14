// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCShop.h"

#include "PropAndCapabilitiesManager.h"
#include "UI/ShopPropsItem.h"
#include "TilePawn/NPC/ShopNPCTilePawn.h"

void UNPCShop::InitializeNPCShop(class AShopNPCTilePawn* ShopNPC)
{
	OwnerShopNPC = ShopNPC;

	ShopPropsItemClass = LoadClass<UShopPropsItem>(this, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/W_ShopPropsItem.W_ShopPropsItem_C'"));
	if (OwnerShopNPC)
	{
		OwnerShopNPC->OnShopPropsItemNumsChangeDelegate.AddUObject(this, &UNPCShop::OnShopPropsItemNumsChange);

		const FPropsShopInfo& PropsShopInfo = OwnerShopNPC->GetPropsShopInfo();
		for (const FPropsShopItemInfo& PropsShopItemInfo : PropsShopInfo.AllShopItems)
		{
			AddShopPropsItemFromInfo(PropsShopItemInfo);
		}
	}
}

void UNPCShop::AddShopPropsItemFromInfo(const FPropsShopItemInfo& InInfo)
{
	APlayerController* OwnerPC = GetOwningPlayer();
	if (OwnerPC && ShopPropsItemClass)
	{
		UShopPropsItem* ShopPropsItem = CreateWidget<UShopPropsItem>(OwnerPC, ShopPropsItemClass);
		if (ShopPropsItem)
		{
			ShopPropsItem->InitializeShopPropsItem(OwnerShopNPC, InInfo.ID, InInfo.Nums, InInfo.Gold);
			AllShopPropsItem.Add(ShopPropsItem);
			AddShopPropsItem(ShopPropsItem);
		}
	}
}

void UNPCShop::OnShopPropsItemNumsChange(int32 PropsIndex, int32 PropsNum)
{
	if (AllShopPropsItem.IsValidIndex(PropsIndex) && AllShopPropsItem[PropsIndex])
	{
		AllShopPropsItem[PropsIndex]->UpdatePropsNum(PropsNum);
	}
}