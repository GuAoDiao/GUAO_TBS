// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSCharacter.h"

#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GridManager.h"
#include "GridPathFinding.h"
#include "TilePawn/NPC/NPCTilePawn.h"
#include "TilePawn/Enemy/EnemyTilePawn.h"

ATBSCharacter::ATBSCharacter()
{
	bDisableClickTile = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->TargetArmLength = 2000.f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->SetupAttachment(GridAnchor);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ScrollRoof = 2000.f;
	ScrollFloor = 600.f;

	CameraMoveSpeed = 2000.f;
	CameraRotateSpeed = 1000.f;
	CameraScrollSpeed = 200000.f;


	MovePathComp = CreateDefaultSubobject<USplineComponent>(TEXT("MovePathComp"));
	SplineHeight = 0.7f;

	CurrentSpeed = 0.f;
	PawnMaxSpeed = 500.f;
	PawnMovementSpeedAcceleration = 25.f;
	bCanMoveViewport = true;

	TileType = ETBSTileType::Player;
}

void ATBSCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpringArmComp->AttachToComponent(GridAnchor, FAttachmentTransformRules::KeepWorldTransform);
	if (GridManager)
	{
		MovePathComp->AttachToComponent(GridManager->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	}
	ResetAngleOfView();
}

void ATBSCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsMoving) { TickMovement(DeltaSeconds); }
}

void ATBSCharacter::RebindInputComponent(UInputComponent* InInputComp)
{
	if (InInputComp)
	{
		InInputComp->BindAxis("MoveRight", this, &ATBSCharacter::MoveHorizontal);
		InInputComp->BindAxis("MoveForward", this, &ATBSCharacter::MoveVertical);
		InInputComp->BindAxis("RotatingAngleOfView", this, &ATBSCharacter::RotatingAngleOfView);


		InInputComp->BindAction("ZoomIn", IE_Pressed, this, &ATBSCharacter::ZoomIn);
		InInputComp->BindAction("ZoomOut", IE_Pressed, this, &ATBSCharacter::ZoomOut);
		InInputComp->BindAction("ResetAngleOfView", IE_Pressed, this, &ATBSCharacter::ResetAngleOfView);

		InInputComp->BindAction("ClickedTile", IE_Pressed, this, &ATBSCharacter::ClickedTile);
	}
}

void ATBSCharacter::ZoomIn()
{
	if (bCanMoveViewport && SpringArmComp->TargetArmLength < ScrollRoof)
	{
		SpringArmComp->TargetArmLength = FMath::Lerp(SpringArmComp->TargetArmLength, SpringArmComp->TargetArmLength + CameraScrollSpeed * GetWorld()->GetDeltaSeconds(), 0.1f);
	}
}

void ATBSCharacter::ZoomOut()
{
	if (bCanMoveViewport && SpringArmComp->TargetArmLength > ScrollFloor)
	{
		SpringArmComp->TargetArmLength = FMath::Lerp(SpringArmComp->TargetArmLength, SpringArmComp->TargetArmLength - CameraScrollSpeed * GetWorld()->GetDeltaSeconds(), 0.1f);
	}
}


void ATBSCharacter::RotatingAngleOfView(float AxisValue)
{
	if (AxisValue != 0.f && bCanMoveViewport)
	{
		FRotator Rotation = SpringArmComp->GetComponentRotation();
		Rotation.Yaw = FMath::Lerp(Rotation.Yaw, Rotation.Yaw + AxisValue * GetWorld()->GetDeltaSeconds() * CameraRotateSpeed, 0.2f);
		SpringArmComp->SetWorldRotation(Rotation);
	}
}

void ATBSCharacter::ResetAngleOfView()
{
	if (bCanMoveViewport)
	{
		FRotator Rotation = SpringArmComp->GetComponentRotation();
		Rotation.Yaw = 0.f;
		SpringArmComp->SetWorldRotation(Rotation);
	}
}

void ATBSCharacter::MoveHorizontal(float AxisValue)
{
	if (AxisValue != 0.f && bCanMoveViewport)
	{
		SpringArmComp->AddWorldOffset(FRotationMatrix(FRotator(0.f, CameraComp->GetComponentRotation().Yaw, 0.f)).GetScaledAxis(EAxis::Y) * AxisValue * GetWorld()->GetDeltaSeconds() * CameraMoveSpeed);
	}
}

void ATBSCharacter::MoveVertical(float AxisValue)
{
	if (AxisValue != 0.f && bCanMoveViewport)
	{
		SpringArmComp->AddWorldOffset(FRotator(0., CameraComp->GetComponentRotation().Yaw, 0.f).Vector() * AxisValue * GetWorld()->GetDeltaSeconds() * CameraMoveSpeed);
	}
}

