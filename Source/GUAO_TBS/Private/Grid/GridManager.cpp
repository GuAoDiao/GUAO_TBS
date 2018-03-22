// Fill out your copyright notice in the Description page of Project Settings.

#include "GridManager.h"

#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "EngineUtils.h"

#include "GridPathFinding.h"
#include "TilePawn.h"
#include "SceneObject/BasedTile.h"

AGridManager::AGridManager()
{
	GridSizeX = GridSizeY = 10;
	bShowCollisionPlane = true;
	bShowDefaultTile = true;
	bSnapToCustomGrid = true;
	bCollisionPlaneWalkable = true;
	bAutoCalculateCostsBaseOnHeight = true;
	bPregenerateGameplayGrids = true;
	HeightImpassableCutoff = 100.f;

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	CollisionPlaneComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionPlaneComp"));
	CollisionPlaneComp->SetupAttachment(GetRootComponent());

	DefaultInstanceTileComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("DefaultInstanceTileComp"));;
	DefaultInstanceTileComp->SetupAttachment(GetRootComponent());
}

FVector AGridManager::GetVectorFromIndex(int32 Index) const
{
	if (FieldLocationArray.IsValidIndex(Index))
	{
		return FieldLocationArray[Index] + GetActorLocation();
	}
	return FVector::ZeroVector;
}

FVector AGridManager::GetVectorFromIndexOnGrid(int32 Index, float ZOffset) const
{
	if (FieldLocationArray.IsValidIndex(Index))
	{
		FVector Location = FieldLocationArray[Index] + GetActorLocation();
		Location.Z += ZOffset;
		return Location;
	}
	return FVector::ZeroVector;
}

void AGridManager::OnConstruction(const FTransform& Transform)
{
	// add the default tile mesh to the grid
	DefaultInstanceTileComp->SetVisibility(bShowDefaultTile);

	// saving its bounds in TileBoundsX,Y
	if (DefaultGridMesh)
	{
		FBoxSphereBounds MeshBounds = DefaultGridMesh->GetBounds();

		TileBoundsX = 2 * MeshBounds.BoxExtent.X;
		TileBoundsY = 2 * MeshBounds.BoxExtent.Y;
	}

	// make the gap between tiles in the Y direction smaller for hexagonal grids
	NodeGapY = TileBoundsY * 0.86603f; 

	// This makes individual collision volumes unecessary for flat grids, and makes it possible to place meshes in the viewport if the default tile is invisible
	ScaleAndPositionCollisionPlaen();

	CollisionPlaneComp->SetVisibility(bShowCollisionPlane);
	if (bCollisionPlaneWalkable)
	{
		CollisionPlaneComp->SetCollisionResponseToChannel(ECC_PathTrace, ECR_Block);
		CollisionPlaneComp->SetCollisionResponseToChannel(ECC_RangeTrace, ECR_Block);
	}
	else
	{
		CollisionPlaneComp->SetCollisionResponseToChannel(ECC_PathTrace, ECR_Ignore);
		CollisionPlaneComp->SetCollisionResponseToChannel(ECC_RangeTrace, ECR_Ignore);
	}

	// create the vector grids that from the basis of moving between grid array indexes and world locations
	FieldLocationArray.Empty();
	for (int32 i = 0, l = GridSizeX * GridSizeY; i < l; ++i)
	{
		FieldLocationArray.Add(CreateVectorFromIndex(i));
	}

	// spawn tile grid
	if (bShowDefaultTile && DefaultGridMesh)
	{
		DefaultInstanceTileComp->SetStaticMesh(DefaultGridMesh);
		DefaultInstanceTileComp->ClearInstances();

		for (const FVector& TileLocation : FieldLocationArray)
		{
			DefaultInstanceTileComp->AddInstance(FTransform(TileLocation));
		}
	}

	if (bPregenerateGameplayGrids) { InitializeGridEdgeArray(); }
}


void AGridManager::InitializeGridEdgeArray()
{
	int32 Size = GridSizeX * GridSizeY;

	GridEdgeArray.SetNum(Size);

	FGridEdgesCost GridEdges = bCollisionPlaneWalkable ? FGridEdgesCost::FullGridEdge : FGridEdgesCost::EmptyGridEdge;

	for (int32 i = 0; i < Size; ++i)
	{
		GridEdgeArray[i] = GridEdges;
	}
}



