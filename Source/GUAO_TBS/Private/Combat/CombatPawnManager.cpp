// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawnManager.h"

#include "Combat/CombatPawn.h"


FCombatPawnManager* FCombatPawnManager::CombatPawnManager = nullptr;

FCombatPawnManager::FCombatPawnManager()
{
	AllBaseCombatDisplayInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_AllBaseCombatDisplayInfo.DT_AllBaseCombatDisplayInfo'"));
	AllCombatPawnClassInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_AllCombatPawnClassInfo.DT_AllCombatPawnClassInfo'"));
	AllBaseCombatPawnFightInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_AllBaseCombatPawnFightInfo.DT_AllBaseCombatPawnFightInfo'"));
	// FBaseCombatPawnFightInfo
}

FCombatPawnManager* FCombatPawnManager::GetCombatPawnManagerInstance()
{
	if (!CombatPawnManager)
	{
		CombatPawnManager = new FCombatPawnManager();
	}

	check(CombatPawnManager);

	return CombatPawnManager;
}

bool FCombatPawnManager::GetBaseCombatDisplayInfo(const FString& InCombatPawnName, FBaseCombatPawnDisplayInfo& OutBaseCombatDisplayInfo)
{
	if (AllBaseCombatDisplayInfoDT)
	{
		FBaseCombatPawnDisplayInfo*  BaseCombatDisplayInfo = AllBaseCombatDisplayInfoDT->FindRow<FBaseCombatPawnDisplayInfo>(FName(*InCombatPawnName), TEXT("-_- find combat pawn base display info"));
		if (BaseCombatDisplayInfo)
		{
			OutBaseCombatDisplayInfo = *BaseCombatDisplayInfo;
			return true;
		}
	}
	
	return false;
}


TSubclassOf<ACombatPawn> FCombatPawnManager::GetCombatPawnClassFromName(const FString& InCombatPawnName)
{
	if (AllCombatPawnClassInfoDT)
	{
		FCombatPawnClassInfo*  CombatPawnClassInfo = AllCombatPawnClassInfoDT->FindRow<FCombatPawnClassInfo>(FName(*InCombatPawnName), TEXT("-_- find combat pawn class info"));
		if (CombatPawnClassInfo)
		{
			return CombatPawnClassInfo->CombatPawnClass;
		}
	}

	return nullptr;
}

bool FCombatPawnManager::GetBaseCombatPawnFightInfo(const FString& InCombatPawnName, FBaseCombatPawnFightInfo& OutBaseCombatPawnDisplayInfo)
{
	if (AllBaseCombatPawnFightInfoDT)
	{
		FBaseCombatPawnFightInfo*  BaseCombatFightInfo = AllBaseCombatPawnFightInfoDT->FindRow<FBaseCombatPawnFightInfo>(FName(*InCombatPawnName), TEXT("-_- find combat pawn base base fight info"));
		if (BaseCombatFightInfo)
		{
			OutBaseCombatPawnDisplayInfo = *BaseCombatFightInfo;
			return true;
		}
	}

	return false;
}