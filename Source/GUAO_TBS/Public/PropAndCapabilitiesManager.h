// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSPropsTypes.h"

class UCombatCapabilities;
class UGameCapabilities;

/**
 * 
 */
class GUAO_TBS_API FPropAndCapabilitiesManager
{	
protected:
	FPropAndCapabilitiesManager();
	static FPropAndCapabilitiesManager* PropAndCapabilitiesManagerInstance;
public:
	static FPropAndCapabilitiesManager* GetInstance();
	
public:
	const FGamePropsInfo& GetPropsInfoFormID(int32 PropsID);
	const FConsumablesPropsInfo& GetConsumablesPropsInfoFormID(int32 PropsID);
	const FPropsShopInfo& GetShopInfo(const FString& InShopNPCName) const;

	UCombatCapabilities* GetCombatCapabilities(ECombatCapabilitiesType InConsumablesType);
	UGameCapabilities* GetGameCapabilities(EGameCapabilitiesType InGameCapabilitiesType);


protected:
	UPROPERTY()
	class UDataTable* GamePropsInfoDT;
	UPROPERTY()
	class UDataTable* ConsumablesPropsInfoDT;
	UPROPERTY()
	class UDataTable* GameCapabilitiesClassInfoDT;
	UPROPERTY()
	class UDataTable* CombatCapabilitiesClassInfoDT;
	UPROPERTY()
	class UDataTable* PropsShopInfoDT;

	TMap<int32, FGamePropsInfo> AllGamePropsInfo;
	TMap<int32, FConsumablesPropsInfo> AllConsumablesPropsInfo;

	TMap<ECombatCapabilitiesType, UCombatCapabilities*> AllCombatCapabilities;
	TMap<EGameCapabilitiesType, UGameCapabilities*> AllGameCapabilities;
};
