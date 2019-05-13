// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuLayoutWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "TBSGameAssetManager.h"
#include "UI/Menu/MainMenuWidget.h"
#include "UI/Menu/Archive/ArchiveMenuWidget.h"
#include "UI/Menu/Setting/SettingMenuWidget.h"

bool UMenuLayoutWidget::Initialize()
{
	if (Super::Initialize())
	{
		ReflectionStyleWidget();

		ensure(RootCanvas);

		return true;
	}

	return false;
}

void UMenuLayoutWidget::InitializeMenuLayoutWidget()
{
	SetDisplayMainMenu(true);
}

void UMenuLayoutWidget::SetDisplayWidget(class UWidget* InWidget, bool bDisplay)
{
	if (RootCanvas && InWidget)
	{
		if (bDisplay)
		{
			if (!RootCanvas->HasChild(InWidget))
			{
				if (UCanvasPanelSlot* CanvasPanelSlot = RootCanvas->AddChildToCanvas(InWidget))
				{
					CanvasPanelSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
					CanvasPanelSlot->SetPosition(FVector2D::ZeroVector);
					CanvasPanelSlot->SetOffsets(FMargin(0.f));
					CanvasPanelSlot->SetAutoSize(true);
				}
			}
		}
		else
		{
			RootCanvas->RemoveChild(InWidget);
		}
	}
}

UUserWidget* UMenuLayoutWidget::CreateWidgetFromName(const FName& InWidgetName)
{
	if (TSubclassOf<UUserWidget> WidgetClass = FTBSGameAssetManager::GetInstance()->GetWidgetClass(InWidgetName))
	{
		UMenuBaseWidget* MenuBaseWidget = CreateWidget<UMenuBaseWidget>(GetOwningPlayer(), WidgetClass);
		if (MenuBaseWidget)
		{
			MenuBaseWidget->SetMenuLayoutWidget(this);
		}
		return MenuBaseWidget;
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
/// MainMenu
void UMenuLayoutWidget::SetDisplayMainMenu(bool bDisplay)
{
	if (bDisplay && !MainMenuWidget.IsValid())
	{
		MainMenuWidget = MakeWeakObjectPtr(Cast<UMainMenuWidget>(CreateWidgetFromName("MainMenu")));
	}

	SetDisplayWidget(MainMenuWidget.Get(), bDisplay);
}

//////////////////////////////////////////////////////////////////////////
/// Setting Menu
void UMenuLayoutWidget::SetDisplaySettingMenu(bool bDisplay)
{
	if (bDisplay && !SettingMenuWidget.IsValid())
	{
		SettingMenuWidget = MakeWeakObjectPtr(Cast<USettingMenuWidget>(CreateWidgetFromName("SettingMenu")));
	}

	SetDisplayWidget(SettingMenuWidget.Get(), bDisplay);
}

//////////////////////////////////////////////////////////////////////////
/// Archive Menu
void UMenuLayoutWidget::SetDisplayArchiveMenu(bool bDisplay)
{
	if (bDisplay && !ArchiveMenuWidget.IsValid())
	{
		ArchiveMenuWidget = MakeWeakObjectPtr(Cast<UArchiveMenuWidget>(CreateWidgetFromName("ArchiveMenu")));
		ArchiveMenuWidget->InitializeArchiveMenuWidget();
	}

	SetDisplayWidget(ArchiveMenuWidget.Get(), bDisplay);
}
