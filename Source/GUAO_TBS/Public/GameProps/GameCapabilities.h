// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameCapabilities.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class GUAO_TBS_API UGameCapabilities : public UObject
{
	GENERATED_BODY()

public:
	UGameCapabilities();

	void InitializeGameCapabilities(UWorld* World, const FString& Info);
	void UseGameCapabilities();

	virtual UWorld* GetWorld() const override { return CurrentWorld; }
protected:
	virtual void ParseStringToInfo(const FString& Info) {}
	virtual void OnUseGameCapabilities() {}
	UWorld* CurrentWorld;
};
