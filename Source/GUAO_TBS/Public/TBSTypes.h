// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "TBSTypes.generated.h"

UENUM(BlueprintType)
enum class  ETBSTileType : uint8
{
	Empty,
	Player,
	NPC,
	Enemy
};

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
struct FGridEdgesCost
{
	GENERATED_USTRUCT_BODY()
public:
	static const FGridEdgesCost FullGridEdge;
	static const FGridEdgesCost EmptyGridEdge;

	FGridEdgesCost(int32 InEast = 5, int32 InWest = 5, int32 InNorthEast = 5, int32 InSouthEast = 5, int32 InSouthWest = 5, int32 InNorthWest = 5)
	: East(InEast), West(InWest), NorthEast(InNorthEast), NorthWest(InNorthWest), SouthEast(InSouthEast), SouthWest(InSouthWest) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 East;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 West;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NorthEast;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SouthEast;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SouthWest;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NorthWest;
};

struct FGridPathFindingResult
{
public:
	FGridPathFindingResult(int32 InIndex = 0, int32 InCost = 0, int32 InParent = 0) : Index(InIndex), Cost(InCost), Parent(InParent) {}
	int32 Index;
	int32 Cost;
	int32 Parent;
};


USTRUCT(BlueprintType)
struct FBaseCombatPawnDisplayInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FString CombatPawnName;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditDefaultsOnly)
	FVector SkeletalMeshScale;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* IdleAnimAsset;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* ReadFightAnimAsset;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* RunAnimAsset;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* AttackAnimAsset;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* AccpetDamageAnimAsset;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* OnDeathAnimAsset;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* DeathAnimAsset;
};

USTRUCT(BlueprintType)
struct FCombatPawnClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FString CombatPawnName;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACombatPawn> CombatPawnClass;
};

USTRUCT(BlueprintType)
struct FBaseCombatPawnFightInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FString CombatPawnName;
	UPROPERTY(EditDefaultsOnly)
	int32 Level;
	UPROPERTY(EditDefaultsOnly)
	float MHP;
	UPROPERTY(EditDefaultsOnly)
	float MMP;
	UPROPERTY(EditDefaultsOnly)
	float Attack;
	UPROPERTY(EditDefaultsOnly)
	float Defence;
	UPROPERTY(EditDefaultsOnly)
	float Luck;
};


USTRUCT(BlueprintType)
struct FCombatTeam
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class ACombatPawn*> AllCombatPawns;
};

struct FCombatPawnInfo;


USTRUCT(BlueprintType)
struct FCombatPawnInfo
{
	GENERATED_USTRUCT_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginPawnTurnDelegate, const FCombatPawnInfo&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndTurnDelegate, const FCombatPawnInfo&);

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


#define ECC_PathTrace ECC_GameTraceChannel1
#define ECC_RangeTrace ECC_GameTraceChannel1