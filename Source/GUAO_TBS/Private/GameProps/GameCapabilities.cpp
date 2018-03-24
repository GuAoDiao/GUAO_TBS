// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCapabilities.h"

UGameCapabilities::UGameCapabilities()
{
	SetFlags(RF_Standalone);
}

void UGameCapabilities::InitializeGameCapabilities(UWorld* World, const FString& Info)
{
	CurrentWorld = World;
	ParseStringToInfo(Info);
}

void UGameCapabilities::UseGameCapabilities()
{
	OnUseGameCapabilities();
}