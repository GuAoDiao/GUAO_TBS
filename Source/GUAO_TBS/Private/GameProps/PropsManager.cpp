// Fill out your copyright notice in the Description page of Project Settings.

#include "PropsManager.h"

FPropsManager* FPropsManager::PropsManagerInstance = nullptr;

FPropsManager* FPropsManager::GetPropsManagerInstance()
{
	if (!PropsManagerInstance) { PropsManagerInstance = new FPropsManager(); }
	check(PropsManagerInstance);
	return PropsManagerInstance;
}

FPropsManager::FPropsManager()
{
	GamePropsInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_GamePropsInfo.DT_GamePropsInfo'"));
}

const FGamePropsInfo& FPropsManager::GetPropsInfoFormID(int32 PropsID)
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

	return FGamePropsInfo::EmpeyProps;
}