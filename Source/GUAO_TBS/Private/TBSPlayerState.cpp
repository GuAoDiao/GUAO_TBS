// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSPlayerState.h"

#include "Engine/World.h"
#include "Combat/CombatPawn.h"
#include "Combat/CombatPawnManager.h"

#include "GameProps/GamePropsComponent.h"

ATBSPlayerState::ATBSPlayerState()
{
	Gold = 1000;

	CombatPawnNameInPlayerTeam.Add(TEXT("LeadingRole"));
	CombatPawnNameInPlayerTeam.Add(TEXT("LeadingRole"));
	CombatPawnNameInPlayerTeam.Add(TEXT("LeadingRole"));

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
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FCombatPawnManager* CombatPawnManager = FCombatPawnManager::GetCombatPawnManagerInstance();

		for (const FString& CombatPawnName : CombatPawnNameInPlayerTeam)
		{
			TSubclassOf<ACombatPawn> OwnerCombatPawnClass = CombatPawnManager->GetCombatPawnClassFromName(CombatPawnName);
			ACombatPawn* CombatPawn = OwnerCombatPawnClass ? World->SpawnActor<ACombatPawn>(OwnerCombatPawnClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters) : nullptr;
			if (CombatPawn)
			{
				CombatPawn->SetCombatPawnName(CombatPawnName);
				CombatPawn->SetActorHiddenInGame(true);
				PlayerCombatTeam.AllCombatPawns.Add(CombatPawn);
			}
		}
	}
	PlayerCombatTeam.TeamName = TEXT("PlayerTeam");
}