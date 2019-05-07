// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInfo.h"

#include "GameFramework/PlayerController.h"

#include "TBSPlayerState.h"


void UPlayerInfo::InitializePlayInfo()
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState*  OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;

	if (OwnerTBSPS)
	{
		OwnerTBSPS->OnGoldUpdateDelegate.AddUObject(this, &UPlayerInfo::UpdateGoldDisplay);
		OwnerTBSPS->OnExperienceUpdateDelegate.AddUObject(this, &UPlayerInfo::UpdateExperienceDisplay);
		OwnerTBSPS->OnLevelUpDelegate.AddUObject(this, &UPlayerInfo::OnLevelUp);

		InitializePlayerInfoDisplay(OwnerTBSPS->GetPlayerUserName(), OwnerTBSPS->GetGold(), OwnerTBSPS->GetLevel(), OwnerTBSPS->GetExperience(), OwnerTBSPS->GetMaxExperience());
	}
}

void UPlayerInfo::OnLevelUp(int32 Level)
{
	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState*  OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;

	if (OwnerTBSPS)
	{
		UpdateLevelAndMaxExperienceDisplay(Level, OwnerTBSPS->GetExperience(), OwnerTBSPS->GetMaxExperience());
	}
}
