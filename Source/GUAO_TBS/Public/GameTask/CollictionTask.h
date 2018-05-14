// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTask/GameTask.h"
#include "CollictionTask.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UCollictionTask : public UGameTask
{
	GENERATED_BODY()
	
public:
	virtual void OnWaitForAcceptImplementation() override;
	virtual void OnAcceptImplementation() override;
	virtual void OnFinishedTaskImplementation() override;

	virtual void UpdateGameState() override;

	void OnPropsStoreItemChange(int32 PropsIndex, int32 PropsID, int32 PropsNum);
	
	
protected:
	FDelegateHandle CollictionDelegate;
	TMap<int32, int32> CollictionInfo;
	TMap<int32, int32> CurrentCollictionInfo;
};
