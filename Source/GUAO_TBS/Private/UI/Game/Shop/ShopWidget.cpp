// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopWidget.h"

#include "GameFramework/TBSGameAssetManager.h"
#include "UI/Game/Shop/ShopPropItemWidget.h"
#include "TilePawn/NPC/ShopNPCTilePawn.h"

void UShopWidget::InitializeNPCShop(class AShopNPCTilePawn* ShopNPC)
{
	OwnerShopNPC = ShopNPC;

	ShopPropsItemClass = LoadClass<UShopPropItemWidget>(this, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/Game/Shop/UMG_ShopPropItemWidget.UMG_ShopPropItemWidget_C'"));
	if (OwnerShopNPC)
	{
		OwnerShopNPC->OnShopPropsItemNumsChangeDelegate.AddUObject(this, &UShopWidget::OnShopPropsItemNumsChange);

		const FPropsShopInfo& PropsShopInfo = OwnerShopNPC->GetPropsShopInfo();
		for (const FPropsShopItemInfo& PropsShopItemInfo : PropsShopInfo.AllShopItems)
		{
			AddShopPropsItemFromInfo(PropsShopItemInfo);
		}
	}
}

void UShopWidget::AddShopPropsItemFromInfo(const FPropsShopItemInfo& InInfo)
{
	APlayerController* OwnerPC = GetOwningPlayer();
	if (OwnerPC && ShopPropsItemClass)
	{
		UShopPropItemWidget* ShopPropsItem = CreateWidget<UShopPropItemWidget>(OwnerPC, ShopPropsItemClass);
		if (ShopPropsItem)
		{
			ShopPropsItem->InitializeShopPropsItem(OwnerShopNPC, InInfo.ID, InInfo.Nums, InInfo.Gold);
			AllShopPropsItem.Add(ShopPropsItem);
			AddShopPropsItem(ShopPropsItem);
		}
	}
}

void UShopWidget::OnShopPropsItemNumsChange(int32 PropsIndex, int32 PropsNum)
{
	if (AllShopPropsItem.IsValidIndex(PropsIndex) && AllShopPropsItem[PropsIndex])
	{
		AllShopPropsItem[PropsIndex]->UpdatePropsNum(PropsNum);
	}
}