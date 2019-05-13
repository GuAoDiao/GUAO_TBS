// Fill out your copyright notice in the Description page of Project Settings.

#include "ArchiveMenuWidget.h"

#include "Components/VerticalBox.h"

#include "GameFramework/TBSGameInstance.h"
#include "GameFramework/TBSGameAssetManager.h"
#include "GameFramework/Archive/TBSArchiveItem.h"
#include "UI/Menu/Archive/ArchiveItemWidget.h"
#include "UI/MenuLayoutWidget.h"


bool UArchiveMenuWidget::Initialize()
{
	if (Super::Initialize())
	{
		ReflectionStyleWidget();
	}

	return false;
}

void UArchiveMenuWidget::InitializeArchiveMenuWidget()
{
	if (ensure(AllArchiveItemVerticalBox))
	{
		AllArchiveItemVerticalBox->ClearChildren();

		if (UTBSGameInstance* TBSGameInstance = Cast<UTBSGameInstance>(GetGameInstance()))
		{
			AllArchiveNameList = TBSGameInstance->GetAllArchiveNameList();
			for (FName& ArchiveName : AllArchiveNameList)
			{
				AddArchiveItemWidget(TBSGameInstance->GetArchiveItemInfo(ArchiveName));
			}

			UpdateAllCharacterNameCanSelect(FTBSGameAssetManager::GetInstance()->GetAllCharacterName());
		}
	}
}

void UArchiveMenuWidget::AddArchiveItemWidget(class UTBSArchiveItem* InTBSArchiveItem)
{
	if (InTBSArchiveItem && ensure(AllArchiveItemVerticalBox))
	{
		if (AllArchiveItemWidget.Contains(InTBSArchiveItem->ArchiveName))
		{
			RemoveArchiveItemWidget(InTBSArchiveItem->ArchiveName);
		}

		if (TSubclassOf<UUserWidget> ArchiveItemWidgetClass = FTBSGameAssetManager::GetInstance()->GetWidgetClass("ArchiveItem"))
		{
			if (UArchiveItemWidget* ArchiveItemWidget = CreateWidget<UArchiveItemWidget>(GetOwningPlayer(), ArchiveItemWidgetClass))
			{
				ArchiveItemWidget->InitializeArchiveItemWidget(InTBSArchiveItem);
				
				AllArchiveItemVerticalBox->AddChildToVerticalBox(ArchiveItemWidget);
			}
		}
	}
}

void UArchiveMenuWidget::RemoveArchiveItemWidget(const FName& InArchiveName)
{
	if (ensure(AllArchiveItemVerticalBox))
	{
		UArchiveItemWidget** ArchiveItemWidgetValue = AllArchiveItemWidget.Find(InArchiveName);
		if (ArchiveItemWidgetValue)
		{
			if (*ArchiveItemWidgetValue)
			{
				AllArchiveItemVerticalBox->RemoveChild(*ArchiveItemWidgetValue);
			}
			AllArchiveItemWidget.Remove(InArchiveName);
		}
	}
}

void UArchiveMenuWidget::CreateNewArchive(const FName& InArchiveName, const FString& InPlayerName, const FName& InCharacterName)
{
	if (
		!InArchiveName.IsNone() && !InPlayerName.IsEmpty() && !InCharacterName.IsNone()
		&& !AllArchiveNameList.Contains(InArchiveName)
		)
	{
		if (UTBSGameInstance* TBSGameInstance = Cast<UTBSGameInstance>(GetGameInstance()))
		{
			if (UTBSArchiveItem* TBSArchiveItem = TBSGameInstance->CreateNewArchive(InArchiveName, InPlayerName, InCharacterName))
			{
				AddArchiveItemWidget(TBSArchiveItem);

				ShowArchiveListWidget();
			}
		}
	}
}

void UArchiveMenuWidget::OnCreateNewArchiveButtonClicked()
{
	ShowCreateNewArchiveWidget();
}

void UArchiveMenuWidget::OnBackButtonClicked()
{
	if (MenuLayoutWidget.IsValid())
	{
		MenuLayoutWidget->SetDisplayArchiveMenu(false);
		MenuLayoutWidget->SetDisplayMainMenu(true);
	}
}
