// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TBSTypes.h"

#include "BasedTile.generated.h"

class AGridManager;

UCLASS()
class GUAO_TBS_API ABasedTile : public AActor
{
	GENERATED_BODY()
	
public:
	ABasedTile();
	
	/// Tile Interface
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Index;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIgnoreSnapToCustomGrid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPlaceActorAtAnchor;
	UPROPERTY(EditDefaultsOnly)
	FGridEdgesCost EdgeCosts;	

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* GridAnchor;

protected:
	UPROPERTY()
	AGridManager* GridManager;
};
