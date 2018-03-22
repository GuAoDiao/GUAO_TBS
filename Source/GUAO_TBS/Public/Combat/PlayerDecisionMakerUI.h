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

	//////////////////////////////////////////////////////////////////////////
	/// Make Decision
	UFUNCTION(BlueprintCallable)
	void MakeCommonAttackAction(int32 TargetTeam, int32 TargetEnemy);
	UFUNCTION(BlueprintCallable)
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
