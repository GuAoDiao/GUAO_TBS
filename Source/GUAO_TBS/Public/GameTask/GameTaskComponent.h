// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameTaskComponent.generated.h"

class UGameTask;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUAO_TBS_API UGameTaskComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameTaskComponent();

	virtual void BeginPlay() override;

	void OnLevelUp(int32 Level);

	void UpdateAllCanAcceptTask();

	void AccpetGameTask(int32 TaskID);
	void InterruptTask(int32 TaskID);
	void CompleteGameTask(int32 TaskID);

	bool TargetTaskIsFinished(int32 TaskID);


	const TMap<int32, UGameTask*>& GetAllAccpetTasks() const { return AllAcceptTask; }
	const TMap<int32, UGameTask*>& GetAllCanAcceptTask() const { return AllCanAcceptTask; }

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCanAcceptTaskAddDelegate, int32 /*TaskID*/, UGameTask* /*GameTask*/);
	FOnCanAcceptTaskAddDelegate OnCanAcceptTaskAddDelegate;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAcceptTaskDelegate, int32 /*TaskID*/, UGameTask* /*GameTask*/);
	FOnAcceptTaskDelegate OnAcceptTaskDelegate;
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInterruptTaskDelegate, int32 /*TaskID*/, UGameTask* /*GameTask*/);
	FOnInterruptTaskDelegate OnInterruptTaskDelegate;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinishedTaskDelegate, int32 /*TaskID*/, UGameTask* /*GameTask*/);
	FOnFinishedTaskDelegate OnFinishedTaskDelegate;
protected:
	class ATBSCharacter* OwnerCharacter;
	TArray<int32> AllFinishedTask;
	UPROPERTY()
	TMap<int32 /**TaskID*/, UGameTask*> AllAcceptTask;
	UPROPERTY()
	TMap<int32 /**TaskID*/, UGameTask*> AllCanAcceptTask;
};
