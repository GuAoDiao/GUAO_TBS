// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCapabilities.h"




void UGameCapabilities::InitializeGameCapabilities(const FString& Info)
{
	ParseStringToInfo(Info);
}

void UGameCapabilities::UseGameCapabilities()
{
	OnUseGameCapabilities();
}