// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "TBSTypes.h"

/**
 * 
 */
class GUAO_TBS_API FCombatPawnManager
{
public:
	FCombatPawnManager();

	static FCombatPawnManager* GetCombatPawnManagerInstance();
private:
	static FCombatPawnManager* CombatPawnManager;

protected:
	UPROPERTY()
	class UDataTable* BaseCombatPawnAnimationDT;


public:
	bool GetBaseAnimationFromName(const FString& InCombatPawnName, FBaseCombatPawnAnimation& OutBaseCombatPawnAnimation);
};
