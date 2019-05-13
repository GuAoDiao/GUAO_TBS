// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Templates/SubclassOf.h"

#include "GameFramework/TBSTypes.h"

#include "TBSAssetTypes.generated.h"

USTRUCT(BlueprintType)
struct FTBSWidgetDTInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName WidgetName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<class UUserWidget> WidgetClass;
};

USTRUCT(BlueprintType)
struct FTBSLevelDTInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName LevelName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName LevelFullPath;
};

USTRUCT(BlueprintType)
struct FTBSCharacterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName CharacterName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<class USkeletalMesh> CharacterMesh;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<class UAnimInstance> CharacterAnimInstance;
};