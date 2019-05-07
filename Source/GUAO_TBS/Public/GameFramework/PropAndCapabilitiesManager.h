// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSPropsAndCapabilitiesTypes.h"

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
	
	//////////////////////////////////////////////////////////////////////////
	/// Props
public:
	const FGamePropsInfo& GetPropsInfoFormID(int32 PropsID);
	const FConsumablesPropsInfo& GetConsumablesPropsInfoFormID(int32 PropsID);
	
protected:
	UPROPERTY()
	class UDataTable* GamePropsInfoDT;
	UPROPERTY()
	class UDataTable* ConsumablesPropsInfoDT;

	TMap<int32, FGamePropsInfo> AllGamePropsInfo;
	TMap<int32, FConsumablesPropsInfo> AllConsumablesPropsInfo;

	//////////////////////////////////////////////////////////////////////////
	/// Props Shop
public:
	const FPropsShopInfo& GetShopInfo(int32 InShopNPCID) const;

protected:
	UPROPERTY()
	class UDataTable* PropsShopInfoDT;

	//////////////////////////////////////////////////////////////////////////
	/// Capabilities
public:
	UCombatCapabilities* GetCombatCapabilities(ECombatCapabilitiesType InConsumablesType);
	UGameCapabilities* GetGameCapabilities(EGameCapabilitiesType InGameCapabilitiesType);

protected:
	UPROPERTY()
	class UDataTable* GameCapabilitiesClassInfoDT;
	UPROPERTY()
	class UDataTable* CombatCapabilitiesClassInfoDT;

	UPROPERTY()
	TMap<ECombatCapabilitiesType, UCombatCapabilities*> AllCombatCapabilities;
	UPROPERTY()
	TMap<EGameCapabilitiesType, UGameCapabilities*> AllGameCapabilities;
};
