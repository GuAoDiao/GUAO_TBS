// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDecisionMakerUI.generated.h"


class ACombatPawn;

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UPlayerDecisionMakerUI : public UUserWidget
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
	bool SelectTeamDelegateIsBind() { return SelectTeamDelegate.IsBound(); }
	UFUNCTION(BlueprintPure)
	bool SelectAttackeDelegateIsBind() { return SelectAttackeDelegate.IsBound(); }

	UFUNCTION(BlueprintCallable)
	void CallSelectTeamDelegate(int32 TargetTeam) { SelectTeamDelegate.ExecuteIfBound(TargetTeam); }
	UFUNCTION(BlueprintCallable)
	void CallSelectAttackeDelegate(int32 TargetTeam, int32 TargetEnemy) { SelectAttackeDelegate.ExecuteIfBound(TargetTeam, TargetEnemy); }

	DECLARE_DELEGATE_OneParam(FSelectTeamDelegate, int32 /*TargetTeam*/);
	FSelectTeamDelegate SelectTeamDelegate;
	
	DECLARE_DELEGATE_TwoParams(FSelectAttackeDelegate, int32 /*TargetTeam*/, int32 /*TargetEnemy*/);
	FSelectAttackeDelegate SelectAttackeDelegate;

	//////////////////////////////////////////////////////////////////////////
	/// Make Decision
protected:
	UFUNCTION(BlueprintCallable)
	void WantedToMakeCommonAttackAction() { SelectAttackeDelegate.BindUObject(this, &UPlayerDecisionMakerUI::MakeCommonAttackAction); }
	UFUNCTION(BlueprintCallable)
	void WantedToMakeTeamAttackAction() { SelectTeamDelegate.BindUObject(this, &UPlayerDecisionMakerUI::MakeTeamAttackAction); }
	
	void MakeCommonAttackAction(int32 TargetTeam, int32 TargetEnemy);
	void MakeTeamAttackAction(int32 TargetTeam);

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
};
