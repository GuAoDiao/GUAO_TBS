// Fill out your copyright notice in the Description page of Project Settings.

#include "TilePawn.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/SkeletalMeshComponent.h"

#include "GridManager.h"

ATilePawn::ATilePawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	GridAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("GridAnchor"));
	GridAnchor->SetupAttachment(RootComponent);

	PawnSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PawnSkeletalMeshComp"));
	PawnSkeletalMeshComp->SetupAttachment(GridAnchor);
}

void ATilePawn::OnConstruction(const FTransform& Transform)
{
	if (!GridManager && GetWorld())
	{
		TActorIterator<AGridManager> GridManagerItr(GetWorld());
		if (GridManagerItr) { GridManager = *GridManagerItr; }
	}


	if (GridManager)
	{
		Index = GridManager->VectorToIndex(GetActorLocation());

		GridAnchor->SetWorldLocation(GridManager->GetVectorFromIndex(Index));
	}
}
