// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn/TilePawn.h"
#include "NPCTilePawn.generated.h"

class ATBSCharacter;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ANPCTilePawn : public ATilePawn
{
	GENERATED_BODY()
	
public:
	ANPCTilePawn();

	virtual void TalkWith(ATBSCharacter* InPlayer);
	


protected:
	UPROPERTY(EditDefaultsOnly)
	FString NPCName;
};
