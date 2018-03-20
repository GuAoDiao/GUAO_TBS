// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTilePawn.h"

#include "Engine/World.h"

#include "TBSGameState.h"
#include "TBSTypes.h"
#include "Combat/CombatPawn.h"

AEnemyTilePawn::AEnemyTilePawn()
{
	TileType = ETBSTileType::Enemy;
}

void AEnemyTilePawn::FightWith(ATBSCharacter* InPlayer)
{
	UWorld* World = GetWorld();
	ATBSGameState* OnwerTBSGS = GetWorld() ? GetWorld()->GetGameState<ATBSGameState>() : nullptr;
	if (OnwerTBSGS)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FCombatTeam EnemyTeam;
		EnemyTeam.AllCombatPawns.Add(World->SpawnActor<ACombatPawn>(OwnerCombatEnemyClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters));
		EnemyTeam.AllCombatPawns.Add(World->SpawnActor<ACombatPawn>(OwnerCombatEnemyClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters));
		EnemyTeam.AllCombatPawns.Add(World->SpawnActor<ACombatPawn>(OwnerCombatEnemyClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters));

		OnwerTBSGS->BeginCombat(EnemyTeam);
	}
}


