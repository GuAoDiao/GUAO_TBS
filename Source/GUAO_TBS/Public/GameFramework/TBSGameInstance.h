// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TBSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UTBSGameInstance : public UGameInstance
{
	GENERATED_BODY()

	//////////////////////////////////////////////////////////////////////////
	/// Level
public:
	void BackToMenuLevel();


protected:
	void OpenTargetLevel(const FName& InLevelName);

	//////////////////////////////////////////////////////////////////////////
	/// Archive
public:
	TArray<FName> GetAllArchiveNameList() const;

	class UTBSArchiveItem* GetArchiveItemInfo(const FName& InArchiveName) const;
	
	inline FName GetCurrentArchiveName() const { return CurrentArchiveName; }
	inline class UTBSArchiveItem* GetCurrentArchiveItemInfo() const { return GetArchiveItemInfo(CurrentArchiveName); }

protected:
	FString GetActualArchiveName(const FName& InArchiveName) const;

public:
	class UTBSArchiveItem* CreateNewArchive(const FName& InArchiveName, const FString& InPlayerName, const FName& InCharacterName);
	
	void LoadArchive(const FName& InArchiveName);

	bool SaveArchiveItemInfo(const FName& InArchiveName, class UTBSArchiveItem* InArchiveItem) const;
	bool SaveArchiveList(const TArray<FName>& AllArchiveListName) const;

	bool SaveCurrentStatusToArchive();

protected:
	FName CurrentArchiveName;
};
