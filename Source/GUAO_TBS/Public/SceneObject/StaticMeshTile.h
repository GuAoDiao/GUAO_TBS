// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneObject/BasedTile.h"
#include "StaticMeshTile.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API AStaticMeshTile : public ABasedTile
{
	GENERATED_BODY()
	
public:
	AStaticMeshTile();
	
protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComp;
};
