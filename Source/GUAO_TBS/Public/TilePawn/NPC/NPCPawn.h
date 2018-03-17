// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn/TilePawn.h"
#include "NPCPawn.generated.h"

class ATBSCharacter;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ANPCPawn : public ATilePawn
{
	GENERATED_BODY()
	
public:
	ANPCPawn();

	void TalkWith(ATBSCharacter* InPlayer);
	
	
};
