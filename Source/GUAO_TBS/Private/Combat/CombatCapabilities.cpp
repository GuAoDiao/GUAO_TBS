// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatCapabilities.h"




UCombatCapabilities::UCombatCapabilities()
{
	SetFlags(RF_Standalone);
}

void UCombatCapabilities::InitializeCombatCapabilities(UWorld* World, const FString& Info)
{
	CurrentWorld = World;
	ParseStringToInfo(Info);
}

void UCombatCapabilities::UseCombatCapabilities()
{
	OnUseCombatCapabilities();
}
