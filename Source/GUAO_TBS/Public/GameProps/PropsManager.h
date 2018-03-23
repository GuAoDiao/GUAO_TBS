// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSPropsTypes.h"

/**
 * 
 */
class GUAO_TBS_API FPropsManager
{	
protected:
	FPropsManager();
	static FPropsManager* PropsManagerInstance;
public:
	static FPropsManager* GetPropsManagerInstance();
	
public:
	const FGamePropsInfo& GetPropsInfoFormID(int32 PropsID);

protected:
	UPROPERTY()
	class UDataTable* GamePropsInfoDT;
	UPROPERTY()
	class UDataTable* ConsumablesPropsInfoDT;

	TMap<int32, FGamePropsInfo> AllGamePropsInfo;
};
