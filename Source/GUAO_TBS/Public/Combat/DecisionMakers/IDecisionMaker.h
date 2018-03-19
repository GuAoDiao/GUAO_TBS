// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class IDecisionMaker
{
public:
	virtual void BeginMakeDecision(class ACombatPawn* Character) = 0;
	virtual bool MakeDecision(float DeltaSeconds) = 0;
};
