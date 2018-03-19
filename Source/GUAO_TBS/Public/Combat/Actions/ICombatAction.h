// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ICombatAction
{
public:
	virtual void BeginExecuteAction(class ACombatPawn* Character) = 0;
	virtual bool ExecuteAction(float DeltaSeconds) = 0;
};
