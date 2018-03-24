// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBackpack.h"

#include "TBSPlayerState.h"
#include "GameProps/GamePropsComponent.h"

#include "UI/PropItem.h"

void UPlayerBackpack::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState* OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;
	UGamePropsComponent* GamePropsComp = OwnerTBSPS ? OwnerTBSPS->GetGamePropsComponent() : nullptr;
	if(GamePropsComp)
	{
		UpdatePlayerBackpackDisplay(GamePropsComp->GetPropsStoreInfo());
		GamePropsComp->OnPropsStoreInfoUpdate.AddUObject(this, &UPlayerBackpack::OnPropsStoreInfoUpdate);
	}
}

void UPlayerBackpack::OnPropsStoreInfoUpdate(const TArray<FPropsStoreItemInfo>& PropsStoreBag)
{
	UpdatePlayerBackpackDisplay(PropsStoreBag);
}

void UPlayerBackpack::UpdatePlayerBackpackDisplay_Implementation(const TArray<FPropsStoreItemInfo>& PropsStoreBag)
{
	TSubclassOf<UPropsItem> PropsItemClass = LoadClass<UPropsItem>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/W_PropsItem.W_PropsItem_C'"));
	APlayerController* OwnerPC = GetOwningPlayer();
	if (PropsItemClass && OwnerPC)
	{
		for (int32 i = 0; i < PropsStoreBag.Num(); ++i)
		{
			UPropsItem* PropsItem = CreateWidget<UPropsItem>(OwnerPC, PropsItemClass);
			PropsItem->InitializePropsItemDisplay(PropsStoreBag[i].ID, PropsStoreBag[i].Nums);

			AddPropsItem(PropsItem);
		}
	}
}