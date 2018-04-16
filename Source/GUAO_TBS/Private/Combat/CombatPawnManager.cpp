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

FCombatPawnManager* FCombatPawnManager::GetInstance()
{
	if (!CombatPawnManager)
	{
		CombatPawnManager = new FCombatPawnManager();
	}

	checkf(CombatPawnManager, TEXT("-_- the Combat Pawn Manager must be exists."));

	return CombatPawnManager;
}

bool FCombatPawnManager::GetBaseCombatDisplayInfo(int32 InCombatPawnID, FBaseCombatPawnDisplayInfo& OutBaseCombatDisplayInfo)
{
	if (AllBaseCombatDisplayInfoDT)
	{
		FBaseCombatPawnDisplayInfo*  BaseCombatDisplayInfo = AllBaseCombatDisplayInfoDT->FindRow<FBaseCombatPawnDisplayInfo>(FName(*FString::FromInt(InCombatPawnID)), TEXT("-_- find combat pawn base display info"));
		if (BaseCombatDisplayInfo)
		{
			OutBaseCombatDisplayInfo = *BaseCombatDisplayInfo;
			return true;
		}
	}
	
	return false;
}


TSubclassOf<ACombatPawn> FCombatPawnManager::GetCombatPawnClassFromID(int32 InCombatPawnID)
{
	if (AllCombatPawnClassInfoDT)
	{
		FCombatPawnClassInfo*  CombatPawnClassInfo = AllCombatPawnClassInfoDT->FindRow<FCombatPawnClassInfo>(FName(*FString::FromInt(InCombatPawnID)), TEXT("-_- find combat pawn class info"));
		if (CombatPawnClassInfo)
		{
			return CombatPawnClassInfo->CombatPawnClass;
		}
	}

	return nullptr;
}

bool FCombatPawnManager::GetBaseCombatPawnFightInfo(int32 InCombatPawnID, FBaseCombatPawnFightInfo& OutBaseCombatPawnDisplayInfo)
{
	if (AllBaseCombatPawnFightInfoDT)
	{
		FBaseCombatPawnFightInfo*  BaseCombatFightInfo = AllBaseCombatPawnFightInfoDT->FindRow<FBaseCombatPawnFightInfo>(FName(*FString::FromInt(InCombatPawnID)), TEXT("-_- find combat pawn base base fight info"));
		if (BaseCombatFightInfo)
		{
			OutBaseCombatPawnDisplayInfo = *BaseCombatFightInfo;
			return true;
		}
	}

	return false;
}