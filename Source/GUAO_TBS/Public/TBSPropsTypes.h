// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SubclassOf.h"

#include "TBSPropsTypes.generated.h"

UENUM(BlueprintType)
enum class EGamePropsType : uint8
{
	Consumables  UMETA(DisplayName = "Consumables"),
	Equipment UMETA(DisplayName = "Equipment"),
	Materials UMETA(DisplayName = "Materials"),
	Quest UMETA(DisplayName = "Quest")
};

UENUM(BlueprintType)
enum class EGameCapabilitiesType : uint8
{
	MoneyOffset,
	MoneyRandomOffset,
	ExperienceOffset
};

UENUM(BlueprintType)
enum class ECombatCapabilitiesType : uint8
{
	MonomerDamage,
	MultiDamage,
	MonomerCure,
	MultiCure
};

UENUM(BlueprintType)
enum class FEquipmentType :uint8
{
	Weapon,
	Armor,
	Decorations,
};

USTRUCT(BlueprintType)
struct FGamePropsInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	static const FGamePropsInfo EmptyProps;

	FGamePropsInfo() : ID(-1), Type(EGamePropsType::Consumables), Icon(nullptr) {}

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Name;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EGamePropsType Type;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Description;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UTexture2D* Icon;
};

USTRUCT(BlueprintType)
struct FEquipmentInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FEquipmentType Type;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Health;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Mana;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Attack;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Defence;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Luck;
};

UENUM(BlueprintType)
enum class EConsumablesType : uint8
{
	Common,
	Combat
};

USTRUCT(BlueprintType)
struct FConsumablesPropsInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	static const FConsumablesPropsInfo EmptyConsumablesProps;

	FConsumablesPropsInfo() : ID(-1), Type(EConsumablesType::Common){}

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 ID;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EConsumablesType Type;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<ECombatCapabilitiesType, FString> CombatCapabilities;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<EGameCapabilitiesType, FString> GameCapabilities;
};


USTRUCT(BlueprintType)
struct FPropsStoreInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FPropsStoreInfo() : ID(-1), Nums(0) {}

	UPROPERTY(BlueprintReadOnly)
	int32 ID;
	UPROPERTY(BlueprintReadOnly)
	int32 Nums;
};

USTRUCT(BlueprintType)
struct FGameCapabilitiesClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EGameCapabilitiesType Type;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UGameCapabilities> ClassInfo;
};

USTRUCT(BlueprintType)
struct FCombatCapabilitiesClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ECombatCapabilitiesType Type;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UCombatCapabilities> ClassInfo;
};