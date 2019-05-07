// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TBSTypes.h"

#include "GridManager.generated.h"

class FGridPathFinding;
class ATilePawn;

UCLASS()
class GUAO_TBS_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	AGridManager();

	//////////////////////////////////////////////////////////////////////////
	/// Grid Manager Base
public:
	int32 VectorToIndex(const FVector& Location) const;
	FVector GetVectorFromIndex(int32 Index) const;
	FVector GetVectorFromIndexOnGrid(int32 Index, float ZOffset) const;
	virtual FVector CreateVectorFromIndex(int32 Index) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bSnapToCustomGrid;


	//////////////////////////////////////////////////////////////////////////
	/// Construct
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	void ScaleAndPositionCollisionPlaen();


	UPROPERTY(EditDefaultsOnly)
	int32 GridSizeX;
	UPROPERTY(EditDefaultsOnly)
	int32 GridSizeY;
	UPROPERTY()
	float TileBoundsX;
	UPROPERTY()
	float TileBoundsY;
	UPROPERTY()
	float NodeGapY;
	float HeightImpassableCutoff;
	float bAutoCalculateCostsBaseOnHeight;

	UPROPERTY(EditDefaultsOnly)
	bool bShowDefaultTile;

	UPROPERTY(EditDefaultsOnly)
	bool bShowCollisionPlane;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> FieldLocationArray;

protected:
	void InitializeGridEdgeArray();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bPregenerateGameplayGrids;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bCollisionPlaneWalkable;

	//////////////////////////////////////////////////////////////////////////
	/// Initialize 
public:
	virtual void BeginPlay() override;

	void AddViewportTerrainToArrays();
	void AddAllTilePawnToArrays();

	int32 GetMaxValueWhenAllNotZero(int32 FirstValue, int32 SecondValue);

	void SetEdgesOfTiles();
	void ScaleRelativeToDefaultTile(UStaticMeshComponent* InStaticMeshComp);
	
public:
	UPROPERTY()
	TArray<FGridEdgesCost> GridEdgeArray;
	UPROPERTY()
	TMap<int32, ATilePawn*> AllTilePawns;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UInstancedStaticMeshComponent* DefaultInstanceTileComp;
	class UStaticMeshComponent* CollisionPlaneComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMesh* DefaultGridMesh;

public:
	float GetTileBoundsX() { return TileBoundsX; }
	float GetTileBoundsY() { return TileBoundsY; }
};
