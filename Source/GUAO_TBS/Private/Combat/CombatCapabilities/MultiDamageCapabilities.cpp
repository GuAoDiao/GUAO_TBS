// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiDamageCapabilities.h"

#include "Combat/CombatPawn.h"



void UMultiDamageCapabilities::SetOwnerAndAttackTarget(ACombatPawn* InOwnerPawn, const TArray<ACombatPawn*>& InAttackTarget)
{
	OwnerPawn = InOwnerPawn;
	AttackTarget = InAttackTarget;
}

void UMultiDamageCapabilities::ParseStringToInfo(const FString& Info)
{
	DamagePercent = FCString::Atof(*Info);
}

void UMultiDamageCapabilities::OnUseCombatCapabilities()
{
	if (OwnerPawn)
	{
		for (ACombatPawn* TargetPawn : AttackTarget)
		{
			if (TargetPawn)
			{
				float Damage = (OwnerPawn->Attack - TargetPawn->Defence) * DamagePercent;

				float Luck = OwnerPawn->Luck - TargetPawn->Luck;
				if (FMath::RandRange(0.f, 1000.f) / 10.f < Luck)
				{
					Damage *= 2.f;
					UE_LOG(LogTemp, Warning, TEXT("-_- good luck, critical attack"));
				}

				TargetPawn->AcceptDamage(Damage, OwnerPawn);
			}
		}
	}
}

