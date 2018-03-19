// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPawn.h"

AEnemyPawn::AEnemyPawn()
{
	TileType = ETBSTileType::Enemy;
}

void AEnemyPawn::FightWith(ATBSCharacter* InPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("Fight With Enemy"));
}


