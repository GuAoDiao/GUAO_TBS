// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLayout.h"

#include "UI/PlayerBackpack.h"


void UGameLayout::NativeConstruct()
{
	InitializeGameLayoutWidget();

	Super::NativeConstruct();
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