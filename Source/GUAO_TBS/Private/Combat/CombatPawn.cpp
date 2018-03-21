// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawn.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "WidgetComponent.h"
#include "GameFramework/PlayerController.h"

#include "Combat/DecisionMakers/TestDecisionMaker.h"
#include "Combat/Actions/ICombatAction.h"
#include "Combat/CombatManager.h"
#include "Combat/CombatPawnHealthBar.h"
#include "Combat/CombatPawnManager.h"
#include "TBSCharacter.h"

ACombatPawn::ACombatPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	HealthBarComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComp"));
	HealthBarComp->SetupAttachment(GetRootComponent());
	HealthBarComp->SetRelativeLocation(FVector(0.f, 0.f, 140.f));

	bIsDead = false;

	Level = 1;
	MaxHealth = 50.f;
	MaxMana = 50.f;
	Attack = 15.f;
	Defence = 5.f;
	Luck = 0.f;

	PrimaryActorTick.bCanEverTick = true;
}

void ACombatPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


	if (!CombatPawnName.IsEmpty())
	{
		FCombatPawnManager* CombatPawnManager = FCombatPawnManager::GetCombatPawnManagerInstance();
		CombatPawnManager->GetBaseCombatDisplayInfo(CombatPawnName, BaseDisplayInfo);
		if (BaseDisplayInfo.SkeletalMesh) { SkeletalMeshComp->SetSkeletalMesh(BaseDisplayInfo.SkeletalMesh); }

		if (CombatPawnManager->GetBaseCombatPawnFightInfo(CombatPawnName, BaseFightInfo))
		{
			Level = BaseFightInfo.Level;
			MaxHealth = BaseFightInfo.MHP;
			MaxMana = BaseFightInfo.MMP;
			Attack = BaseFightInfo.Attack;
			Defence = BaseFightInfo.Defence;
			Luck = BaseFightInfo.Luck;
		}
	}
	
	Health = MaxHealth;
	Mana = MaxMana;
}

void ACombatPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarClass)
	{
		HealthBarComp->SetWidgetClass(HealthBarClass);
		HealthBarComp->SetWidgetSpace(EWidgetSpace::Screen);
		HealthBarComp->SetDrawSize(FVector2D(100.f, 20.f));
		
		HealthBar = Cast<UCombatPawnHealthBar>(HealthBarComp->GetUserWidgetObject());
		if (HealthBar) { HealthBar->UpdateHealthBarPercent(Health, MaxHealth); }
	}
}

void ACombatPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	if (HealthBarComp && HealthBarClass)
	{
		APlayerController* OwnerPC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
		if (OwnerPC)
		{
			FVector Location;
			FRotator Rotation;
			OwnerPC->GetPlayerViewPoint(Location, Rotation);
			HealthBarComp->SetWorldRotation(FRotationMatrix::MakeFromX(Location - HealthBarComp->GetComponentLocation()).Rotator());
		}
	}
	*/
}

void ACombatPawn::BeginMakeDecision()
{
	DecisionMaker = new FTestDecisionMaker();
	if (DecisionMaker) { DecisionMaker->BeginMakeDecision(this); }
}

bool ACombatPawn::MakeDecision(float DeltaSeconds)
{
	if (DecisionMaker)
	{
		if (DecisionMaker->MakeDecision(DeltaSeconds))
		{
			delete DecisionMaker;
			DecisionMaker = nullptr;
			return true;
		}
		return false;
	}
	return true;
}

void ACombatPawn::BeginExecuteAction()
{
	if (CombatAction) { CombatAction->BeginExecuteAction(this); }
}

bool ACombatPawn::ExecuteAction(float DeltaSeconds)
{
	if (CombatAction)
	{
		if (CombatAction->ExecuteAction(DeltaSeconds))
		{
			delete CombatAction;
			CombatAction = nullptr;
			return true;
		}
		return false;
	}
	return false;
}



void ACombatPawn::AcceptDamage(float Damage, ACombatPawn* Causer)
{
	if (Damage < 0.f) { Damage = 0.f; }

	if (Damage == 0.f) { return; }

	Health -= Damage;

	if (Health < 0.f) { Health = 0.f; }

	UpdateHealth();

	if (Health == 0.f)
	{
		OnDeath();
	}
	else if (SkeletalMeshComp && BaseDisplayInfo.AccpetDamageAnimAsset)
	{
		SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.AccpetDamageAnimAsset, false);
	}
}

void ACombatPawn::UpdateHealth()
{
	if (HealthBar) { HealthBar->UpdateHealthBarPercent(Health, MaxHealth); }
}
void ACombatPawn::ResetPawnState()
{
	Health = MaxHealth;
	UpdateHealth();
}

void ACombatPawn::OnDeath()
{
	bIsDead = true;
	
	OnCombatPawnDeathDelegate.Broadcast();

	if (SkeletalMeshComp && BaseDisplayInfo.OnDeathAnimAsset)
	{
		SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.OnDeathAnimAsset, false);
		if (GetWorld() && BaseDisplayInfo.DeathAnimAsset)
		{
			GetWorld()->GetTimerManager().SetTimer(DelayToSetDeathPositionTimer, this, &ACombatPawn::DelayToSetDeathPosition, BaseDisplayInfo.OnDeathAnimAsset->GetMaxCurrentTime(), false);
		}
	}
}


void ACombatPawn::DelayToSetDeathPosition() { if (SkeletalMeshComp && BaseDisplayInfo.DeathAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.DeathAnimAsset, false); } }
void ACombatPawn::BeginAttackAnimation() { if (SkeletalMeshComp && BaseDisplayInfo.AttackAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.AttackAnimAsset, false); } }

void ACombatPawn::BeginRunAnimation() { if (SkeletalMeshComp && BaseDisplayInfo.RunAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.RunAnimAsset, true); } }
void ACombatPawn::BeginIdleAnimation() { if (SkeletalMeshComp && BaseDisplayInfo.IdleAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.IdleAnimAsset, true); } }