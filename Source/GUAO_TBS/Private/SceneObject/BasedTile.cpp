// Fill out your copyright notice in the Description page of Project Settings.

#include "BasedTile.h"

#include "EngineUtils.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "GridManager.h"


ABasedTile::ABasedTile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	GridAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("GridAnchor"));
	GridAnchor->SetupAttachment(RootComponent);

	EdgeCosts = FGridEdgesCost::EmptyGridEdge;
}


void ABasedTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


	if (!GridManager)
	{
		if (GetWorld())
		{
			TActorIterator<AGridManager> GridManagerItr(GetWorld());
			if (GridManagerItr) { GridManager = *GridManagerItr; }
		}
	}

	if (GridManager)
	{
		Index = GridManager->VectorToIndex(GetActorLocation());

		if (GridManager->bSnapToCustomGrid && !bIgnoreSnapToCustomGrid)
		{
			FVector Location = GridManager->GetVectorFromIndex(Index);

			if (bPlaceActorAtAnchor) { SetActorLocation(Location); }

			if (GridAnchor) { GridAnchor->SetWorldLocation(Location); }
		}
	}
}