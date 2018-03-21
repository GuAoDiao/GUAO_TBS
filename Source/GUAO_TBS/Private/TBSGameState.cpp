// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSGameState.h"

#include "Engine/World.h"

#include "TBSPlayerController.h"
#include "TBSPlayerState.h"
#include "Combat/CombatManager.h"
#include "Combat/CombatPawn.h"
#include "TilePawn/Enemy/EnemyTilePawn.h"

ATBSGameState::ATBSGameState()
{
	CombatLocation = FVector(4000.f, 4000.f, 20.f);
}

void ATBSGameState::BeginCombatFromEnemyTilePawn(AEnemyTilePawn* EnemyTilePawn)
{
	if (EnemyTilePawn)
	{
		CurrentFightWithEnemyTilePawn = EnemyTilePawn;
		CurrentFightWithEnemyTilePawn->BeginCombat();
	}
}

void ATBSGameState::BeginCombat(FCombatTeam& EnemyTeam)
{
	UWorld* World = GetWorld();
	if (World && CombatManagerClass)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		CombatManager = World->SpawnActor<ACombatManager>(CombatManagerClass, CombatLocation, FRotator::ZeroRotator, ActorSpawnParameters);

		ATBSPlayerController* OwnerTBSPC = Cast<ATBSPlayerController>(World->GetFirstPlayerController());
		if (OwnerTBSPC && CombatManager) { OwnerTBSPC->TurnViewportToCombat(CombatManager); }

		AllCombatTeam.Empty();
		APlayerController* OnwerPC = GetWorld()->GetFirstPlayerController();
		ATBSPlayerState* OwnerTBSPS = OnwerPC ? Cast<ATBSPlayerState>(OnwerPC->PlayerState) : nullptr;

		FCombatTeam& PlayerTeam = OwnerTBSPS->GetPlayerCombatPawnTeam();
		for (ACombatPawn* CombatPawn : PlayerTeam.AllCombatPawns)
		{
			CombatPawn->SetActorHiddenInGame(false);
		}

		AllCombatTeam.Add(PlayerTeam);
		AllCombatTeam.Add(EnemyTeam);

		PlayerTeamNum = 0;

		CombatManager->InitiallizeCombat(AllCombatTeam, 0);
	}
}

void ATBSGameState::CloseCombat(int32 WinTeam, bool bIsPlayerWin)
{
	if (CombatManager) { CombatManager->Destroy(); }

	ATBSPlayerController* OwnerTBSPC = GetWorld() ? Cast<ATBSPlayerController>(GetWorld()->GetFirstPlayerController()) : nullptr;
	if (OwnerTBSPC) { OwnerTBSPC->TurnViewportToCharacter(); }

	for (int32 i = 0; i < AllCombatTeam.Num(); ++i)
	{
		if (i == PlayerTeamNum)
		{
			for (ACombatPawn* CombatPawn : AllCombatTeam[i].AllCombatPawns)
			{
				CombatPawn->SetActorHiddenInGame(true);
				CombatPawn->ResetPawnState();
			}
		}
		else
		{
			for (ACombatPawn* CombatPawn : AllCombatTeam[i].AllCombatPawns)
			{
				CombatPawn->Destroy();
			}
		}
	}

	if (CurrentFightWithEnemyTilePawn)
	{
		if (bIsPlayerWin)
		{
			CurrentFightWithEnemyTilePawn->FightSuccess();
		}
		else
		{
			CurrentFightWithEnemyTilePawn->FightFailure();
		}
	}
}