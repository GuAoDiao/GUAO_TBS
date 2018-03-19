// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawn.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "WidgetComponent.h"

#include "Combat/DecisionMakers/TestDecisionMaker.h"
#include "Combat/Actions/ICombatAction.h"
#include "Combat/CombatManager.h"
#include "Combat/CombatPawnHealthBar.h"

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
}

void ACombatPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Health = MaxHealth;
}

void ACombatPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarClass)
	{
		HealthBarComp->SetWidgetClass(HealthBarClass);
		HealthBarComp->SetWidgetSpace(EWidgetSpace::Screen);
		HealthBarComp->SetDrawSize(FVector2D(100.f, 20.f));
	}
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
	else if (SkeletalMeshComp && AccpetDamageAnimSequence)
	{
		SkeletalMeshComp->PlayAnimation(AccpetDamageAnimSequence, false);
	}

	if (Causer)
	{
		UE_LOG(LogTemp, Log, TEXT("-_- %s causer %f damage to %s"), *Causer->CombatPawnName, Damage, *CombatPawnName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("-_- %s accept %f damage"), *CombatPawnName, Damage);
	}
}

void ACombatPawn::UpdateHealth()
{
	UCombatPawnHealthBar* HealthBar = Cast<UCombatPawnHealthBar>(HealthBarComp->GetUserWidgetObject());
	if (HealthBar) { HealthBar->UpdateHealthBarPercent(Health, MaxHealth); }
}

void ACombatPawn::OnDeath()
{
	bIsDead = true;

	UE_LOG(LogTemp, Log, TEXT("-_- %s is death"), *CombatPawnName);

	OnCombatPawnDeathDelegate.Broadcast();

	if (SkeletalMeshComp && OnDeathAnimSequence)
	{
		SkeletalMeshComp->PlayAnimation(OnDeathAnimSequence, false);
		if (GetWorld() && DeathAnimSequence)
		{
			GetWorld()->GetTimerManager().SetTimer(DelayToSetDeathPositionTimer, this, &ACombatPawn::DelayToSetDeathPosition, OnDeathAnimSequence->GetMaxCurrentTime(), false);
		}
	}
}


void ACombatPawn::DelayToSetDeathPosition() { if (SkeletalMeshComp && DeathAnimSequence) { SkeletalMeshComp->PlayAnimation(DeathAnimSequence, false); } }
void ACombatPawn::BeginAttackAnimation() { if (SkeletalMeshComp && AttackAnimSequence) { SkeletalMeshComp->PlayAnimation(AttackAnimSequence, false); } }

void ACombatPawn::BeginRunAnimation() { if (SkeletalMeshComp && RunAnimSequence) { SkeletalMeshComp->PlayAnimation(RunAnimSequence, true); } }
void ACombatPawn::BeginIdleAnimation() { if (SkeletalMeshComp && IdleAnimSequence) { SkeletalMeshComp->PlayAnimation(IdleAnimSequence, true); } }