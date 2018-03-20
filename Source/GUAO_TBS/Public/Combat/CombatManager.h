// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatManager.generated.h"

class ACombatPawn;

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	Startup,
	BeginCombat,

	ChoosePawn,
	BeginPawnTurn,
	Decision,
	Action,
	EndPawnTurn,

	TurnTeam,

	TurnBout,

	GameOver,
	Results
};

USTRUCT(BlueprintType)
struct FCombatTeam
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ACombatPawn*> AllCombatPawns;
};

struct  FCombatPawnInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginPawnTurnDelegate, const FCombatPawnInfo&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndTurnDelegate, const FCombatPawnInfo&);

USTRUCT(BlueprintType)
struct FCombatPawnInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ACombatPawn* CombatPawn;
	FVector CommonAttackLocation;
	FOnBeginPawnTurnDelegate OnBeginPawnTurn;
	FOnEndTurnDelegate OnEndTurnDelegate;
};

USTRUCT(BlueprintType)
struct FCombatTeamInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCombatPawnInfo> AllCombatPawnInfo;
	UPROPERTY()
	USceneComponent* TeamBaseComps;
};


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

	void CheckCombatState();
	void GameOver();

	//////////////////////////////////////////////////////////////////////////
	/// Combat State
public:
	ECombatState GetCombatState() const { return CurrentCombatState; }
	void ToggleToTargetState(ECombatState InTargetState);
	bool IsToggleTargetState(ECombatState InTargetState) const { return CurrentCombatState == InTargetState; }
protected:
	ECombatState CurrentCombatState;

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 TeamNums;
	UPROPERTY(EditDefaultsOnly)
	TArray<FTransform> TeamBasePosition;
	UPROPERTY(EditDefaultsOnly)
	TArray<class UArrowComponent*> TeamArrowPositionComp;

	void Startup();
	void ChooseFirstPawn();
	void ChooseNextPawn();
	void TurnTeam();
	void TurnBout();

	void BeginPawnTurn();

	void Decision(float DeltaSeconds);
	void Action(float DeltaSeconds);

	void EndPawnTurn();



	int32 CurrentTeamNum;
	int32 CurrentPawnNum;
	int32 CurrentBout;
	int32 PlayerTeam;
	int32 WinTeam;

	bool bWaitingForPawn;

	UPROPERTY(EditDefaultsOnly)
	int32 CharacterMargin;
	UPROPERTY(EditDefaultsOnly)
	int32 CommonAttackMargin;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCombatLayout> CombatLayoutClass;
	UPROPERTY(Transient)
	class UCombatLayout* CombatLayout;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCombatTeamInfo> AllTeamsInfo;
};
