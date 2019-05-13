// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuBaseWidget.h"

#include "UI/MenuLayoutWidget.h"


void UMenuBaseWidget::SetMenuLayoutWidget(class UMenuLayoutWidget* InMenuLayoutWidget)
{
	MenuLayoutWidget = MakeWeakObjectPtr(InMenuLayoutWidget);
}
