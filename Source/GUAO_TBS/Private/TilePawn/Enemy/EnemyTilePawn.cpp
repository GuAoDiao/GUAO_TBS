// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTilePawn.h"

#include "Engine/World.h"

#include "TBSTypes.h"
#include "TBSGameState.h"
#include "Combat/CombatPawn.h"
#include "CombatPawnManager.h"

AEnemyTilePawn::AEnemyTilePawn()
{
	TileType = ETBSTileType::Enemy;

	AllCombatEnemy.Add(TEXT("Rebels"));
	AllCombatEnemy.Add(TEXT("LeadingRole"));
	AllCombatEnemy.Add(TEXT("Rebels"));
}

void AEnemyTilePawn::FightWith(ATBSCharacter* InPlayer)
{
	UWorld* World = GetWorld();
	ATBSGameState* OnwerTBSGS = GetWorld() ? GetWorld()->GetGameState<ATBSGameState>() : nullptr;
	if (OnwerTBSGS)
	{
		OnwerTBSGS->BeginCombatFromEnemyTilePawn(this);
	}
}

void AEnemyTilePawn::BeginCombat()
{
	UWorld* World = GetWorld();
	ATBSGameState* OnwerTBSGS = GetWorld() ? GetWorld()->GetGameState<ATBSGameState>() : nullptr;
	if (World && OnwerTBSGS)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FCombatTeam EnemyTeam;
		for (const FString& CombatEnemyName : AllCombatEnemy)
		{
			TSubclassOf<ACombatPawn> CombatEnemyClass = FCombatPawnManager::GetCombatPawnManagerInstance()->GetCombatPawnClassFromName(CombatEnemyName);
			ACombatPawn* ComatPawn = CombatEnemyClass ? World->SpawnActor<ACombatPawn>(CombatEnemyClass, FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator, ActorSpawnParameters) : nullptr;
			if (ComatPawn)
			{
				ComatPawn->SetCombatPawnName(CombatEnemyName);
				EnemyTeam.AllCombatPawns.Add(ComatPawn);
			}
		}

		OnwerTBSGS->BeginCombat(EnemyTeam);
	}
}

void AEnemyTilePawn::FightSuccess()
{
	UE_LOG(LogTemp, Log, TEXT("-_- you win"));
}

void AEnemyTilePawn::FightFailure()
{
	UE_LOG(LogTemp, Log, TEXT("-_- you lost"));
}