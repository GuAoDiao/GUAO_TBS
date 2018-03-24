// Fill out your copyright notice in the Description page of Project Settings.

#include "MoneyRandomOffsetCapabilities.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

#include "TBSPlayerState.h"


void UMoneyRandomOffsetCapabilities::ParseStringToInfo(const FString& Info)
{
	int32 Position = Info.Find(TEXT("/"));

	if (Position == -1)
	{
		MoneyMinOffset = MoneyMaxOffset = 0.f;
		UE_LOG(LogTemp, Warning, TEXT("-_- Unable to parse Information"));
		return;
	}

	FString MinMoneyString = Info.Mid(0, Position);
	FString MaxMoneyString = Info.Mid(Position + 1);

	MoneyMinOffset = FCString::Atod(*MinMoneyString);
	MoneyMaxOffset = FCString::Atod(*MaxMoneyString);
}

void UMoneyRandomOffsetCapabilities::OnUseGameCapabilities()
{
	APlayerController* OwnerPC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	ATBSPlayerState* OwnertTBSPS = OwnerPC ? Cast<ATBSPlayerState>(OwnerPC->PlayerState) : nullptr;
	if (OwnertTBSPS)
	{
		OwnertTBSPS->AddGold(FMath::RandRange(MoneyMinOffset, MoneyMaxOffset));
	}
}

