// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCShop.h"

#include "GameProps/PropsManager.h"
#include "UI/ShopPropsItem.h"
#include "TilePawn/NPC/ShopNPCTilePawn.h"

void UNPCShop::NativeConstruct()
{
	Super::NativeConstruct();

	ShopPropsItemClass = LoadClass<UShopPropsItem>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/W_ShopPropsItem.W_ShopPropsItem_C'"));
}

void UNPCShop::InitializeNPCShop(class AShopNPCTilePawn* ShopNPC)
{
	OwnerShopNPC = ShopNPC;

	ShopPropsItemClass = LoadClass<UShopPropsItem>(this, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/W_ShopPropsItem.W_ShopPropsItem_C'"));

	const FPropsShopInfo& PropsShopInfo = OwnerShopNPC->GetPropsShopInfo();
	for (const FPropsShopItemInfo& PropsShopItemInfo : PropsShopInfo.AllShopItems)
	{
		AddShopPropsItemFromInfo(PropsShopItemInfo);
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
			AddShopPropsItem(ShopPropsItem);
		}
	}
}