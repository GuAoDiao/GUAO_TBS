// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTask/GameTask.h"
#include "DialogueTask.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UDialogueTask : public UGameTask
{
	GENERATED_BODY()
	
public:
	virtual void UpdateGameState() override;
};
