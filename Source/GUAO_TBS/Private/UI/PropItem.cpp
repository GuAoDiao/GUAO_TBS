// Fill out your copyright notice in the Description page of Project Settings.

#include "PropItem.h"

#include "GameProps/PropsManager.h"


void UPropsItem::InitializePropsItemDisplay(int32 PropsID, int32 PropsNum)
{
	CurrentPropsID = PropsID;

	if (PropsID != -1)
	{
		UpdatePropsItemDisplay(FPropsManager::GetPropsManagerInstance()->GetPropsInfoFormID(PropsID), PropsNum);
	}
	else
	{
		ShowEmptyPropsItem();
	}
}