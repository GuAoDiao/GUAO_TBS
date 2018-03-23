// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatPawn.h"
#include "CombatLeadingRolePawn.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API ACombatLeadingRolePawn : public ACombatPawn
{
	GENERATED_BODY()
	
public:
	virtual void MakeDecisionImplementation() override;	
	
	
};
