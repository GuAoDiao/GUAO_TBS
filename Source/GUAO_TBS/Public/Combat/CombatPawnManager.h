// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "TBSTypes.h"

class ACombatPawn;

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
	class UDataTable* AllBaseCombatDisplayInfoDT;
	UPROPERTY()
	class UDataTable* AllCombatPawnClassInfoDT;
	UPROPERTY()
	class UDataTable* AllBaseCombatPawnFightInfoDT;

public:
	bool GetBaseCombatDisplayInfo(const FString& InCombatPawnName, FBaseCombatPawnDisplayInfo& OutBaseCombatDisplayInfo);
	TSubclassOf<ACombatPawn> GetCombatPawnClassFromName(const FString& InCombatPawnName);
	bool GetBaseCombatPawnFightInfo(const FString& InCombatPawnName, FBaseCombatPawnFightInfo& OutBaseCombatPawnDisplayInfo);
};
