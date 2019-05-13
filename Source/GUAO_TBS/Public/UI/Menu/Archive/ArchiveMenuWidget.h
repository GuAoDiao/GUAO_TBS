// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/MenuBaseWidget.h"
#include "ArchiveMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UArchiveMenuWidget : public UMenuBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ReflectionStyleWidget();

	void InitializeArchiveMenuWidget();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAllCharacterNameCanSelect(const TArray<FName>& InAllCharacterName);

	//////////////////////////////////////////////////////////////////////////
	/// Button Clicked
public:
	UFUNCTION(BlueprintCallable)
	void OnCreateNewArchiveButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();

	//////////////////////////////////////////////////////////////////////////
	/// Style Widget
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowCreateNewArchiveWidget();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowArchiveListWidget();

protected:
	UPROPERTY(BlueprintReadWrite)
	class UVerticalBox* AllArchiveItemVerticalBox;

	//////////////////////////////////////////////////////////////////////////
	/// Archive Item Widget

public:
	void AddArchiveItemWidget(class UTBSArchiveItem* InTBSArchiveItem);
	void RemoveArchiveItemWidget(const FName& InArchiveName);

	UFUNCTION(BlueprintCallable)
	void CreateNewArchive(const FName& InArchiveName, const FString& InPlayerName, const FName& InCharacterName);

protected:
	TArray<FName> AllArchiveNameList;

	UPROPERTY()
	TMap<FName, class UArchiveItemWidget*> AllArchiveItemWidget;
};
