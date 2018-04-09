// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPawn.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "WidgetComponent.h"
#include "GameFramework/PlayerController.h"

#include "Combat/DecisionMakers/AutoDecisionMaker.h"
#include "Combat/Actions/ICombatAction.h"
#include "Combat/CombatManager.h"
#include "Combat/CombatPawnInfoDisplay.h"
#include "Combat/CombatPawnManager.h"
#include "TBSCharacter.h"

ACombatPawn::ACombatPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	CombatPawnInfoDisplayComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComp"));
	CombatPawnInfoDisplayComp->SetDrawSize(FVector2D(100.f, 60.f));
	CombatPawnInfoDisplayComp->SetupAttachment(GetRootComponent());
	CombatPawnInfoDisplayComp->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	CombatPawnInfoDisplayClass = LoadClass<UCombatPawnInfoDisplay>(this, TEXT("WidgetBlueprint'/Game/GUAO_TBS/Blueprints/Combat/W_CombatPawnDisplayInfo.W_CombatPawnDisplayInfo_C'"));

	AutoPossessAI = EAutoPossessAI::Disabled;

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

	if (!CombatPawnName.IsEmpty()) { SetCombatPawnName(CombatPawnName); }
}

void ACombatPawn::SetCombatPawnName(const FString& InCombatPawnName)
{
	CombatPawnName = InCombatPawnName;

	if (!CombatPawnName.IsEmpty())
	{
		FCombatPawnManager* CombatPawnManager = FCombatPawnManager::GetInstance();
		CombatPawnManager->GetBaseCombatDisplayInfo(CombatPawnName, BaseDisplayInfo);
		if (BaseDisplayInfo.SkeletalMesh)
		{
			SkeletalMeshComp->SetSkeletalMesh(BaseDisplayInfo.SkeletalMesh);
			SkeletalMeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
			SkeletalMeshComp->SetRelativeScale3D(BaseDisplayInfo.SkeletalMeshScale);
			if (BaseDisplayInfo.IdleAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.IdleAnimAsset, true); }
		}

		if (CombatPawnManager->GetBaseCombatPawnFightInfo(CombatPawnName, BaseFightInfo)) { InitializeCombatPawnAttribute(); }
	}
	
	ResetPawnState();
}

void ACombatPawn::BeginPlay()
{
	Super::BeginPlay();

	if (CombatPawnInfoDisplayClass)
	{
		CombatPawnInfoDisplayComp->SetWidgetClass(CombatPawnInfoDisplayClass);
		CombatPawnInfoDisplayComp->SetWidgetSpace(EWidgetSpace::Screen);
		
		CombatPawnInfoDisplay = Cast<UCombatPawnInfoDisplay>(CombatPawnInfoDisplayComp->GetUserWidgetObject());
		if (CombatPawnInfoDisplay)
		{
			CombatPawnInfoDisplay->InitializeCombatPawnInfoDisplay(Level, CombatPawnName, MaxHealth, MaxMana);
		}
	}
}

void ACombatPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//////////////////////////////////////////////////////////////////////////
/// Attribute
void ACombatPawn::InitializeCombatPawnAttribute()
{
	Level = BaseFightInfo.Level;
	MaxHealth = BaseFightInfo.MHP;
	MaxMana = BaseFightInfo.MMP;
	Attack = BaseFightInfo.Attack;
	Defence = BaseFightInfo.Defence;
	Luck = BaseFightInfo.Luck;

	if (CombatPawnInfoDisplay)
	{
		CombatPawnInfoDisplay->InitializeCombatPawnInfoDisplay(Level, CombatPawnName, MaxHealth, MaxMana);
	}
}
void ACombatPawn::ResetPawnState()
{
	Health = MaxHealth;
	Mana = MaxMana;
	bIsDead = false;
	UpdateHealth();
	ToggleToTargetCombatPawnState(ECombatPawnState::Idle);
}

