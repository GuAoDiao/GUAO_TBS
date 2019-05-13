// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSHUD_Menu.h"

#include "GameFramework/PlayerController.h"

#include "GameFramework/TBSGameAssetManager.h"
#include "UI/MenuLayoutWidget.h"

void ATBSHUD_Menu::BeginPlay()
{
	Super::BeginPlay();

	ShowMenuLayoutWidget();
}

void ATBSHUD_Menu::ShowMenuLayoutWidget()
{
	if (APlayerController* OwnerPC = GetOwningPlayerController())
	{
		if (!MenuLayoutWidget)
		{
			if (TSubclassOf<UUserWidget> MenuLayoutClass = FTBSGameAssetManager::GetInstance()->GetWidgetClass("MenuLayout"))
			{
				MenuLayoutWidget = CreateWidget<UMenuLayoutWidget>(OwnerPC, MenuLayoutClass);
				MenuLayoutWidget->InitializeMenuLayoutWidget();
			}
		}

		if (MenuLayoutWidget)
		{
			if (!MenuLayoutWidget->IsInViewport()) { MenuLayoutWidget->AddToViewport(); }

			OwnerPC->SetInputMode(FInputModeUIOnly());
			OwnerPC->bShowMouseCursor = true;
		}
	}
}