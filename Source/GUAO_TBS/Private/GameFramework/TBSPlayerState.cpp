// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSPlayerState.h"

#include "Engine/World.h"

#include "Combat/CombatPawn.h"
#include "GameFramework/TBSGameInstance.h"
#include "GameFramework/TBSGameAssetManager.h"
#include "GameFramework/Archive/TBSArchiveItem.h"

ATBSPlayerState::ATBSPlayerState()
{
	PlayerUserName = TEXT("GUAO");
	Gold = 1000;
	Level = 1;
	Experience = 0;
	MaxLevel = 10;
	MaxExperience = 10;

	CombatPawnIDInPlayerTeam.Add(1);
	CombatPawnIDInPlayerTeam.Add(1);
	CombatPawnIDInPlayerTeam.Add(1);
}

void ATBSPlayerState::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (UTBSGameInstance* TBSGameInstance = Cast<UTBSGameInstance>(GetGameInstance()))
	{
		if (UTBSArchiveItem* TBSArchiveItemInfo = TBSGameInstance->GetCurrentArchiveItemInfo())
		{
			PlayerUserName = TBSArchiveItemInfo->PlayerName;
			Gold = TBSArchiveItemInfo->Gold;
			Level = TBSArchiveItemInfo->Level;
			Experience = TBSArchiveItemInfo->Experience;
		}
	}
}

void ATBSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	InitializePlayerCombatTeam();
}

void ATBSPlayerState::InitializePlayerCombatTeam()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FTBSGameAssetManager* TBSGameAssetManager = FTBSGameAssetManager::GetInstance();

		for (int32 CombatPawnID : CombatPawnIDInPlayerTeam)
		{
			TSubclassOf<ACombatPawn> OwnerCombatPawnClass = TBSGameAssetManager->GetCombatPawnClassFromID(CombatPawnID);
			FTransform SpawnTransorm;
			SpawnTransorm.SetLocation(FVector(0.f, 0.f, 10000.f));
			ACombatPawn* CombatPawn = OwnerCombatPawnClass ? World->SpawnActorDeferred<ACombatPawn>(OwnerCombatPawnClass, SpawnTransorm) : nullptr;
			if (CombatPawn)
			{
				CombatPawn->SetCombatPawnID(CombatPawnID);
				CombatPawn->SetActorHiddenInGame(true);
				CombatPawn->FinishSpawning(SpawnTransorm);
				PlayerCombatTeam.AllCombatPawns.Add(CombatPawn);
			}
		}
	}
	PlayerCombatTeam.TeamName = TEXT("PlayerTeam");
}

void ATBSPlayerState::AddExperience(int32 InOffset)
{
	Experience += InOffset;

	while (Experience >= MaxExperience)
	{
		if (Level == MaxLevel) { Experience = MaxExperience; break; }

		++Level;
		Experience -= MaxExperience;
		MaxExperience *= 2;
		OnLevelUpDelegate.Broadcast(Level);
	}

	OnExperienceUpdateDelegate.Broadcast(Experience, MaxExperience);
}
