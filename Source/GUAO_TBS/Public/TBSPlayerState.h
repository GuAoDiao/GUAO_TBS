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
	TArray<int32> CombatPawnIDInPlayerTeam;

	UFUNCTION(BlueprintCallable)
	const FString& GetPlayerUserName() const { return PlayerUserName; }

	//////////////////////////////////////////////////////////////////////////
	/// Gold
public:
	UFUNCTION(BlueprintPure)
	int32 GetGold() const { return Gold; }
	UFUNCTION(BlueprintCallable)
	void AddGold(int32 InOffset) { Gold += InOffset; UpdateGold(); }


	DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoldUpdateDelegate, int32 /* Gold */)
	FOnGoldUpdateDelegate OnGoldUpdateDelegate;
protected:
	void UpdateGold() { OnGoldUpdateDelegate.Broadcast(Gold); UE_LOG(LogTemp, Log, TEXT("-_- Gold : %d"), Gold); }
	
	//////////////////////////////////////////////////////////////////////////
	/// Level And Experience
public:
	UFUNCTION(BlueprintCallable)
	int32 GetLevel() const { return Level; }
	UFUNCTION(BlueprintCallable)
	int32 GetExperience() const { return Experience; }
	UFUNCTION(BlueprintCallable)
	int32 GetMaxExperience() const { return MaxExperience; }

	UFUNCTION(BlueprintCallable)
	void AddExperience(int32 InOffset);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExperienceUpdateDelegate, int32 /* Experience */, int32 /* MaxExperience */)
	FOnExperienceUpdateDelegate OnExperienceUpdateDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int32 /* Level */)
	FOnLevelUpDelegate OnLevelUpDelegate;
protected:
	int32 Gold;
	int32 Level;
	int32 MaxLevel;
	int32 Experience;
	int32 MaxExperience;
	FString PlayerUserName;
};
