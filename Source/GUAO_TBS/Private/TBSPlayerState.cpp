// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSPlayerState.h"

#include "Engine/World.h"
#include "Combat/CombatPawn.h"
#include "Combat/CombatPawnManager.h"

#include "GameProps/GamePropsComponent.h"

ATBSPlayerState::ATBSPlayerState()
{
	PlayerName = TEXT("GUAO");
	Gold = 1000;

	CombatPawnIDInPlayerTeam.Add(1);
	CombatPawnIDInPlayerTeam.Add(1);
	CombatPawnIDInPlayerTeam.Add(1);

	GamePropsComponent = CreateDefaultSubobject<UGamePropsComponent>(TEXT("GamePropsComponent"));
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
		FCombatPawnManager* CombatPawnManager = FCombatPawnManager::GetInstance();

		for (int32 CombatPawnID : CombatPawnIDInPlayerTeam)
		{
			TSubclassOf<ACombatPawn> OwnerCombatPawnClass = CombatPawnManager->GetCombatPawnClassFromID(CombatPawnID);
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