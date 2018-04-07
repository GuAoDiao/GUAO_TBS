// Fill out your copyright notice in the Description page of Project Settings.

#include "PropAndCapabilitiesManager.h"

#include "Package.h"

#include "GameProps/GameCapabilities.h"
#include "Combat/CombatCapabilities.h"

FPropAndCapabilitiesManager* FPropAndCapabilitiesManager::PropAndCapabilitiesManagerInstance = nullptr;

FPropAndCapabilitiesManager* FPropAndCapabilitiesManager::GetInstance()
{
	if (!PropAndCapabilitiesManagerInstance) { PropAndCapabilitiesManagerInstance = new FPropAndCapabilitiesManager(); }
	check(PropAndCapabilitiesManagerInstance);
	return PropAndCapabilitiesManagerInstance;
}

FPropAndCapabilitiesManager::FPropAndCapabilitiesManager()
{
	GamePropsInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GamePropsInfo.DT_GamePropsInfo'"));
	ConsumablesPropsInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_ConsumablesPropsInfo.DT_ConsumablesPropsInfo'"));
	PropsShopInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_PropsShopInfo.DT_PropsShopInfo'"));

	
	GameCapabilitiesClassInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GameCapabilitiesClassInfo.DT_GameCapabilitiesClassInfo'"));
	if (GameCapabilitiesClassInfoDT)
	{
		TArray<FGameCapabilitiesClassInfo*> AllGameCapabilitiesClassInfo;
		GameCapabilitiesClassInfoDT->GetAllRows<FGameCapabilitiesClassInfo>(TEXT("-_- find all game capabilities class info"), AllGameCapabilitiesClassInfo);
		for (FGameCapabilitiesClassInfo* GameCapabilitiesClassInfo : AllGameCapabilitiesClassInfo)
		{
			if (GameCapabilitiesClassInfo && GameCapabilitiesClassInfo->ClassInfo)
			{
				AllGameCapabilities.Add(GameCapabilitiesClassInfo->Type, NewObject<UGameCapabilities>(GetTransientPackage(), GameCapabilitiesClassInfo->ClassInfo));
			}
		}
	}

	CombatCapabilitiesClassInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_CombatCapabilitiesClassInfo.DT_CombatCapabilitiesClassInfo'"));

	if (CombatCapabilitiesClassInfoDT)
	{
		TArray<FCombatCapabilitiesClassInfo*> AllCombatCapabilitiesClassInfo;
		CombatCapabilitiesClassInfoDT->GetAllRows<FCombatCapabilitiesClassInfo>(TEXT("-_- find all game capabilities class info"), AllCombatCapabilitiesClassInfo);
		for (FCombatCapabilitiesClassInfo* CombatCapabilitiesClassInfo : AllCombatCapabilitiesClassInfo)
		{
			if (CombatCapabilitiesClassInfo && CombatCapabilitiesClassInfo->ClassInfo)
			{
				AllCombatCapabilities.Add(CombatCapabilitiesClassInfo->Type, NewObject<UCombatCapabilities>(GetTransientPackage(), CombatCapabilitiesClassInfo->ClassInfo));
			}
		}
	}

}

const FGamePropsInfo& FPropAndCapabilitiesManager::GetPropsInfoFormID(int32 PropsID)
{
	if (AllGamePropsInfo.Contains(PropsID))
	{
		return AllGamePropsInfo[PropsID];
	}

	if (GamePropsInfoDT)
	{
		FGamePropsInfo* GamePropsInfo = GamePropsInfoDT->FindRow<FGamePropsInfo>(FName(*FString::FromInt(PropsID)), TEXT("-_- find props info"));
		if (GamePropsInfo)
		{
			AllGamePropsInfo.Add(PropsID, *GamePropsInfo);
			return AllGamePropsInfo[PropsID];
		}
	}

	return FGamePropsInfo::EmptyProps;
}


const FConsumablesPropsInfo& FPropAndCapabilitiesManager::GetConsumablesPropsInfoFormID(int32 PropsID)
{
	if (AllConsumablesPropsInfo.Contains(PropsID))
	{
		return AllConsumablesPropsInfo[PropsID];
	}

	if (ConsumablesPropsInfoDT)
	{
		FConsumablesPropsInfo* ConsumablesPropsInfo = ConsumablesPropsInfoDT->FindRow<FConsumablesPropsInfo>(FName(*FString::FromInt(PropsID)), TEXT("-_- find consumables props info"));
		if (ConsumablesPropsInfo)
		{
			AllConsumablesPropsInfo.Add(PropsID, *ConsumablesPropsInfo);
			return AllConsumablesPropsInfo[PropsID];
		}
	}

	return FConsumablesPropsInfo::EmptyConsumablesProps;
}

UCombatCapabilities* FPropAndCapabilitiesManager::GetCombatCapabilities(ECombatCapabilitiesType InConsumablesType)
{
	if (AllCombatCapabilities.Contains(InConsumablesType))
	{
		return AllCombatCapabilities[InConsumablesType];
	}
	return nullptr;
}

UGameCapabilities* FPropAndCapabilitiesManager::GetGameCapabilities(EGameCapabilitiesType InGameCapabilitiesType)
{
	if (AllGameCapabilities.Contains(InGameCapabilitiesType))
	{
		return AllGameCapabilities[InGameCapabilitiesType];
	}
	return nullptr;
}


const FPropsShopInfo& FPropAndCapabilitiesManager::GetShopInfo(const FString& InShopNPCName) const
{
	if (PropsShopInfoDT)
	{
		FPropsShopInfo* PropsShopInfo = PropsShopInfoDT->FindRow<FPropsShopInfo>(FName(*InShopNPCName), TEXT("-_- find PropsShop info"));
		if (PropsShopInfo)
		{
			return *PropsShopInfo;
		}
	}

	return FPropsShopInfo::EmptyFPropsShopInfo;
}