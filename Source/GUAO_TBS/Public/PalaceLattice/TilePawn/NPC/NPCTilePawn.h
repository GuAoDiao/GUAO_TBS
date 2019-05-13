// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PalaceLattice/TilePawn.h"
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

	void TalkWith(ATBSCharacter* InPlayer);
	
	virtual void OnTalkWithImplementation(ATBSCharacter* InPlayer);
	
	DECLARE_DELEGATE_OneParam(FOnTalkWithDelegate, ATBSCharacter* /*InPlayer*/);
	FOnTalkWithDelegate OnTalkWithDelegate;

	void SetTaskDialogueID(int32 InTaskDialogueID) {TaskDialogueID = InTaskDialogueID;}
protected:
	// Talk when more than zero.
	UPROPERTY(EditDefaultsOnly)
	int32 CommonDialogueID;
	int32 TaskDialogueID;
};