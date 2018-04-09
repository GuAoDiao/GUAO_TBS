// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSTypes.h"

/**
 * 
 */
class GUAO_TBS_API FTilePawnManager
{
public:
	FTilePawnManager();

	static FTilePawnManager* GetInstance();
private:
	static FTilePawnManager* TilePawnManager;



public:
	const FTilePawnInfo* GetTilePawnInfo(int32 ID);

protected:
	UPROPERTY()
	class UDataTable* TilePawnInfoDT;
};
