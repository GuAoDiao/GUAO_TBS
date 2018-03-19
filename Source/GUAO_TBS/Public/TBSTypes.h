// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSTypes.generated.h"

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

USTRUCT()
struct FGridPathFindingResult
{
	GENERATED_USTRUCT_BODY()
public:
	FGridPathFindingResult(int32 InIndex = 0, int32 InCost = 0, int32 InParent = 0) : Index(InIndex), Cost(InCost), Parent(InParent) {}
	int32 Index;
	int32 Cost;
	int32 Parent;
};

#define ECC_PathTrace ECC_GameTraceChannel1
#define ECC_RangeTrace ECC_GameTraceChannel1