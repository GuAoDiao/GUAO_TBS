// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCTilePawn.h"

#include "TBSCharacter.h"

ANPCTilePawn::ANPCTilePawn()
{
	TileType = ETBSTileType::NPC;
	CurrentDialogueID = 0;
}

void ANPCTilePawn::TalkWith(ATBSCharacter* InPlayer)
{
	if (OnTalkWithDelegate.IsBound())
	{
		OnTalkWithDelegate.Execute(InPlayer);
	}
	else
	{
		OnTalkWithImplementation(InPlayer);
	}
}


void ANPCTilePawn::OnTalkWithImplementation(ATBSCharacter* InPlayer)
{
	if (InPlayer && CurrentDialogueID > 0)
	{
		InPlayer->OpenDialogue(CurrentDialogueID);
	}
}