void AGridManager::BeginPlay()
{	
	Super::BeginPlay();

	if (!bPregenerateGameplayGrids) { InitializeGridEdgeArray(); }

	AddViewportTerrainToArrays();

	AddAllTilePawnToArrays();
}

void AGridManager::AddViewportTerrainToArrays()
{
	// Gets the edge costs of all tile actors and add them to the edge array.
	// If there are two tile actors on the same tile it adds the highest cost for each edge, or adds a wall if either of the actors' edges has a wall

	
	if (!bCollisionPlaneWalkable)
	{
		for (TActorIterator<ABasedTile> BasedTileIterator(GetWorld()); BasedTileIterator; ++BasedTileIterator)
		{
			if (GridEdgeArray.IsValidIndex(BasedTileIterator->TileIndex))
			{

				GridEdgeArray[BasedTileIterator->TileIndex] = FGridEdgesCost::FullGridEdge;
			}
		}
	}

	for (TActorIterator<ABasedTile> BasedTileIterator(GetWorld()); BasedTileIterator; ++BasedTileIterator)
	{

		int32 Index = BasedTileIterator->TileIndex;
		if (GridEdgeArray.IsValidIndex(Index))
		{
			GridEdgeArray[Index].East = GetMaxValueWhenAllNotZero(BasedTileIterator->EdgeCosts.East, GridEdgeArray[Index].East);
			GridEdgeArray[Index].West = GetMaxValueWhenAllNotZero(BasedTileIterator->EdgeCosts.West, GridEdgeArray[Index].West);
			GridEdgeArray[Index].SouthEast = GetMaxValueWhenAllNotZero(BasedTileIterator->EdgeCosts.SouthEast, GridEdgeArray[Index].SouthEast);
			GridEdgeArray[Index].SouthWest = GetMaxValueWhenAllNotZero(BasedTileIterator->EdgeCosts.SouthWest, GridEdgeArray[Index].SouthWest);
			GridEdgeArray[Index].NorthEast = GetMaxValueWhenAllNotZero(BasedTileIterator->EdgeCosts.NorthEast, GridEdgeArray[Index].NorthEast);
			GridEdgeArray[Index].NorthWest = GetMaxValueWhenAllNotZero(BasedTileIterator->EdgeCosts.NorthWest, GridEdgeArray[Index].NorthWest);

			// If height differences are used, update the vector field array according to the tile actors in the viewport
			if (bAutoCalculateCostsBaseOnHeight)
			{
				float ActorHeight = BasedTileIterator->GetActorLocation().Z;
				if (ActorHeight != 0.f)
				{
					int32 Index = BasedTileIterator->TileIndex;
					if (FieldLocationArray.IsValidIndex(Index)) { FieldLocationArray[Index].Z = ActorHeight; }
				}
			}
		}
	}
	SetEdgesOfTiles();
}

void AGridManager::AddAllTilePawnToArrays()
{
	for (TActorIterator<ATilePawn> TilePawnIterator(GetWorld()); TilePawnIterator; ++TilePawnIterator)
	{
		if (TilePawnIterator->GetGridAnchor())
		{
			FVector Location = TilePawnIterator->GetGridAnchor()->GetComponentLocation();
			TilePawnIterator->SetActorLocation(Location);
			TilePawnIterator->GetGridAnchor()->SetWorldLocation(Location);

			AllTilePawns.Add(TilePawnIterator->GetTileIndex(), *TilePawnIterator);
		}
	}
}

int32 AGridManager::GetMaxValueWhenAllNotZero(int32 FirstValue, int32 SecondValue)
{
	if (FirstValue == 0 || SecondValue == 0)
	{
		return 0;
	}
	return FMath::Max(FirstValue, SecondValue);
}



int32 AGridManager::VectorToIndex(const FVector& Location) const
{
	FVector OwnerLocation = GetActorLocation();
	float IndexX, IndexY;
	IndexX = TileBoundsX / 2 + Location.X - OwnerLocation.X;
	IndexY = TileBoundsY * 0.375f + Location.Y - OwnerLocation.Y;
	IndexY /= TileBoundsY * 0.75f;
	IndexX -= FMath::FloorToInt(IndexY) % 2 * (TileBoundsX * 0.5f);
	IndexX /= TileBoundsX;

	return FMath::FloorToInt(IndexX) + FMath::FloorToInt(IndexY) * GridSizeX;
}

