// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSGameMode_Menu.h"

#include "GameFramework/Menu/TBSHUD_Menu.h"

ATBSGameMode_Menu::ATBSGameMode_Menu()
{
	DefaultPawnClass = nullptr;
	HUDClass = ATBSHUD_Menu::StaticClass();
}
