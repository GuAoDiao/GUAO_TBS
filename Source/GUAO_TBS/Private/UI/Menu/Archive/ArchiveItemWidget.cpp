// Fill out your copyright notice in the Description page of Project Settings.

#include "ArchiveItemWidget.h"

#include "GameFramework/TBSGameInstance.h"
#include "GameFramework/Archive/TBSArchiveItem.h"

void UArchiveItemWidget::InitializeArchiveItemWidget(class UTBSArchiveItem* InTBSArchiveItem)
{
	if (ensure(InTBSArchiveItem))
	{
		UpdateArchiveItemWidgetDisplay(InTBSArchiveItem->ArchiveName, InTBSArchiveItem->PlayerName, InTBSArchiveItem->Level, InTBSArchiveItem->LevelName);

		ArchiveName = InTBSArchiveItem->ArchiveName;
	}
}

void UArchiveItemWidget::OnLoadArchiveItemButtonClicked()
{
	if (UTBSGameInstance* TBSGameInstance = Cast<UTBSGameInstance>(GetGameInstance()))
	{
		TBSGameInstance->LoadArchive(ArchiveName);
	}
}
