// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCTilePawn.h"

ANPCTilePawn::ANPCTilePawn()
{
	TileType = ETBSTileType::NPC;
}

void ANPCTilePawn::TalkWith(ATBSCharacter* InPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("Talk With NPC"));
}

