// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSHUD.h"

#include "GameFramework/PlayerController.h"

#include "UI/GameLayoutWidget.h"
#include "UI/CombatLayoutWidget.h"

void ATBSHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowGameLayout();
}

void ATBSHUD::ShowGameLayout()
{
	APlayerController* OwnerPC = GetOwningPlayerController();
	if (OwnerPC)
	{
		if (!GameLayout && GameLayoutClass)
		{
			GameLayout = CreateWidget<UGameLayoutWidget>(GetGameInstance(), GameLayoutClass);
			GameLayout->InitializeGameLayoutWidget();
		}

		if (GameLayout)
		{			
			if(!GameLayout->IsInViewport()){ GameLayout->AddToViewport(); }
			if (CombatLayout && CombatLayout->IsInViewport()) { CombatLayout->RemoveFromViewport(); }
			

			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(GameLayout->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

			OwnerPC->SetInputMode(InputMode);
		}
	}
}

void ATBSHUD::ShowCombatLayout()
{
	APlayerController* OwnerPC = GetOwningPlayerController();
	if (OwnerPC)
	{
		if (!CombatLayout && CombatLayoutClass)
		{
			CombatLayout = CreateWidget<UCombatLayoutWidget>(GetGameInstance(), CombatLayoutClass);
		}
		if (CombatLayout)
		{
			CombatLayout->InitializeGameLayoutWidget();
			
			if (GameLayout && GameLayout->IsInViewport()) { GameLayout->RemoveFromViewport(); }
			if (!CombatLayout->IsInViewport()) { CombatLayout->AddToViewport(); }

			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(CombatLayout->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

			OwnerPC->SetInputMode(InputMode);
		}
	}
}

void ATBSHUD::TogglePlayerBackPackDisplay() { if (GameLayout && GameLayout->IsInViewport()) { GameLayout->TogglePlayerBackPackDisplay(); } }
void ATBSHUD::ToggleGameTaskListDisplay() { if (GameLayout && GameLayout->IsInViewport()) { GameLayout->ToggleGameTaskListDisplay(); } }