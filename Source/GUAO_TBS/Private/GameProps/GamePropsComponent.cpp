// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePropsComponent.h"

#include "PropAndCapabilitiesManager.h"
#include "GameProps/GameCapabilities.h"

UGamePropsComponent::UGamePropsComponent()
{
	MaxPropsNum = 20;
	FPropsStoreItemInfo PropsStoreInfo;

	PropsStoreBag.SetNum(MaxPropsNum);
	for(int32 i = 0 ; i < MaxPropsNum; ++i)
	{
		PropsStoreBag[i] = PropsStoreInfo;
	}

	PropsStoreBag[0].ID = 1;
	PropsStoreBag[0].Nums = 5;

	PropsStoreBag[1].ID = 2;
	PropsStoreBag[1].Nums = 3;

	PropsStoreBag[2].ID = 3;
	PropsStoreBag[2].Nums = 3;

	PropsStoreBag[3].ID = 4;
	PropsStoreBag[3].Nums = 3;

	PropsStoreBag[4].ID = 5;
	PropsStoreBag[4].Nums = 3;

	PropsStoreBag[5].ID = 6;
	PropsStoreBag[5].Nums = 3;
}

int32 UGamePropsComponent::GetPropsNum(int32 PropsID) const
{
	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			return PropsStoreBag[i].Nums;
		}
	}
	return 0;
}

void UGamePropsComponent::AddProps(int32 PropsID, int32 PropsNum)
{
	int32 EmptyID = -1;

	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			PropsStoreBag[i].Nums += PropsNum;

			OnPropsStoreItemChangeDelegate.Broadcast(i, PropsID, PropsStoreBag[i].Nums);
			return;
		}
		
		if (EmptyID == -1 && PropsStoreBag[i].ID == -1)
		{
			EmptyID = i;
		}
	}

	if (EmptyID != -1)
	{
		PropsStoreBag[EmptyID].ID = PropsID;
		PropsStoreBag[EmptyID].Nums = PropsNum;

		OnPropsStoreItemChangeDelegate.Broadcast(EmptyID, PropsID, PropsStoreBag[EmptyID].Nums);
	}
}

void UGamePropsComponent::UseSingleProps(int32 PropsID)
{
	int32 EmptyID = -1;

	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			if (PropsStoreBag[i].Nums <= 0)
			{
				UE_LOG(LogTemp, Log, TEXT("-_- don't have prop"));
				return;
			}
			FPropAndCapabilitiesManager* PropsManager = FPropAndCapabilitiesManager::GetInstance();
			const FGamePropsInfo& PropsInfo = PropsManager->GetPropsInfoFormID(PropsStoreBag[i].ID);

			if (PropsInfo.Type == EGamePropsType::Consumables)
			{
				const FConsumablesPropsInfo& ConsumablesPropsInfo = PropsManager->GetConsumablesPropsInfoFormID(PropsStoreBag[i].ID);
				if (ConsumablesPropsInfo.Type == EConsumablesType::Game || ConsumablesPropsInfo.Type == EConsumablesType::All)
				{
					for (TMap<EGameCapabilitiesType, FString>::TConstIterator It(ConsumablesPropsInfo.GameCapabilities); It; ++It)
					{
						UGameCapabilities* GameCapabilities = PropsManager->GetGameCapabilities(It.Key());
						if (GameCapabilities)
						{
							GameCapabilities->InitializeGameCapabilities(GetWorld(), It.Value());
							GameCapabilities->UseGameCapabilities();
						}
							
					}
					UE_LOG(LogTemp, Log, TEXT("-_- use prop"));
					--PropsStoreBag[i].Nums;

					OnPropsStoreItemChangeDelegate.Broadcast(i, PropsID, PropsStoreBag[i].Nums);
				}
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("-_- don't use combat prop"));
			}
		}
	}
}

void UGamePropsComponent::UseMultiProps(int32 PropsID, int32 PropsNum)
{
	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			PropsStoreBag[i].Nums -= PropsNum;

			OnPropsStoreItemChangeDelegate.Broadcast(i, PropsID, PropsStoreBag[i].Nums);

			return;
		}
	}
}

void UGamePropsComponent::RemoveProps(int32 PropsID, int32 PropsNum)
{
	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			if (PropsStoreBag[i].Nums < PropsNum)
			{
				UE_LOG(LogTemp, Log, TEXT("-_- don't have enough prop to remove."));
				return;
			}

			PropsStoreBag[i].Nums -= PropsNum;

			checkf(PropsStoreBag[i].Nums >= 0, TEXT("-_- the props nums must more then zero."));

			OnPropsStoreItemChangeDelegate.Broadcast(i, PropsID, PropsStoreBag[i].Nums);

			return;
		}
	}
}