// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TBSTypes.h"
#include "TBSAssetTypes.h"
#include "TBSPropsAndCapabilitiesTypes.h"

#include "TBSGameAssetManager.generated.h"

USTRUCT(BlueprintType)
struct FTBSGameDTInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DTName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UDataTable* DataTable;
};

/**
 * 
 */
class GUAO_TBS_API FTBSGameAssetManager
{	
protected:
	FTBSGameAssetManager();
	static FTBSGameAssetManager* TBSGameAssetManagerInstance;
public:
	static FTBSGameAssetManager* GetInstance();


	//////////////////////////////////////////////////////////////////////////
	/// DataTable Info 所有数据库的基础信息
public:
	void LoadAllDataTable();

	class UDataTable* GetTargetDataTable(const FName& InDTName) const;

protected:
	UPROPERTY()
	class UDataTable* DTInfoDT;
	UPROPERTY()
	TMap<FName, UDataTable*> AllDTInfo;

	//////////////////////////////////////////////////////////////////////////
	/// Level
public:
	FName GetLevelFullPath(const FName& InLevelName) const;

	//////////////////////////////////////////////////////////////////////////
	/// Widget
public:
	TSubclassOf<class UUserWidget> GetWidgetClass(const FName& InWidgetName) const;

	//////////////////////////////////////////////////////////////////////////
	/// Character Info
public:
	const FTBSCharacterInfo* GetCharacterInfo(const FName& InCharacterName) const;
	TArray<FName> GetAllCharacterName() const;

	//////////////////////////////////////////////////////////////////////////
	/// _Dialogue
public:
	void LoadAllDialogueClassInfo();
	const FDialogueInfo* GetDialogueInfo(int32 DialogueID) const;
	const FDialogueChoiceInfo* GetDialogueChoiceInfo(int32 DialogueID) const;
	const FDialogueTaskInfo* GetDialogueTaskInfo(int32 DialogueID) const;
	TSubclassOf<class UDialogueWidget> GetDialogueClass(EDialogueType DialogueType);
protected:
	TMap<EDialogueType, FDialogueClassInfo> AllDialogueClassInfo;

	//////////////////////////////////////////////////////////////////////////
	/// Game Task
public:
	const FGameTaskInfo* GetGameTaskInfo(int32 GameTaskID) const;
	const FGameKillTaskInfo* GetGameKillTaskInfo(int32 GameTaskID) const;
	const FGameCollectionTaskInfo* GetGameCollectionTaskInfo(int32 GameTaskID) const;
	const FGameTaskAcceptableConditions* GetGameTaskAcceptableConditions(int32 GameTaskID) const;


	//////////////////////////////////////////////////////////////////////////
	/// Combat Pawn Info
public:
	bool GetBaseCombatDisplayInfo(int32 InCombatPawnID, FBaseCombatPawnDisplayInfo& OutBaseCombatDisplayInfo);
	TSubclassOf<ACombatPawn> GetCombatPawnClassFromID(int32 InCombatPawnID);
	bool GetBaseCombatPawnFightInfo(int32 InCombatPawnID, FBaseCombatPawnFightInfo& OutBaseCombatPawnDisplayInfo);

	//////////////////////////////////////////////////////////////////////////
	/// Tile Pawn Info 
public:
	const FTilePawnInfo* GetTilePawnInfo(int32 ID) const;

	//////////////////////////////////////////////////////////////////////////
	/// Props
public:
	const FGamePropsInfo& GetPropsInfoFormID(int32 PropsID);
	const FConsumablesPropsInfo& GetConsumablesPropsInfoFormID(int32 PropsID);
	
protected:
	TMap<int32, FGamePropsInfo> AllGamePropsInfo;
	TMap<int32, FConsumablesPropsInfo> AllConsumablesPropsInfo;

	//////////////////////////////////////////////////////////////////////////
	/// Props Shop
public:
	const FPropsShopInfo& GetShopInfo(int32 InShopNPCID) const;

	//////////////////////////////////////////////////////////////////////////
	/// Capabilities
public:
	void InitializeCapabilities();

	UCombatCapabilities* GetCombatCapabilities(ECombatCapabilitiesType InConsumablesType) const;
	UGameCapabilities* GetGameCapabilities(EGameCapabilitiesType InGameCapabilitiesType) const;

protected:
	UPROPERTY()
	TMap<ECombatCapabilitiesType, UCombatCapabilities*> AllCombatCapabilities;
	UPROPERTY()
	TMap<EGameCapabilitiesType, UGameCapabilities*> AllGameCapabilities;
};
