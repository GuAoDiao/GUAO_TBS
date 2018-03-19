// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticMeshTile.h"

#include "Components/StaticMeshComponent.h"

AStaticMeshTile::AStaticMeshTile()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetCastShadow(false);
	StaticMeshComp->SetupAttachment(GridAnchor);

	EdgeCosts = FGridEdgesCost::EmptyGridEdge;
}

