// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePropsComponent.h"

UGamePropsComponent::UGamePropsComponent()
{
	MaxPropsNum = 20;
	FPropsStoreInfo PropsStoreInfo;

	PropsStoreBag.SetNum(MaxPropsNum);
	for(int32 i = 0 ; i < MaxPropsNum; ++i)
	{
		PropsStoreBag[i] = PropsStoreInfo;
	}

	PropsStoreBag[0].ID = 1;
	PropsStoreBag[0].Nums = 5;

	PropsStoreBag[1].ID = 2;
	PropsStoreBag[1].Nums = 3;
}

int32 UGamePropsComponent::GetPropsNum(int32 PropsID) const
{
	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			return PropsStoreBag[i].Nums;
		}
	}
	return 0;
}

void UGamePropsComponent::AddProps(int32 PropsID, int32 PropsNum)
{
	int32 EmptyID = -1;

	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			PropsStoreBag[i].Nums += PropsNum;
			return;
		}
		
		if (EmptyID == -1 && PropsStoreBag[i].ID == -1)
		{
			EmptyID = i;
		}
	}

	if (EmptyID != -1)
	{
		PropsStoreBag[EmptyID].ID = PropsID;
		PropsStoreBag[EmptyID].Nums = PropsNum;
	}
}

void UGamePropsComponent::UseSingleProps(int32 PropsID)
{
	int32 EmptyID = -1;

	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			--PropsStoreBag[i].Nums;
			return;
		}
	}
}

void UGamePropsComponent::UseMultiProps(int32 PropsID, int32 PropsNum)
{
	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			PropsStoreBag[i].Nums -= PropsNum;
			return;
		}
	}
}

void UGamePropsComponent::RemoveProps(int32 PropsID, int32 PropsNum)
{
	for (int32 i = 0; i < MaxPropsNum; ++i)
	{
		if (PropsStoreBag[i].ID == PropsID)
		{
			PropsStoreBag[i].Nums -= PropsNum;
			return;
		}
	}
}