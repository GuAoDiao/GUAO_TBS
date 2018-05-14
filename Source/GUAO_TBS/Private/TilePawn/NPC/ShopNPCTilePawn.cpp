// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopNPCTilePawn.h"


#include "PropAndCapabilitiesManager.h"
#include "UI/NPCShop.h"
#include "TBSCharacter.h"
#include "TBSPlayerState.h"
#include "GameProps/GamePropsComponent.h"

void AShopNPCTilePawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


	PropsShopInfo = FPropAndCapabilitiesManager::GetInstance()->GetShopInfo(TilePawnID);
}


void AShopNPCTilePawn::OnTalkWithImplementation(ATBSCharacter* InPlayer)
{
	if (!NPCShop && NPCShopClass)
	{
		NPCShop = CreateWidget<UNPCShop>(GetGameInstance(), NPCShopClass);
		if (NPCShop) { NPCShop->InitializeNPCShop(this); }
	}

	if (NPCShop) { NPCShop->AddToViewport(); }
}

void AShopNPCTilePawn::BuyItem(int32 ID)
{
	APlayerController* OwnerPC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	ATBSPlayerState* OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;
	ATBSCharacter* OwnerTBSC = OwnerPC ? Cast<ATBSCharacter>(OwnerPC->GetPawn()) : nullptr;
	
	int32 PropsShopItemIndex = GetPropsShopItemIndex(ID);

	if(PropsShopItemIndex !=-1 && OwnerTBSPS->GetGold() >= PropsShopInfo.AllShopItems[PropsShopItemIndex].Gold)
	{
		if (PropsShopInfo.AllShopItems[PropsShopItemIndex].Nums > 0)
		{
			OwnerTBSPS->AddGold(-PropsShopInfo.AllShopItems[PropsShopItemIndex].Gold);
			UGamePropsComponent* GamePropsComp = OwnerTBSC->GetGamePropsComponent();
			if (GamePropsComp) { GamePropsComp->AddProps(ID, 1); }

			--PropsShopInfo.AllShopItems[PropsShopItemIndex].Nums;

			OnShopPropsItemNumsChangeDelegate.Broadcast(PropsShopItemIndex, PropsShopInfo.AllShopItems[PropsShopItemIndex].Nums);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("-_- the shop don't have enough gods."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("-_- you don't have enough gold."));
	}
}

bool AShopNPCTilePawn::GetPropsShopItemInfo(int32 ID, FPropsShopItemInfo& OutPropsShopItemInfo) const
{
	for (const FPropsShopItemInfo& PropsShopItemInfo : PropsShopInfo.AllShopItems)
	{
		if (PropsShopItemInfo.ID == ID) { OutPropsShopItemInfo = PropsShopItemInfo; return true; }
	}

	return false;
}

int32 AShopNPCTilePawn::GetPropsShopItemIndex(int32 ID) const
{

	for (int32 i =0;i<PropsShopInfo.AllShopItems.Num();++i)
	{
		if (PropsShopInfo.AllShopItems[i].ID == ID) { return i; }
	}

	return -1;
}