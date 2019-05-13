// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"

#include "UI/MenuLayoutWidget.h"
#include "UI/Menu/Archive/ArchiveMenuWidget.h"


void UMainMenuWidget::OnNewGameButtonClicked()
{
	if (MenuLayoutWidget.IsValid())
	{
		MenuLayoutWidget->SetDisplayMainMenu(false);
		MenuLayoutWidget->SetDisplayArchiveMenu(true);
		
		TWeakObjectPtr<UArchiveMenuWidget> ArchiveMenuWidget = MenuLayoutWidget->GetArchiveMenuWidget();
		if (ArchiveMenuWidget.IsValid())
		{
			ArchiveMenuWidget->OnCreateNewArchiveButtonClicked();
		}
	}
}

void UMainMenuWidget::OnLoadArchiveButtonClicked()
{
	if (MenuLayoutWidget.IsValid())
	{
		MenuLayoutWidget->SetDisplayMainMenu(false);
		MenuLayoutWidget->SetDisplayArchiveMenu(true);
	}
}

void UMainMenuWidget::OnSettingButtonClicked()
{
	if (MenuLayoutWidget.IsValid())
	{
		MenuLayoutWidget->SetDisplayMainMenu(false);
		MenuLayoutWidget->SetDisplaySettingMenu(true);
	}
}

void UMainMenuWidget::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
