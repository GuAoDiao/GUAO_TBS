// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameProps/GameCapabilities.h"
#include "MoneyOffsetCapabilities.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UMoneyOffsetCapabilities : public UGameCapabilities
{
	GENERATED_BODY()
	
public:
	virtual void ParseStringToInfo(const FString& Info) override;
	virtual void OnUseGameCapabilities() override;
	
protected:
	int32 MoneyOffset;
	
};
