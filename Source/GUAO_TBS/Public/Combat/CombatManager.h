// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TBSTypes.h"

#include "CombatManager.generated.h"

class ACombatPawn;


UCLASS()
class GUAO_TBS_API ACombatManager : public AActor
{
	GENERATED_BODY()
	
public:
	ACombatManager();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void InitiallizeCombat(const TArray<FCombatTeam>& InAllTeams, int32 InPlayerTeam);

	//////////////////////////////////////////////////////////////////////////
	/// Base Combat Info
protected:
	UPROPERTY(EditDefaultsOnly)
	int32 TeamNums;
	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> TeamBasePosition;
	UPROPERTY(EditDefaultsOnly)
	int32 CharacterMargin;
	UPROPERTY(EditDefaultsOnly)
	int32 CommonAttackMargin;
	UPROPERTY(EditDefaultsOnly)
	TArray<class UArrowComponent*> TeamArrowPositionComp;

	//////////////////////////////////////////////////////////////////////////
	/// Base Comp
public:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	//////////////////////////////////////////////////////////////////////////
	/// Combat State
public:
	ECombatState GetCombatState() const { return CurrentCombatState; }
	void ToggleToTargetState(ECombatState InTargetState);
	bool IsToggleTargetState(ECombatState InTargetState) const { return CurrentCombatState == InTargetState; }
protected:
	ECombatState CurrentCombatState;

	//////////////////////////////////////////////////////////////////////////
	/// Combat Run
protected:
	void Startup();
	void BeginCombat();
	void ChooseNextPawn();
	void TurnTeam();
	void TurnBout();

	void BeginPawnTurn();

	void Decision(float DeltaSeconds);
	void Action(float DeltaSeconds);

	void EndPawnTurn();
	void CheckCombatState();

	void FightEnd();
	void RunAway();
	UFUNCTION(BlueprintCallable)
	void CloseCombat();

	
public:
	bool TryToRunAway(ACombatPawn* InCombatPawn);

	UFUNCTION(BlueprintPure)
	int32 GetPlayerTeam() const { return PlayerTeam; }
	UFUNCTION(BlueprintPure)
	bool IsAutoAttack() const { return bIsAutoAttack; }
	UFUNCTION(BlueprintCallable)
	void SetIsAutoAttack(bool bInIsAutoAttack);
protected:

	int32 CurrentTeamNum;
	int32 CurrentPawnNum;
	int32 CurrentBout;
	int32 PlayerTeam;
	int32 WinTeam;

	bool bWaitingForPawn;
	bool bWantedAndCanRunAway;
	bool bIsAutoAttack;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCombatTeamInfo> AllTeamsInfo;

	//////////////////////////////////////////////////////////////////////////
	/// UI Display

protected:
	UPROPERTY(Transient)
	class UCombatLayout* CombatLayout;
};
