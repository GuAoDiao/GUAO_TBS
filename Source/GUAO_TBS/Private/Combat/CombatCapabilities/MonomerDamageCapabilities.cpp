// Fill out your copyright notice in the Description page of Project Settings.

#include "MonomerDamageCapabilities.h"

#include "Combat/CombatPawn.h"



void UMonomerDamageCapabilities::SetOwnerAndAttackTarget(ACombatPawn* InOwnerPawn, ACombatPawn* InAttackTarget)
{
	OwnerPawn = InOwnerPawn;
	AttackTarget = InAttackTarget;
}

void UMonomerDamageCapabilities::ParseStringToInfo(const FString& Info)
{
	DamagePercent = FCString::Atof(*Info);
}

void UMonomerDamageCapabilities::OnUseCombatCapabilities()
{
	if (OwnerPawn && AttackTarget)
	{
		float Damage = (OwnerPawn->Attack - AttackTarget->Defence) * DamagePercent;

		float Luck = OwnerPawn->Luck - AttackTarget->Luck;
		if (FMath::RandRange(0.f, 1000.f) / 10.f < Luck)
		{
			Damage *= 2.f;
			UE_LOG(LogTemp, Warning, TEXT("-_- good luck, critical attack"));
		}

		AttackTarget->AcceptDamage(Damage, OwnerPawn);
	}
}
