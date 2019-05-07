// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Templates/SubclassOf.h"

#include "TBSTypes.generated.h"

//////////////////////////////////////////////////////////////////////////
/// Grid

UENUM(BlueprintType)
enum class  ETBSTileType : uint8
{
	Empty,
	Player,
	NPC,
	Enemy
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

//////////////////////////////////////////////////////////////////////////
/// Combat
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

	FightEnd,
	RunAway,

	Results
};


USTRUCT(BlueprintType)
struct FBaseCombatPawnDisplayInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	int32 ID;

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
	int32 ID;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACombatPawn > CombatPawnClass;
};

USTRUCT(BlueprintType)
struct FBaseCombatPawnFightInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	int32 ID;
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TeamName;
};

struct FCombatPawnInfo;


USTRUCT(BlueprintType)
struct FCombatPawnInfo
{
	GENERATED_USTRUCT_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginPawnTurnDelegate, const FCombatPawnInfo&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndTurnDelegate, const FCombatPawnInfo&);

	UPROPERTY(BlueprintReadOnly)
	ACombatPawn* CombatPawn;
	UPROPERTY(BlueprintReadOnly)
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
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* TeamBaseComps;
	UPROPERTY(BlueprintReadOnly)
	FVector TeamCommonAttackLocation;
	UPROPERTY(BlueprintReadOnly)
	FString TeamName;
};


//////////////////////////////////////////////////////////////////////////
/// Tile Pawn
USTRUCT(BlueprintType)
struct FTilePawnInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	int32 ID;
	UPROPERTY(EditDefaultsOnly)
	FName Name;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditDefaultsOnly)
	class UAnimationAsset* IdleAnim;
};

//////////////////////////////////////////////////////////////////////////
/// Dialogue

UENUM(BlueprintType)
enum class EDialogueType : uint8
{
	Common,
	Final,
	Choice,
	AcceptTask,
	CompleteTask
};

USTRUCT(BlueprintType)
struct FDialogueInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText Content;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 NextID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EDialogueType Type;
};

USTRUCT(BlueprintType)
struct FDialogueClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EDialogueType Type;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<class UDialogueWidget > DialogueClass;
};

USTRUCT(BlueprintType)
struct FDialogueTaskInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 DialogueID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 TaskID;
};


USTRUCT(BlueprintType)
struct FDialogueChoiceInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 DialogueID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<int32 /*NextDialogueID*/, FText/*SelectOption*/> SelectOptions;
};


UENUM(BlueprintType)
enum class EGameTaskFlow : uint8
{
	Initialize,
	WaitForAccept,
	WaitForComplete,
	WaitForCommit,
	Finished,
};

UENUM(BlueprintType)
enum class EGameTaskType : uint8
{
	KillTask,
	DialogueTask,
	CollictionTask,
	Custom
};

USTRUCT(BlueprintType)
struct FGameTaskInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FGameTaskInfo() : AcceptFromNPCID(-1),FinishedNPCID(-1),WaitingDialogueID(-1) {}
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 AcceptFromNPCID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 AcceptFromDialogueID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 FinishedNPCID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 WaitingDialogueID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 FinishedDialogueID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText Title;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText Description;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EGameTaskType Type;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<class UGameTask > TaskClass;
};

USTRUCT(BlueprintType)
struct FGameTaskAcceptableConditions : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FGameTaskAcceptableConditions() : Level(-1), PredecessorTask(-1) {}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 Level;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 PredecessorTask;
};

USTRUCT(BlueprintType)
struct FGameKillTaskInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<int32/*EnemyID*/, int32/*Nums*/> TaskInfo;
};

USTRUCT(BlueprintType)
struct FGameCollectionTaskInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<int32/*PropID*/, int32/*Nums*/> TaskInfo;
};


#define ECC_PathTrace ECC_GameTraceChannel1
#define ECC_RangeTrace ECC_GameTraceChannel1