// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSPlayerState.h"

#include "Engine/World.h"
#include "Combat/CombatPawn.h"
#include "Combat/CombatPawnManager.h"

ATBSPlayerState::ATBSPlayerState()
{
	OwnerCombatPawnName = TEXT("LeadingRole");
}

void ATBSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	
	if(World)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		TSubclassOf<ACombatPawn> OwnerCombatPawnClass = FCombatPawnManager::GetCombatPawnManagerInstance()->GetCombatPawnClassFromName(OwnerCombatPawnName);

		if (OwnerCombatPawnClass)
		{
			for (int32 i = 0; i < 3; ++i)
			{
				ACombatPawn* CombatPawn = World->SpawnActor<ACombatPawn>(OwnerCombatPawnClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters);
				if (CombatPawn)
				{
					CombatPawn->SetCombatPawnName(OwnerCombatPawnName);
					AllCombatPawn.AllCombatPawns.Add(CombatPawn);
				}
			}
		}
		
		for (ACombatPawn* CombatPawn : AllCombatPawn.AllCombatPawns)
		{
			CombatPawn->SetActorHiddenInGame(true);
		}
	}
}
