// Fill out your copyright notice in the Description page of Project Settings.

#include "TilePawnManager.h"

#include "Engine/DataTable.h"

FTilePawnManager* FTilePawnManager::TilePawnManager = nullptr;



FTilePawnManager::FTilePawnManager()
{
	TilePawnInfoDT = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GUAO_TBS/Datatable/DT_TilePawnInfo.DT_TilePawnInfo'"));
}

FTilePawnManager* FTilePawnManager::GetInstance()
{
	if (!TilePawnManager)
	{
		TilePawnManager = new FTilePawnManager();
	}

	checkf(TilePawnManager, TEXT("-_- the Tile Pawn Manager must be existx."));

	return TilePawnManager;
}





const FTilePawnInfo* FTilePawnManager::GetTilePawnInfo(int32 ID)
{
	if (TilePawnInfoDT)
	{
		return TilePawnInfoDT->FindRow<FTilePawnInfo>(FName(*FString::FromInt(ID)), TEXT("-_- find tile pawn info"));
	}
	return nullptr;
}