// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInfo.h"

#include "GameFramework/PlayerController.h"

#include "TBSPlayerState.h"


void UPlayerInfo::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* OwnerPC = GetOwningPlayer();
	ATBSPlayerState*  OwnerTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;

	if (OwnerTBSPS)
	{
		OwnerTBSPS->OnGoldUpdateDelegate.AddUObject(this, &UPlayerInfo::UpdateGoldDisplay);

		InitializePlayerInfoDisplay(OwnerTBSPS->GetPlayerName(), OwnerTBSPS->GetGold());
	}
}

void UPlayerInfo::InitializePlayerInfoDisplay_Implementation(const FString& PlayerName, int32 Gold)
{

}