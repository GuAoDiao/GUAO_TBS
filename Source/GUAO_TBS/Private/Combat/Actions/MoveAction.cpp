// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveAction.h"

#include "Combat/CombatPawn.h"

FMoveAction::FMoveAction(const FVector& InTargetLocation)
{
	TargetLocation = InTargetLocation;
	MoveSpeed = 5.f;
}

void FMoveAction::BeginExecuteAction(class ACombatPawn* Character)
{
	OwnerCombatPawn = Character;
	if (OwnerCombatPawn)
	{			
		OwnerCombatPawn->SetActorRotation(FRotationMatrix::MakeFromX(TargetLocation - OwnerCombatPawn->GetActorLocation()).Rotator());
		OwnerCombatPawn->BeginRunAnimation();
		MoveDirection = (TargetLocation - OwnerCombatPawn->GetActorLocation()).GetSafeNormal();
	}
}

bool FMoveAction::ExecuteAction(float DeltaSeconds)
{
	if (OwnerCombatPawn)
	{
		FVector CurrentLocation = OwnerCombatPawn->GetActorLocation();
		if ((TargetLocation - CurrentLocation).Size() < 10.f)
		{
			OwnerCombatPawn->SetActorLocation(TargetLocation);

			return true;
		}
		else
		{
			OwnerCombatPawn->AddActorWorldOffset(MoveDirection * MoveSpeed);
		}
	}


	return false;
}