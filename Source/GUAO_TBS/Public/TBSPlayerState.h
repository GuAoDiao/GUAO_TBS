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

	//////////////////////////////////////////////////////////////////////////
	/// Player Combat Pawn
public:
	void InitializePlayerCombatTeam();
	FCombatTeam& GetPlayerCombatTeam() { return PlayerCombatTeam; }

	FCombatTeam PlayerCombatTeam;
	UPROPERTY(EditDefaultsOnly)
	TArray<FString> CombatPawnNameInPlayerTeam;
};
