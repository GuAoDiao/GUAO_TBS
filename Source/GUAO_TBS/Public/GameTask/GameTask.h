// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameTask.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameTask : public UObject
{
	GENERATED_BODY()
	
public:
	bool CanAccpet(class ATBSCharacter* Character);
	void BeAccpeted(class ATBSCharacter* Character);

	bool CanFinished();
	void BeCannelled();
	void BeFinished();

	void OnGameTaskOrogress();

	void GetGameTaskDisplayInfo();	

protected:
	class ATBSCharacter* CurrentExcuteCharacter;
};
