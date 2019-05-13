// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuLayoutWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUAO_TBS_API UMenuLayoutWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void InitializeMenuLayoutWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ReflectionStyleWidget();

	void SetDisplayWidget(class UWidget* InWidget, bool bDisplay);
	UUserWidget* CreateWidgetFromName(const FName& InWidgetName);

protected:
	UPROPERTY(BlueprintReadWrite)
	class UCanvasPanel* RootCanvas;

	//////////////////////////////////////////////////////////////////////////
	/// MainMenu
public:
	void SetDisplayMainMenu(bool bDisplay);

public:
	TWeakObjectPtr<class UMainMenuWidget> GetMainMenuWidget() const { return MainMenuWidget; }
protected:
	TWeakObjectPtr<class UMainMenuWidget> MainMenuWidget;

	//////////////////////////////////////////////////////////////////////////
	/// SettingMenu
public:
	void SetDisplaySettingMenu(bool bDisplay);

public:
	TWeakObjectPtr<class USettingMenuWidget> GetSettingMenuWidget() const { return SettingMenuWidget; }
protected:
	TWeakObjectPtr<class USettingMenuWidget> SettingMenuWidget;

	//////////////////////////////////////////////////////////////////////////
	/// ArchiveMenu
public:
	void SetDisplayArchiveMenu(bool bDisplay);

public:
	TWeakObjectPtr<class UArchiveMenuWidget> GetArchiveMenuWidget() const { return ArchiveMenuWidget; }
protected:
	TWeakObjectPtr<class UArchiveMenuWidget> ArchiveMenuWidget;
};