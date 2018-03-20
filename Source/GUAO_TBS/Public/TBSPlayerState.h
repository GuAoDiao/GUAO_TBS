// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "TBSTypes.h"

#include "TBSPlayerState.generated.h"

class ACombatPawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATBSPlayerState();

	virtual void BeginPlay() override;

public:
	FCombatTeam& GetPlayerCombatPawnTeam() { return AllCombatPawn; }

	FCombatTeam AllCombatPawn;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatPawn> OwnerCombatPawnClass;
};
