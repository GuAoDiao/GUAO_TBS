// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLayout.h"

#include "UI/PlayerBackpack.h"
#include "UI/GameTask/GameTaskList.h"


void UGameLayout::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeGameLayoutWidget();
}


void UGameLayout::InitializeGameLayoutWidget_Implementation()
{

}

void UGameLayout::TogglePlayerBackPackDisplay()
{
	if (PlayerBackPack)
	{
		if (PlayerBackPack->GetVisibility() == ESlateVisibility::Visible)
		{
			PlayerBackPack->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			PlayerBackPack->SetVisibility(ESlateVisibility::Visible);
		}
	}
}


void UGameLayout::ToggleGameTaskListDisplay()
{
	if (GameTaskList)
	{
		if (GameTaskList->GetVisibility() == ESlateVisibility::Visible)
		{
			GameTaskList->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			GameTaskList->SetVisibility(ESlateVisibility::Visible);
		}
	}
}