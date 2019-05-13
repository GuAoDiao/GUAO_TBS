// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TBSArchiveItem.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UTBSArchiveItem : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName ArchiveName;
	UPROPERTY()
	FString PlayerName;
	UPROPERTY()
	FName CharacterName;
	
	UPROPERTY()
	int64 Gold;
	
	UPROPERTY()
	int8 Level;
	UPROPERTY()
	int32 Experience;
	
	UPROPERTY()
	FName LevelName;
	UPROPERTY()
	FVector2D Position;
};