void ATBSCharacter::ClickedTile()
{
	if (bDisableClickTile) { return; }

	int32 CurrentClickedTileIndex = -1;
	if (!FindCurrentMouseOverTileIndex(CurrentClickedTileIndex)) { return; }
	
	if (!GridManager->FieldLocationArray.IsValidIndex(CurrentClickedTileIndex)) { return; }

	if (CurrentClickedTileIndex == TileIndex) { return; }

	bDisableClickTile = true;
	SelectTilePawnIndex = -1;
	
	if (GridManager->AllTilePawns.Contains(CurrentClickedTileIndex) && GridManager->AllTilePawns[CurrentClickedTileIndex])
	{
		switch (GridManager->AllTilePawns[CurrentClickedTileIndex]->GetTileType())
		{
			case ETBSTileType::Enemy:
			case ETBSTileType::NPC:
			case ETBSTileType::Player:
				SelectTilePawnIndex = CurrentClickedTileIndex;
				break;
		}
	}

	if (!GridPathFinding && GridManager) { GridPathFinding = new FGridPathFinding(GridManager); }

	if (GridPathFinding)
	{
		GridPathFinding->Pathfinding(TileIndex, CurrentClickedTileIndex);

		if (GridPathFinding->bFound)
		{
			if (SelectTilePawnIndex != -1)
			{
				if (GridPathFinding->CanMoveTilesArray[CurrentClickedTileIndex].Cost > 1)
				{
					GridPathFinding->CurrentPathEnd = GridPathFinding->PathIndexArray[1];
					StartMovement();
				}
				else
				{
					EndMovement();
				}
			}
			else
			{
				GridPathFinding->CurrentPathEnd = CurrentClickedTileIndex;
				StartMovement();
			}
			return;
		}
	}

	SelectTilePawnIndex = -1;
	EndMovement();
}

bool ATBSCharacter::FindCurrentMouseOverTileIndex(int32& OutIndex)
{
	bool bHasClickedTile = false;

	APlayerController* OwnerPC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	if (OwnerPC)
	{
		FHitResult HitResult;
		if (OwnerPC->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, false, HitResult))
		{
			OutIndex = GridManager->VectorToIndex(HitResult.Location);
			bHasClickedTile = true;
		}
	}

	return bHasClickedTile;
}


void ATBSCharacter::StartMovement()
{
	TArray<FVector> PathVectorArray;

	for (int32 PathIndex : GridPathFinding->PathIndexArray)
	{
		PathVectorArray.Add(GridManager->GetVectorFromIndexOnGrid(PathIndex, SplineHeight));
	}

	PathVectorArray.Add(GridManager->GetVectorFromIndexOnGrid(GridPathFinding->CurrentStartIndex, SplineHeight));

	MovePathComp->SetSplineWorldPoints(PathVectorArray);

	CurrentSplineDistance = MovePathComp->GetSplineLength();
	bIsMoving = true;
}


void ATBSCharacter::TickMovement(float DeltaSeconds)
{
	int32 PointIndex = SelectTilePawnIndex != -1 ? 1 : 0;

	if (CurrentSplineDistance <= MovePathComp->GetDistanceAlongSplineAtSplinePoint(PointIndex))
	{
		SetActorLocation(GridManager->GetVectorFromIndex(GridPathFinding->CurrentPathEnd));
		EndMovement();
	}
	else
	{
		if (CurrentSpeed <= PawnMaxSpeed)
		{
			CurrentSpeed = CurrentSpeed + PawnMovementSpeedAcceleration;
		}

		
		CurrentSplineDistance = CurrentSplineDistance - GetWorld()->GetDeltaSeconds() * CurrentSpeed * ((GridManager->GetTileBoundsX() + GridManager->GetTileBoundsY()) / 400);

		FVector PathSplieLocation = MovePathComp->GetWorldLocationAtDistanceAlongSpline(CurrentSplineDistance);
		PathSplieLocation.Z -= SplineHeight;

		SetActorLocationAndRotation(PathSplieLocation, FRotator(0.f, MovePathComp->GetWorldRotationAtDistanceAlongSpline(CurrentSplineDistance).Yaw + 180, 0.f));
		
	}
}

void ATBSCharacter::EndMovement()
{
	bIsMoving = false;
	bDisableClickTile = false;
	CurrentSpeed = 0.f;

	GridManager->AllTilePawns.Remove(TileIndex);
	TileIndex = GridPathFinding->CurrentPathEnd;
	GridManager->AllTilePawns.Add(TileIndex, this);

	if (SelectTilePawnIndex != -1 && GridManager->AllTilePawns.Contains(SelectTilePawnIndex) && GridManager->AllTilePawns[SelectTilePawnIndex])
	{
		switch (GridManager->AllTilePawns[SelectTilePawnIndex]->GetTileType())
		{
			case  ETBSTileType::Enemy:
			{
				AEnemyTilePawn* EnemyPawn = Cast<AEnemyTilePawn>(GridManager->AllTilePawns[SelectTilePawnIndex]);
				if (EnemyPawn) { EnemyPawn->FightWith(this); }
				break;
			}
			case ETBSTileType::NPC:
			{
				ANPCTilePawn* NPCPawn = Cast<ANPCTilePawn>(GridManager->AllTilePawns[SelectTilePawnIndex]);
				if (NPCPawn) { NPCPawn->TalkWith(this); }
				break;
			}
			case ETBSTileType::Player:
			{
				break;
			}
		}

		SelectTilePawnIndex = -1;
	}
}