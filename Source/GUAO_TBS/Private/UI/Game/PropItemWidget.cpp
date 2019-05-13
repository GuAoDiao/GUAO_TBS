// Fill out your copyright notice in the Description page of Project Settings.

#include "PropItemWidget.h"

#include "TBSCharacter.h"
#include "GameProps/GamePropsComponent.h"
#include "GameFramework/TBSGameAssetManager.h"

void UPropItemWidget::InitializePropsItemDisplay(int32 PropsID, int32 PropsNum)
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

const FGamePropsInfo& UPropItemWidget::GetGamePropsInfo() const
{
	return FTBSGameAssetManager::GetInstance()->GetPropsInfoFormID(CurrentPropsID);
}



void UPropItemWidget::UseProps()
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSCharacter* OwnerTBSPS = OwnerPC ? Cast<ATBSCharacter>(OwnerPC->GetPawn()) : nullptr;
	UGamePropsComponent* GamePropsComponent = OwnerTBSPS ? OwnerTBSPS->GetGamePropsComponent() : nullptr;
	if (GamePropsComponent) { GamePropsComponent->UseSingleProps(CurrentPropsID); }
}