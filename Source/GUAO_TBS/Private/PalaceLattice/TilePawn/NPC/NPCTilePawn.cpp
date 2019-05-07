// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCTilePawn.h"

#include "TBSCharacter.h"

ANPCTilePawn::ANPCTilePawn()
{
	TileType = ETBSTileType::NPC;
	CommonDialogueID = -1;
	TaskDialogueID = -1;
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
	if (InPlayer)
	{
		if (TaskDialogueID > 0)
		{
			InPlayer->OpenDialogue(TaskDialogueID);
		}
		else if (CommonDialogueID > 0)
		{
			InPlayer->OpenDialogue(CommonDialogueID);
		}
	}
}