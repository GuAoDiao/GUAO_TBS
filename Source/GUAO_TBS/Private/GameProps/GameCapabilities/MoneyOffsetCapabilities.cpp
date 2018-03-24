// Fill out your copyright notice in the Description page of Project Settings.

#include "MoneyOffsetCapabilities.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "TBSPlayerState.h"


void UMoneyOffsetCapabilities::ParseStringToInfo(const FString& Info)
{
	MoneyOffset = FCString::Atod(*Info);
}

void UMoneyOffsetCapabilities::OnUseGameCapabilities()
{
	APlayerController* OwnerPC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	ATBSPlayerState* OwnertTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;
	if (OwnertTBSPS)
	{
		OwnertTBSPS->AddGold(MoneyOffset);
	}
}