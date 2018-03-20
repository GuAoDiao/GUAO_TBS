// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawnManager.h"

FCombatPawnManager* FCombatPawnManager::CombatPawnManager = nullptr;

FCombatPawnManager::FCombatPawnManager()
{
	BaseCombatPawnAnimationDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_BaseCombatPawnAnimation.DT_BaseCombatPawnAnimation'"));
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

bool FCombatPawnManager::GetBaseAnimationFromName(const FString& InCombatPawnName, FBaseCombatPawnAnimation& OutBaseCombatPawnAnimation)
{
	if (BaseCombatPawnAnimationDT)
	{
		FBaseCombatPawnAnimation*  BaseCombatPawnAnimation  = BaseCombatPawnAnimationDT->FindRow<FBaseCombatPawnAnimation>(FName(*InCombatPawnName), TEXT("-_- find combat pawn base animation"));
		if (BaseCombatPawnAnimation)
		{
			OutBaseCombatPawnAnimation = *BaseCombatPawnAnimation;
		}
	}
	
	return false;
}