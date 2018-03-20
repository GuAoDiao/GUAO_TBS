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

	Attack = 20.f;
	Defence = 10.f;
	MaxHealth = 100.f;

	PrimaryActorTick.bCanEverTick = true;
}

void ACombatPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Health = MaxHealth;

	if (!CombatPawnName.IsEmpty())
	{
		FCombatPawnManager::GetCombatPawnManagerInstance()->GetBaseAnimationFromName(CombatPawnName, BaseAnimation);
	}
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
	else if (SkeletalMeshComp && BaseAnimation.AccpetDamageAnimAsset)
	{
		SkeletalMeshComp->PlayAnimation(BaseAnimation.AccpetDamageAnimAsset, false);
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

	if (SkeletalMeshComp && BaseAnimation.OnDeathAnimAsset)
	{
		SkeletalMeshComp->PlayAnimation(BaseAnimation.OnDeathAnimAsset, false);
		if (GetWorld() && BaseAnimation.DeathAnimAsset)
		{
			GetWorld()->GetTimerManager().SetTimer(DelayToSetDeathPositionTimer, this, &ACombatPawn::DelayToSetDeathPosition, BaseAnimation.OnDeathAnimAsset->GetMaxCurrentTime(), false);
		}
	}
}


void ACombatPawn::DelayToSetDeathPosition() { if (SkeletalMeshComp && BaseAnimation.DeathAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseAnimation.DeathAnimAsset, false); } }
void ACombatPawn::BeginAttackAnimation() { if (SkeletalMeshComp && BaseAnimation.AttackAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseAnimation.AttackAnimAsset, false); } }

void ACombatPawn::BeginRunAnimation() { if (SkeletalMeshComp && BaseAnimation.RunAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseAnimation.RunAnimAsset, true); } }
void ACombatPawn::BeginIdleAnimation() { if (SkeletalMeshComp && BaseAnimation.IdleAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseAnimation.IdleAnimAsset, true); } }