// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "TBSTypes.h"

#include "TilePawn.generated.h"

class AGridManager;

UCLASS()
class GUAO_TBS_API ATilePawn : public APawn
{
	GENERATED_BODY()

public:
	ATilePawn();

	virtual void OnConstruction(const FTransform& Transform) override;
	//////////////////////////////////////////////////////////////////////////
	/// Grid Info
public:
	int32 GetTileIndex() const { return TileIndex; }
	void SetTileIndex(int32 InTileIndex) { TileIndex = InTileIndex; }
	ETBSTileType GetTileType() const { return TileType; }
	USceneComponent* GetGridAnchor() const { return GridAnchor; }
protected:
	UPROPERTY()
	AGridManager* GridManager;
	UPROPERTY()
	int32 TileIndex;

	ETBSTileType TileType;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* GridAnchor;
	
	//////////////////////////////////////////////////////////////////////////
	/// Base Comp
protected:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* PawnSkeletalMeshComp;	


	//////////////////////////////////////////////////////////////////////////
	/// TilePawn
public:
	int32 GetTilePawnID() const { return TilePawnID; }
protected:
	UPROPERTY(EditAnywhere)
	int32 TilePawnID;
	UPROPERTY(EditAnywhere)
	FName TilePawnName;
};
