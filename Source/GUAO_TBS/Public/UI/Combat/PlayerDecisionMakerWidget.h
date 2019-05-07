// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDecisionMakerWidget.generated.h"


class ACombatPawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPlayerDecisionMakerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BeginMakeDecision(class ACombatPawn* CombatPawn);
	bool MakeDecision(float DeltaSeconds);

	UFUNCTION(BlueprintImplementableEvent)
	void InitializePlayerDecisionMakerUIDisplay(ACombatPawn* CombatPawn);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateRemainintTimeDisplay(int32 RemainingSeconds);


	UFUNCTION(BlueprintCallable)
	void ClearAllDelegate() { SelectTeamDelegate.Unbind(); SelectAttackeDelegate.Unbind(); }

	UFUNCTION(BlueprintPure)
	bool SelectTeamDelegateIsBind() const { return SelectTeamDelegate.IsBound(); }
	UFUNCTION(BlueprintPure)
	bool SelectAttackeDelegateIsBind() const { return SelectAttackeDelegate.IsBound(); }
	UFUNCTION(BlueprintPure)
	bool SelectMultiAttackeDelegateIsBind() const { return SelectMultiAttackeDelegate.IsBound(); }

	UFUNCTION(BlueprintPure)
	int32 GetMaxMultiSelectNum() const { return MaxMultiSelectNum; }

	UFUNCTION(BlueprintCallable)
	void CallSelectTeamDelegate(int32 TargetTeam) { SelectTeamDelegate.ExecuteIfBound(TargetTeam); }
	UFUNCTION(BlueprintCallable)
	void CallSelectAttackeDelegate(int32 TargetTeam, int32 TargetEnemy) { SelectAttackeDelegate.ExecuteIfBound(TargetTeam, TargetEnemy); }
	UFUNCTION(BlueprintCallable)
	void CallSelectMultiAttackeDelegate(int32 TargetTeam, const TArray<int32> TargetEnemy) { SelectMultiAttackeDelegate.ExecuteIfBound(TargetTeam, TargetEnemy); }


	DECLARE_DELEGATE_OneParam(FSelectTeamDelegate, int32 /*TargetTeam*/);
	FSelectTeamDelegate SelectTeamDelegate;
	
	DECLARE_DELEGATE_TwoParams(FSelectAttackeDelegate, int32 /*TargetTeam*/, int32 /*TargetEnemy*/);
	FSelectAttackeDelegate SelectAttackeDelegate;

	DECLARE_DELEGATE_TwoParams(FSelectMultiAttackeDelegate, int32 /*TargetTeam*/, const TArray<int32>& /*TargetEnemy*/);
	FSelectMultiAttackeDelegate SelectMultiAttackeDelegate;


	UFUNCTION(BlueprintImplementableEvent)
	void ShowSelectList(bool bDisplayTeammate, bool bDisplayEnemy);

	//////////////////////////////////////////////////////////////////////////
	/// Make Decision
protected:
	UFUNCTION(BlueprintCallable)
	void WantedToMakeCommonAttackAction();
	UFUNCTION(BlueprintCallable)
	void WantedToMakeTeamAttackAction();
	UFUNCTION(BlueprintCallable)
	void WantedToMakeMultiAttackAction();

	void MakeCommonAttackAction(int32 TargetTeam, int32 TargetEnemy);
	void MakeTeamAttackAction(int32 TargetTeam);
	void MakeMultiAttackAction(int32 TargetTeam, const TArray<int32>& TargetEnemy);

	UFUNCTION(BlueprintCallable)
	void MakeDoNothingAction();
	UFUNCTION(BlueprintCallable)
	void MakeRunAwayAction();

	void MakeCombatAction(class ICombatAction* CombatAction);
protected:
	UPROPERTY(BlueprintReadOnly)
	class ACombatPawn* OwnerCombatPawn;

	float RemainingTime;
	bool bHasMadeDecision;
	int32 MaxMultiSelectNum;
};
