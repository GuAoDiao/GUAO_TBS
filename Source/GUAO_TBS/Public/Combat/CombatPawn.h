// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "TBSTypes.h"

#include "CombatPawn.generated.h"

class IDecisionMaker;
class ICombatAction;
class ACombatManager;
class UCombatPawnInfoWidget;


namespace ECombatPawnState
{
	enum Type
	{
		Idle,
		ReadFight,
		Run,
		Attack,
		BeHit,
		Death,
		OnDeath
	};
}

UCLASS()
class GUAO_TBS_API ACombatPawn : public APawn
{
	GENERATED_BODY()

public:
	ACombatPawn();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//////////////////////////////////////////////////////////////////////////
	/// Combat
public:
	void BeginMakeDecision();
	virtual void MakeDecisionImplementation();
	bool MakeDecision(float DeltaSeconds);
	void BeginExecuteAction();
	bool ExecuteAction(float DeltaSeconds);

public:
	UFUNCTION(BlueprintCallable)
	ACombatManager* GetCombatManager() const { return CombatManager; }
	void SetCombatManager(ACombatManager* InCombatManager) { CombatManager = InCombatManager; }
	void SetCombatAction(ICombatAction* InCombatAction) { CombatAction = InCombatAction; }
	
	int32 CombatTeam;
protected:
	IDecisionMaker* DecisionMaker;
	ICombatAction* CombatAction;
	ACombatManager* CombatManager;

	//////////////////////////////////////////////////////////////////////////
	/// Damage , Health, Death;
public:
	void AcceptDamage(float Damage, ACombatPawn* Causer);
	void UpdateHealth();
	void OnDeath();
	UFUNCTION(BlueprintPure)
	bool IsCombatPawnDead() const { return bIsDead; }

protected:
	bool bIsDead;
public:
	DECLARE_MULTICAST_DELEGATE(FOnCombatPawnDeathDelegate);
	FOnCombatPawnDeathDelegate OnCombatPawnDeathDelegate;
	
	//////////////////////////////////////////////////////////////////////////
	/// Attribute
public:
	void SetCombatPawnID(int32 InCombatPawnID);
	int32 GetCombatPawnID() const { return CombatPawnID; }

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 CombatPawnID;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString CombatPawnName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Level;

	float MaxHealth;
	float Health;
	float MaxMana;
	float Mana;
	float Attack;
	float Defence;
	float Luck;
	
	void InitializeCombatPawnAttribute();
	void ResetPawnState();
protected:
	FBaseCombatPawnFightInfo BaseFightInfo;


	//////////////////////////////////////////////////////////////////////////
	/// Combat Pawn State
public:
	ECombatPawnState::Type GetCombatPawnState() const { return CurrentCombatPawnState; }
	void ToggleToTargetCombatPawnState(ECombatPawnState::Type TargetCombatPawnState);


protected:
	void ToggleToIdleState();
	void ToggleToReadFightState();
	void ToggleToRunState();
	void ToggleToAttackState();
	void ToggleToBeHitState();
	void ToggleToOnDeathState();
	void ToggleToDeathState();

	void DelayToSetDeathState();
	void DelayToSetIdleState();

	FTimerHandle DelayToSetDeathStateTimer;
	FTimerHandle DelayToSetIdleStateTimer;

	ECombatPawnState::Type CurrentCombatPawnState;

	//////////////////////////////////////////////////////////////////////////
	/// Display
protected:
	FBaseCombatPawnDisplayInfo BaseDisplayInfo;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComp;

	//////////////////////////////////////////////////////////////////////////
	/// Combat Pawn Info Display
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UWidgetComponent* CombatPawnInfoDisplayComp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCombatPawnInfoWidget> CombatPawnInfoDisplayClass;
	UPROPERTY(Transient)
	UCombatPawnInfoWidget* CombatPawnInfoDisplay;
};
