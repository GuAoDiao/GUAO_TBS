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

	void AccpetGameTask(int32 TaskID);
	void InterruptTask(int32 TaskID);

	const TMap<int32, UGameTask*>& GetAllAccpetTasks() const { return AllAcceptTask; }

	DECLARE_MULTICAST_DELEGATE(FOnAcceptTaskListUpdateDelegate);
	FOnAcceptTaskListUpdateDelegate OnAcceptTaskListUpdateDelegate;
protected:
	class ATBSCharacter* OwnerCharacter;
	TArray<int32> AllFinishedTask;
	TMap<int32 /**TaskID*/, UGameTask*> AllAcceptTask;
	TArray<int32> AllCanAcceptTask;
};
