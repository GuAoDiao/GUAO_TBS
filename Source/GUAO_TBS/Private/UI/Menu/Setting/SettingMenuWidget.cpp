// Fill out your copyright notice in the Description page of Project Settings.

#include "SettingMenuWidget.h"

#include "UI/MenuLayoutWidget.h"

void USettingMenuWidget::OnBackButtonClicked()
{
	if (MenuLayoutWidget.IsValid())
	{
		MenuLayoutWidget->SetDisplaySettingMenu(false);
		MenuLayoutWidget->SetDisplayMainMenu(true);
	}
}
