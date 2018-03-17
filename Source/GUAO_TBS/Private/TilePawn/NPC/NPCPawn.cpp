// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCPawn.h"

ANPCPawn::ANPCPawn()
{
	TileType = ETBSTileType::NPC;
}

void ANPCPawn::TalkWith(ATBSCharacter* InPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("Talk With NPC"));
}