FVector AGridManager::CreateVectorFromIndex(int32 Index) const
{
	FVector Location;
	Location.X = (Index / GridSizeX % 2) * (TileBoundsX / 2) + (Index  % GridSizeX * TileBoundsX);
	Location.Y = Index / GridSizeX * (TileBoundsY * 0.75f);
	Location.Z = 0.f;
	return Location;
}


void AGridManager::ScaleAndPositionCollisionPlaen()
{
	FVector Vector;
	Vector.X = (0.5f + GridSizeX - 1) * (TileBoundsX / 2.f);
	float Temp = TileBoundsY * 0.75f;
	Vector.Y = (GridSizeY - 1.f) * Temp / 2.f;
	Vector.Z = 0.f;
	CollisionPlaneComp->SetWorldLocation(Vector);

	Vector.X = (0.5f + GridSizeX) * TileBoundsX / 200.f;
	Vector.Y = (GridSizeY + 0.25f) * Temp / 200.f;
	Vector.Z = 1.f;
	CollisionPlaneComp->SetWorldScale3D(Vector);
}

void AGridManager::ScaleRelativeToDefaultTile(UStaticMeshComponent* InStaticMeshComp)
{
	InStaticMeshComp->SetWorldScale3D(FVector(TileBoundsX / 200.f, TileBoundsY / 200.f * 0.86603, 1));
}

void AGridManager::SetEdgesOfTiles()
{
	for (int32 i = 0; i < FieldLocationArray.Num(); ++i)
	{
		float FieldHeight = FieldLocationArray[i].Z;
		bool bOnOddRow = i / GridSizeX % 2 != 0;

		int32 Index;

		// Node to the North East
		Index = bOnOddRow ? i - GridSizeX + 1 : i - GridSizeX;
		if (FieldLocationArray.IsValidIndex(Index) && GridEdgeArray.IsValidIndex(Index))
		{
			if (!(FMath::Abs(FieldLocationArray[Index].Z - FieldHeight) < HeightImpassableCutoff))
			{
				GridEdgeArray[Index].SouthWest = 0;
			}
		}

		// Node to the East
		Index = i + 1;
		if (FieldLocationArray.IsValidIndex(Index) && GridEdgeArray.IsValidIndex(Index))
		{
			if (!(FMath::Abs(FieldLocationArray[Index].Z - FieldHeight) < HeightImpassableCutoff))
			{
				GridEdgeArray[Index].West = 0;
			}
		}

		// Node to the South East
		Index = bOnOddRow ? i + GridSizeX + 1 : i + GridSizeX;
		if (FieldLocationArray.IsValidIndex(Index) && GridEdgeArray.IsValidIndex(Index))
		{
			if (!(FMath::Abs(FieldLocationArray[Index].Z - FieldHeight) < HeightImpassableCutoff))
			{
				GridEdgeArray[Index].NorthWest = 0;
			}
		}

		// Node to the South West
		Index = bOnOddRow ? i + GridSizeX : i + GridSizeX - 1;
		if (FieldLocationArray.IsValidIndex(Index) && GridEdgeArray.IsValidIndex(Index))
		{
			if (!(FMath::Abs(FieldLocationArray[Index].Z - FieldHeight) < HeightImpassableCutoff))
			{
				GridEdgeArray[Index].NorthEast = 0;
			}
		}

		// Node to the West
		Index = i - 1;
		if (FieldLocationArray.IsValidIndex(Index) && GridEdgeArray.IsValidIndex(Index))
		{
			if (!(FMath::Abs(FieldLocationArray[Index].Z - FieldHeight) < HeightImpassableCutoff))
			{
				GridEdgeArray[Index].East = 0;
			}
		}

		// Node to the North West
		Index = bOnOddRow ? i - GridSizeX : i - GridSizeX - 1;
		if (FieldLocationArray.IsValidIndex(Index) && GridEdgeArray.IsValidIndex(Index))
		{
			if (!(FMath::Abs(FieldLocationArray[Index].Z - FieldHeight) < HeightImpassableCutoff))
			{
				GridEdgeArray[Index].SouthEast = 0;
			}
		}
	}

}