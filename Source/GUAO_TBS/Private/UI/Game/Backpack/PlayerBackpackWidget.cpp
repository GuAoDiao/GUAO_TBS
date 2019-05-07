// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBackpackWidget.h"

#include "TBSCharacter.h"
#include "GameProps/GamePropsComponent.h"

#include "UI/Game/PropItemWidget.h"

void UPlayerBackpackWidget::InitializePlayerBackPack()
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSCharacter* OwnerTBSC = OwnerPC ? Cast<ATBSCharacter>(OwnerPC->GetPawn()) : nullptr;
	UGamePropsComponent* GamePropsComp = OwnerTBSC ? OwnerTBSC->GetGamePropsComponent() : nullptr;
	if(GamePropsComp)
	{
		UpdatePlayerBackpackDisplay(GamePropsComp->GetPropsStoreInfo());
		GamePropsComp->OnPropsStoreItemChangeDelegate.AddUObject(this, &UPlayerBackpackWidget::OnPropsStoreItemChange);
	}
}

void UPlayerBackpackWidget::UpdatePlayerBackpackDisplay_Implementation(const TArray<FPropsStoreItemInfo>& PropsStoreBag)
{
	TSubclassOf<UPropItemWidget> PropsItemClass = LoadClass<UPropItemWidget>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/Game/UMG_PropItemWidget.UMG_PropItemWidget_C'"));
	APlayerController* OwnerPC = GetOwningPlayer();
	if (PropsItemClass && OwnerPC)
	{
		for (int32 i = 0; i < PropsStoreBag.Num(); ++i)
		{
			UPropItemWidget* PropsItem = CreateWidget<UPropItemWidget>(OwnerPC, PropsItemClass);
			PropsItem->InitializePropsItemDisplay(PropsStoreBag[i].ID, PropsStoreBag[i].Nums);
			
			AllPropsItem.Add(PropsItem);

			AddPropsItem(PropsItem);
		}
	}
}

void UPlayerBackpackWidget::OnPropsStoreItemChange(int32  PropsIndex, int32  PropsID, int32  PropsNum)
{
	if (AllPropsItem.IsValidIndex(PropsIndex) && AllPropsItem[PropsIndex])
	{
		AllPropsItem[PropsIndex]->InitializePropsItemDisplay(PropsID, PropsNum);
	}
}