// Fill out your copyright notice in the Description page of Project Settings.

#include "PropItem.h"

#include "TBSPlayerState.h"
#include "PropAndCapabilitiesManager.h"
#include "GameProps/GamePropsComponent.h"

void UPropsItem::InitializePropsItemDisplay(int32 PropsID, int32 PropsNum)
{
	CurrentPropsID = PropsID;
	CurrentPropsNum = PropsNum;

	if (CurrentPropsID != -1 && PropsNum > 0)
	{
		UpdatePropsItemDisplay();
	}
	else
	{
		ShowEmptyPropsItem();
	}
}

const FGamePropsInfo& UPropsItem::GetGamePropsInfo() const
{
	return FPropAndCapabilitiesManager::GetInstance()->GetPropsInfoFormID(CurrentPropsID);
}



void UPropsItem::UseProps()
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState* OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;
	UGamePropsComponent* GamePropsComponent = OwnerTBSPS ? OwnerTBSPS->GetGamePropsComponent() : nullptr;
	if (GamePropsComponent) { GamePropsComponent->UseSingleProps(CurrentPropsID); }
}