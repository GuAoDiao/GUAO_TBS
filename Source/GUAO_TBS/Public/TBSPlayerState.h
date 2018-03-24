// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "TBSTypes.h"

#include "TBSPlayerState.generated.h"

class ACombatPawn;
class UGamePropsComponent;


/**
 * 
 */
UCLASS()
class GUAO_TBS_API ATBSPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATBSPlayerState();

	virtual void BeginPlay() override;

	//////////////////////////////////////////////////////////////////////////
	/// Player Combat Pawn
public:
	void InitializePlayerCombatTeam();
	FCombatTeam& GetPlayerCombatTeam() { return PlayerCombatTeam; }

	FCombatTeam PlayerCombatTeam;
	UPROPERTY(EditDefaultsOnly)
	TArray<FString> CombatPawnNameInPlayerTeam;

	UFUNCTION(BlueprintPure)
	int32 GetGold() const { return Gold; }
	UFUNCTION(BlueprintCallable)
	void AddGold(int32 InOffset) { Gold += InOffset; UpdateGold(); }

	UFUNCTION(BlueprintCallable)
	const FString& GetPlayerName() const { return PlayerName; }

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoldUpdateDelegate, int32 /* Gold */)
	FOnGoldUpdateDelegate OnGoldUpdateDelegate;
protected:
	void UpdateGold() { OnGoldUpdateDelegate.Broadcast(Gold); UE_LOG(LogTemp, Log, TEXT("-_- Gold : %d"), Gold); }

public:
	UGamePropsComponent* GetGamePropsComponent() const { return GamePropsComponent; }
protected:
	UPROPERTY()
	UGamePropsComponent* GamePropsComponent;
	int32 Gold;
	FString PlayerName;
};
