// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "TBSTypes.h"

#include "CombatPawn.generated.h"

class IDecisionMaker;
class ICombatAction;
class ACombatManager;
class UCombatPawnInfoDisplay;


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
	
	void SetCombatPawnName(const FString& InCombatPawnName);
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//////////////////////////////////////////////////////////////////////////
	/// Combat
	void BeginMakeDecision();
	bool MakeDecision(float DeltaSeconds);
	void BeginExecuteAction();
	bool ExecuteAction(float DeltaSeconds);

	void AcceptDamage(float Damage, ACombatPawn* Causer);

	void UpdateHealth();

	void OnDeath();

	bool bIsDead;
public:
	DECLARE_MULTICAST_DELEGATE(FOnCombatPawnDeathDelegate);
	FOnCombatPawnDeathDelegate& GetOnCombatPawnDeathDelegate() {return OnCombatPawnDeathDelegate;}
protected:
	FOnCombatPawnDeathDelegate OnCombatPawnDeathDelegate;

public:
	ACombatManager* GetCombatManager() const { return CombatManager; }
	void SetCombatManager(ACombatManager* InCombatManager) { CombatManager = InCombatManager; }
	void SetCombatAction(ICombatAction* InCombatAction) { CombatAction = InCombatAction; }
	int32 CombatTeam;

protected:
	IDecisionMaker* DecisionMaker;
	ICombatAction* CombatAction;
	ACombatManager* CombatManager;

public:


	//////////////////////////////////////////////////////////////////////////
	/// Attribute
public:
	UPROPERTY(EditDefaultsOnly)
	FString CombatPawnName;
	UPROPERTY(EditDefaultsOnly)
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
	TSubclassOf<UCombatPawnInfoDisplay> CombatPawnInfoDisplayClass;
	UPROPERTY(Transient)
	UCombatPawnInfoDisplay* CombatPawnInfoDisplay;
};
