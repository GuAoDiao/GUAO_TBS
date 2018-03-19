// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CombatPawn.generated.h"

class IDecisionMaker;
class ICombatAction;

UCLASS()
class GUAO_TBS_API ACombatPawn : public APawn
{
	GENERATED_BODY()

public:
	ACombatPawn();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	void BeginMakeDecision();
	bool MakeDecision(float DeltaSeconds);
	void BeginExecuteAction();
	bool ExecuteAction(float DeltaSeconds);


	void SetCombatAction(ICombatAction* InCombatAction) { CombatAction = InCombatAction; }
protected:
	IDecisionMaker* DecisionMaker;
	ICombatAction* CombatAction;

	float CountTime;
protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly)
	float Health;
	UPROPERTY(EditDefaultsOnly)
	float Attack;
	UPROPERTY(EditDefaultsOnly)
	float Defence;
	UPROPERTY(EditDefaultsOnly)
	float Luck;

	float bIsDead;
};
