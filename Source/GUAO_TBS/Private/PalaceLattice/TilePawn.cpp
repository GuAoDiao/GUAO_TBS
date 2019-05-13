// Fill out your copyright notice in the Description page of Project Settings.

#include "TilePawn.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/SkeletalMeshComponent.h"

#include "GridManager.h"
#include "GameFramework/TBSGameAssetManager.h"

ATilePawn::ATilePawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	GridAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("GridAnchor"));
	GridAnchor->SetupAttachment(RootComponent);

	PawnSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PawnSkeletalMeshComp"));
	PawnSkeletalMeshComp->SetupAttachment(GridAnchor);

	AutoPossessAI = EAutoPossessAI::Disabled;

	TilePawnID = -1;
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
		TileIndex = GridManager->VectorToIndex(GetActorLocation());

		GridAnchor->SetWorldLocation(GridManager->GetVectorFromIndex(TileIndex));
	}
	
	if (TilePawnID > 0)
	{
		const FTilePawnInfo* TilePawnInfo = FTBSGameAssetManager::GetInstance()->GetTilePawnInfo(TilePawnID);
		if (TilePawnInfo)
		{
			TilePawnName = TilePawnInfo->Name;

			PawnSkeletalMeshComp->SetSkeletalMesh(TilePawnInfo->SkeletalMesh);
			PawnSkeletalMeshComp->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			PawnSkeletalMeshComp->SetAnimation(TilePawnInfo->IdleAnim);
			PawnSkeletalMeshComp->PlayAnimation(TilePawnInfo->IdleAnim, true);
		}
	}
}
