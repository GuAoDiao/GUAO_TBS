// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatCapabilities.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class GUAO_TBS_API UCombatCapabilities : public UObject
{
	GENERATED_BODY()
	
	
public:
	UCombatCapabilities();

	void InitializeCombatCapabilities(UWorld* World, const FString& Info);
	void UseCombatCapabilities();

	virtual UWorld* GetWorld() const override { return CurrentWorld; }
protected:
	virtual void ParseStringToInfo(const FString& Info) {}
	virtual void OnUseCombatCapabilities() {}
	UWorld* CurrentWorld;	
};
