// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLayoutWidget.h"

#include "UI/Game/Backpack/PlayerBackpackWidget.h"
#include "UI/Game/GameTask/GameTaskListWidget.h"
#include "UI/Game/PlayerInfo/PlayerBasicInfoWidget.h"

void UGameLayoutWidget::InitializeGameLayoutWidget_Implementation()
{
	if (GameTaskList) { GameTaskList->InitializeGameTaskList(); }
	if (PlayerInfo) { PlayerInfo->InitializePlayInfo(); }
	if (PlayerBackPack) { PlayerBackPack->InitializePlayerBackPack(); }
}

void UGameLayoutWidget::TogglePlayerBackPackDisplay()
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


void UGameLayoutWidget::ToggleGameTaskListDisplay()
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