// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSTypes.h"

/**
 * 
 */
class GUAO_TBS_API FGridPathFinding
{
public:

	FGridPathFinding(class AGridManager* InGridManager);

	AGridManager* GridMananger;

	void Pathfinding(int32 InStartIndex, int32 InTargetIndex);
	void PathSearchStep();
	void ContinuePathFinding();
	void EndPathfinding();

	void SearchAndAddAdjacentTiles();
	void SearchAndAddAdjacentTilesNow(const FGridPathFindingResult& GridPathFiding);
	void SearchAndAddTile(int32 Direction, int32 ParentIndex, int32 ParentCost, int32 EdgeOwnerFaceToTarget, int32 EdgeTargetFaceToOwner);

	TArray<int32> FindPathFromIndex(int32 InStartIndex, int32 InEndIndex);


	int32 CurrentStartIndex;
	int32 CurrentSearchStep;
	int32 CurrentSearchTargetIndex;
	bool bFound;


	TMap<int32, FGridPathFindingResult> CanMoveTilesArray;
	TArray<FGridPathFindingResult> OpenList;
	TArray<FGridPathFindingResult> OpenListChildren;
	TArray<FGridPathFindingResult> DelayedSearchList;

	int32 CurrentPathEnd;
	TArray<int32> PathIndexArray;
};
