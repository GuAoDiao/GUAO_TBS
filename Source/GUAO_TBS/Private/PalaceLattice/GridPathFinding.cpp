// Fill out your copyright notice in the Description page of Project Settings.

#include "GridPathFinding.h"

#include "GridManager.h"

FGridPathFinding::FGridPathFinding(AGridManager* InGridManager)
{
	GridMananger = InGridManager;
	check(GridMananger);
}



void FGridPathFinding::Pathfinding(int32 InStartIndex, int32 InTargetIndex)
{
	CurrentSearchStep = 0;
	CurrentStartIndex = InStartIndex;
	CurrentSearchTargetIndex = InTargetIndex;

	CanMoveTilesArray.Empty();
	bFound = false;

	OpenList.Add(FGridPathFindingResult(CurrentStartIndex, 0, 0));

	PathSearchStep();
}

void FGridPathFinding::PathSearchStep()
{
	// Search And Display
	SearchAndAddAdjacentTiles();

	OpenList.Empty();

	++CurrentSearchStep;

	if (bFound)
	{
		EndPathfinding();
	}

	if (OpenListChildren.Num() > 0 || DelayedSearchList.Num() > 0)
	{
		ContinuePathFinding();
	}

	EndPathfinding();
}

void FGridPathFinding::ContinuePathFinding()
{
	OpenList.Append(OpenListChildren);
	OpenList.Append(DelayedSearchList);

	OpenListChildren.Empty();
	DelayedSearchList.Empty();

	PathSearchStep();
}

void FGridPathFinding::EndPathfinding()
{
	OpenListChildren.Empty();

	CanMoveTilesArray.Add(CurrentStartIndex, FGridPathFindingResult(CurrentStartIndex, 0, 0));

	if (bFound)
	{
		PathIndexArray = FindPathFromIndex(CurrentStartIndex, CurrentSearchTargetIndex);
	}
}


void FGridPathFinding::SearchAndAddAdjacentTiles()
{
	for (FGridPathFindingResult& GridPathFiding : OpenList)
	{		
		if (GridPathFiding.Cost == CurrentSearchStep)
		{
			SearchAndAddAdjacentTilesNow(GridPathFiding);
		}
		else
		{
			DelayedSearchList.Add(GridPathFiding);
		}
	}
}


void FGridPathFinding::SearchAndAddAdjacentTilesNow(const FGridPathFindingResult& GridPathFiding)
{
	if (!GridMananger->GridEdgeArray.IsValidIndex(GridPathFiding.Index)) { return; }

	bool bOnOddRow = GridPathFiding.Index / GridMananger->GridSizeX % 2 != 0;

	bool bOnEastEdge = GridPathFiding.Index % GridMananger->GridSizeX == GridMananger->GridSizeX - 1;
	bool bOnWestEdget = GridPathFiding.Index % GridMananger->GridSizeX == 0;

	const int32& Index = GridPathFiding.Index;
	const int32& Cost = GridPathFiding.Cost;
	int32 Direction;

	// Node to the North East
	Direction = bOnOddRow ? Index - GridMananger->GridSizeX + 1 : Index - GridMananger->GridSizeX;
	if (GridMananger->GridEdgeArray.IsValidIndex(Direction) && !(bOnEastEdge && bOnOddRow))
	{
		SearchAndAddTile(Direction, Index, Cost, GridMananger->GridEdgeArray[Direction].NorthEast, GridMananger->GridEdgeArray[Index].SouthWest);
	}

	// Node to the East
	Direction = Index + 1;
	if (GridMananger->GridEdgeArray.IsValidIndex(Direction) && !bOnEastEdge)
	{
		SearchAndAddTile(Direction, Index, Cost, GridMananger->GridEdgeArray[Direction].East, GridMananger->GridEdgeArray[Index].West);
	}

	// Node to the South East
	Direction = bOnOddRow ? Index + GridMananger->GridSizeX + 1 : Index + GridMananger->GridSizeX;
	if (GridMananger->GridEdgeArray.IsValidIndex(Direction) && !(bOnEastEdge && bOnOddRow))
	{
		SearchAndAddTile(Direction, Index, Cost, GridMananger->GridEdgeArray[Direction].SouthEast, GridMananger->GridEdgeArray[Index].NorthWest);
	}

	// Node to the South West
	Direction = bOnOddRow ? Index + GridMananger->GridSizeX : Index + GridMananger->GridSizeX - 1;
	if (GridMananger->GridEdgeArray.IsValidIndex(Direction) && !(bOnWestEdget && !bOnOddRow))
	{
		SearchAndAddTile(Direction, Index, Cost, GridMananger->GridEdgeArray[Direction].SouthWest, GridMananger->GridEdgeArray[Index].NorthEast);
	}

	// Node to the West
	Direction = Index - 1;
	if (GridMananger->GridEdgeArray.IsValidIndex(Direction) && !bOnWestEdget)
	{
		SearchAndAddTile(Direction, Index, Cost, GridMananger->GridEdgeArray[Direction].West, GridMananger->GridEdgeArray[Index].East);
	}

	// Node to the North West
	Direction = bOnOddRow ? Index - GridMananger->GridSizeX : Index - GridMananger->GridSizeX - 1;
	if (GridMananger->GridEdgeArray.IsValidIndex(Direction) && !(bOnWestEdget && !bOnOddRow))
	{
		SearchAndAddTile(Direction, Index, Cost, GridMananger->GridEdgeArray[Direction].NorthWest, GridMananger->GridEdgeArray[Index].SouthEast);
	}
}

void FGridPathFinding::SearchAndAddTile(int32 Direction, int32 ParentIndex, int32 ParentCost, int32 EdgeOwnerFaceToTarget, int32 EdgeTargetFaceToOwner)
{
	// Has the node already been searched
	if (CanMoveTilesArray.Contains(Direction)) { return; }

	// is the edge of the checked node facing the parent not a wall
	if (EdgeOwnerFaceToTarget == 0 || EdgeTargetFaceToOwner == 0) { return; }


	if (Direction == CurrentSearchTargetIndex) { bFound = true; }

	if (!GridMananger->AllTilePawns.Contains(Direction))
	{
		OpenListChildren.Add(FGridPathFindingResult(Direction, ParentCost + EdgeOwnerFaceToTarget, ParentIndex));
	}

	CanMoveTilesArray.Add(Direction, FGridPathFindingResult(0, ParentCost + EdgeOwnerFaceToTarget, ParentIndex));
	
	if (Direction == CurrentSearchTargetIndex)
	{
		bFound = true;
	}
}


TArray<int32> FGridPathFinding::FindPathFromIndex(int32 InStartIndex, int32 InEndIndex)
{
	PathIndexArray.Empty();

	TArray<int32> Result;
	while (true)
	{
		Result.Add(InEndIndex);

		if (CanMoveTilesArray.Contains(InEndIndex))
		{
			int32 TempParentIndex = CanMoveTilesArray[InEndIndex].Parent;
			if (TempParentIndex == InStartIndex)
			{
				return Result;
			}
			else
			{
				InEndIndex = TempParentIndex;
			}
		}
		else
		{
			check(0);
			break;
		}
	}
	return TArray<int32>();
}
