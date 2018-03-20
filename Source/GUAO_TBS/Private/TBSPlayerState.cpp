// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSPlayerState.h"

#include "Engine/World.h"
#include "Combat/CombatPawn.h"

ATBSPlayerState::ATBSPlayerState()
{

}

void ATBSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	
	if(World)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AllCombatPawn.AllCombatPawns.Add(World->SpawnActor<ACombatPawn>(OwnerCombatPawnClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters));
		AllCombatPawn.AllCombatPawns.Add(World->SpawnActor<ACombatPawn>(OwnerCombatPawnClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters));
		AllCombatPawn.AllCombatPawns.Add(World->SpawnActor<ACombatPawn>(OwnerCombatPawnClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters));

		for (ACombatPawn* CombatPawn : AllCombatPawn.AllCombatPawns)
		{
			CombatPawn->SetActorHiddenInGame(true);
		}
	}
}
