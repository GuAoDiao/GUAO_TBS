// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBasicInfoWidget.h"

#include "GameFramework/PlayerController.h"

#include "TBSPlayerState.h"


void UPlayerBasicInfoWidget::InitializePlayInfo()
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState*  OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;

	if (OwnerTBSPS)
	{
		OwnerTBSPS->OnGoldUpdateDelegate.AddUObject(this, &UPlayerBasicInfoWidget::UpdateGoldDisplay);
		OwnerTBSPS->OnExperienceUpdateDelegate.AddUObject(this, &UPlayerBasicInfoWidget::UpdateExperienceDisplay);
		OwnerTBSPS->OnLevelUpDelegate.AddUObject(this, &UPlayerBasicInfoWidget::OnLevelUp);

		InitializePlayerInfoDisplay(OwnerTBSPS->GetPlayerUserName(), OwnerTBSPS->GetGold(), OwnerTBSPS->GetLevel(), OwnerTBSPS->GetExperience(), OwnerTBSPS->GetMaxExperience());
	}
}

void UPlayerBasicInfoWidget::OnLevelUp(int32 Level)
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState*  OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;

	if (OwnerTBSPS)
	{
		UpdateLevelAndMaxExperienceDisplay(Level, OwnerTBSPS->GetExperience(), OwnerTBSPS->GetMaxExperience());
	}
}