//////////////////////////////////////////////////////////////////////////
/// Combat Info
void ACombatPawn::BeginMakeDecision()
{
	ToggleToTargetCombatPawnState(ECombatPawnState::ReadFight);

	MakeDecisionImplementation();
}

void ACombatPawn::MakeDecisionImplementation()
{
	DecisionMaker = new FAutoDecisionMaker();
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

			ToggleToTargetCombatPawnState(ECombatPawnState::Idle);

			return true;
		}
		return false;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
/// Damage , Health, Death;
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
	if (CombatPawnInfoDisplay) { CombatPawnInfoDisplay->UpdateHealthBarPercent(Health, MaxHealth); }
}


void ACombatPawn::OnDeath()
{
	bIsDead = true;
	
	OnCombatPawnDeathDelegate.Broadcast();

	ToggleToTargetCombatPawnState(ECombatPawnState::OnDeath);
}

//////////////////////////////////////////////////////////////////////////
/// Toggle Combat Pawn State And Update Pawn Display
void ACombatPawn::ToggleToTargetCombatPawnState(ECombatPawnState::Type TargetCombatPawnState)
{
	CurrentCombatPawnState = TargetCombatPawnState;

	switch (CurrentCombatPawnState)
	{	
		case ECombatPawnState::Idle:
			ToggleToIdleState();
			break;
		case ECombatPawnState::ReadFight:
			ToggleToReadFightState();
			break;
		case ECombatPawnState::Run:
			ToggleToRunState();
			break;
		case ECombatPawnState::Attack:
			ToggleToAttackState();
			break;
		case ECombatPawnState::BeHit:
			ToggleToBeHitState();
			break;
		case ECombatPawnState::Death:
			ToggleToDeathState();
			break;
		case ECombatPawnState::OnDeath:
			ToggleToOnDeathState();
			break;
	}

	if (CombatPawnInfoDisplayComp)
	{
		CombatPawnInfoDisplayComp->SetVisibility(
			CurrentCombatPawnState == ECombatPawnState::Idle || CurrentCombatPawnState == ECombatPawnState::BeHit ||
			CurrentCombatPawnState == ECombatPawnState::Death || CurrentCombatPawnState == ECombatPawnState::OnDeath
		);
	}
}


void ACombatPawn::ToggleToIdleState() { if (BaseDisplayInfo.IdleAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.IdleAnimAsset, true); } }
void ACombatPawn::ToggleToReadFightState() { if (BaseDisplayInfo.RunAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.ReadFightAnimAsset, true); } }
void ACombatPawn::ToggleToRunState() { if (BaseDisplayInfo.RunAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.RunAnimAsset, true); } }
void ACombatPawn::ToggleToAttackState() { if (BaseDisplayInfo.AttackAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.AttackAnimAsset, false); } }
void ACombatPawn::ToggleToDeathState() { if (BaseDisplayInfo.DeathAnimAsset) { SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.DeathAnimAsset, false); } }

void ACombatPawn::ToggleToBeHitState()
{
	if (BaseDisplayInfo.AccpetDamageAnimAsset)
	{
		SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.AccpetDamageAnimAsset, false);

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(DelayToSetIdleStateTimer, this, &ACombatPawn::DelayToSetIdleState, BaseDisplayInfo.AccpetDamageAnimAsset->GetMaxCurrentTime(), false);
		}
	}
}

void ACombatPawn::ToggleToOnDeathState()
{
	if (BaseDisplayInfo.OnDeathAnimAsset)
	{
		SkeletalMeshComp->PlayAnimation(BaseDisplayInfo.OnDeathAnimAsset, false);
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(DelayToSetDeathStateTimer, this, &ACombatPawn::DelayToSetDeathState, BaseDisplayInfo.OnDeathAnimAsset->GetMaxCurrentTime(), false);
		}
	}
}

void ACombatPawn::DelayToSetIdleState() { ToggleToTargetCombatPawnState(ECombatPawnState::Idle); }
void ACombatPawn::DelayToSetDeathState() { ToggleToTargetCombatPawnState(ECombatPawnState::Death); }
