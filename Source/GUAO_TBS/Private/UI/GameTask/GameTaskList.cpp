// Fill out your copyright notice in the Description page of Project Settings.

#include "GameTaskList.h"


#include "TBSCharacter.h"
#include "UI/GameTask/GameTaskItem.h"
#include "GameTask/GameTaskComponent.h"

void UGameTaskList::NativeConstruct()
{
	APlayerController* OnwerPC = GetOwningPlayer();
	ATBSCharacter* OwnetTBSCharacter = OnwerPC ? Cast<ATBSCharacter>(OnwerPC->GetPawn()) : nullptr;
	OwnerGameTaskComp = OwnetTBSCharacter ? OwnetTBSCharacter->GetGameTaskComp() : nullptr;
}


void UGameTaskList::OnAcceptTaskListUpdate()
{
	if (OwnerGameTaskComp)
	{
		APlayerController* OwnerPC = GetOwningPlayer();
		TSubclassOf<UGameTaskItem> GameTaskItemClass = LoadClass<UGameTaskItem>(nullptr, TEXT("WidgetBlueprint'/Game/GUAO_TBS/UI/GameTask/W_GameTaskItem.W_GameTaskItem_C'"));
		if (OwnerPC && GameTaskItemClass)
		{
			for (TMap<int32, UGameTask*>::TConstIterator It(OwnerGameTaskComp->GetAllAccpetTasks()); It; ++It)
			{
				UGameTaskItem* GameTaskItem = CreateWidget<UGameTaskItem>(OwnerPC, GameTaskItemClass);
				if (GameTaskItem)
				{
					GameTaskItem->InitializeGameTaskItem(It.Value());
					AddGameTaskItem(GameTaskItem);
				}
			}
		}
	}
}