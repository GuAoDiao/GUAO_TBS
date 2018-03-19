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


	USceneComponent* GetGridAnchor() const { return GridAnchor; }

public:
	UPROPERTY()
	int32 Index;
	ETBSTileType TileType;

	
	UPROPERTY(BlueprintReadOnly)
	float CurrentSpeed;
protected:
	UPROPERTY()
	AGridManager* GridManager;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* GridAnchor;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* PawnSkeletalMeshComp;	
};
