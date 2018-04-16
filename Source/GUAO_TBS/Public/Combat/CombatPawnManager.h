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

	static FCombatPawnManager* GetInstance();
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
	bool GetBaseCombatDisplayInfo(int32 InCombatPawnID, FBaseCombatPawnDisplayInfo& OutBaseCombatDisplayInfo);
	TSubclassOf<ACombatPawn> GetCombatPawnClassFromID(int32 InCombatPawnID);
	bool GetBaseCombatPawnFightInfo(int32 InCombatPawnID, FBaseCombatPawnFightInfo& OutBaseCombatPawnDisplayInfo);
};
