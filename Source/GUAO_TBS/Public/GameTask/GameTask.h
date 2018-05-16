// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBSTypes.h"
#include "GameTask.generated.h"

class ATBSCharacter;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UGameTask : public UObject
{
	GENERATED_BODY()
	
public:

	EGameTaskFlow GetGameTaskFlow() const { return GameTaskFlow; }
	void ToggleToTargetGameTaskFlow(EGameTaskFlow TargetGameTaskFlow);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnToggleToNewGameTaskFlowDelegate, EGameTaskFlow);
	FOnToggleToNewGameTaskFlowDelegate OnToggleToNewGameTaskFlowDelegate;

	void Initilaize(int32 InGameTaskID, FGameTaskInfo* InGameTaskInfo);
	
	virtual void OnInitializeImplementation(int32 InGameTaskID, FGameTaskInfo* InGameTaskInfo) {}

	void WaitForAccept();
	virtual void OnWaitForAcceptImplementation() {};

	bool CanAccpet(ATBSCharacter* Character);

	void BeAccpeted(ATBSCharacter* Character);
	virtual void OnAcceptImplementation() {};

	virtual void UpdateGameState() {};
	
	bool IsFinished() const { return GameTaskFlow == EGameTaskFlow::WaitForCommit; }

	void OnWaitForCompleteTask();
	void OnWaitForCommitTask();

	void OnFinishedTask();
	virtual void OnFinishedTaskImplementation() {};

	void BeCannelled();
	void OnGameTaskOrogress();

	void GetGameTaskDisplayInfo();	

	int32 GetGameTaskID() const { return GameTaskID; }
protected:
	class ATBSCharacter* CurrentExcuteCharacter;
	FGameTaskInfo GameTaskInfo;
	int32 GameTaskID;
	EGameTaskFlow GameTaskFlow;
};
