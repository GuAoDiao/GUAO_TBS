// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TBSArchiveList.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UTBSArchiveList : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FName> AllArachiveName;
};
