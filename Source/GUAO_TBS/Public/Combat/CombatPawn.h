// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "TBSTypes.h"

#include "CombatPawn.generated.h"

class IDecisionMaker;
class ICombatAction;
class ACombatManager;

UCLASS()
class GUAO_TBS_API ACombatPawn : public APawn
{
	GENERATED_BODY()

public:
	ACombatPawn();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void BeginMakeDecision();
	bool MakeDecision(float DeltaSeconds);
	void BeginExecuteAction();
	bool ExecuteAction(float DeltaSeconds);

	void AcceptDamage(float Damage, ACombatPawn* Causer);

	void UpdateHealth();

	void OnDeath();
	void ResetPawnState();

public:
	DECLARE_MULTICAST_DELEGATE(FOnCombatPawnDeathDelegate);
	FOnCombatPawnDeathDelegate& GetOnCombatPawnDeathDelegate() {return OnCombatPawnDeathDelegate;}
protected:
	FOnCombatPawnDeathDelegate OnCombatPawnDeathDelegate;

public:
	ACombatManager* GetCombatManager() const { return CombatManager; }
	void SetCombatManager(ACombatManager* InCombatManager) { CombatManager = InCombatManager; }
	void SetCombatAction(ICombatAction* InCombatAction) { CombatAction = InCombatAction; }
protected:
	IDecisionMaker* DecisionMaker;
	ICombatAction* CombatAction;
	ACombatManager* CombatManager;

	float CountTime;
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UWidgetComponent* HealthBarComp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCombatPawnHealthBar> HealthBarClass;
	UPROPERTY(Transient)
	class UCombatPawnHealthBar* HealthBar;

	UPROPERTY(EditDefaultsOnly)
	FString CombatPawnName;
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
	

	void BeginAttackAnimation();
	void BeginRunAnimation();
	void BeginIdleAnimation();
	void DelayToSetDeathPosition();
	FTimerHandle DelayToSetDeathPositionTimer;

	FBaseCombatPawnAnimation BaseAnimation;

	bool bIsDead;
	int32 CombatTeam;
};
