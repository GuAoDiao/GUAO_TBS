// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSHUD.h"

#include "GameFramework/PlayerController.h"


#include "UI/GameLayout.h"

void ATBSHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OwnerPC = GetOwningPlayerController();
	if (OwnerPC)
	{
		if (!GameLayout && GameLayoutClass)
		{
			GameLayout = CreateWidget<UGameLayout>(GetGameInstance(), GameLayoutClass);
		}
		if (GameLayout)
		{
			GameLayout->AddToViewport();

			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(GameLayout->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

			OwnerPC->SetInputMode(InputMode);
		}
	}
}


void ATBSHUD::TogglePlayerBackPackDisplay() { if (GameLayout) { GameLayout->TogglePlayerBackPackDisplay(); } }