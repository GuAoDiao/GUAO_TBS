// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"

#include "Components/ArrowComponent.h"


#include "Combat/CombatPawn.h"

ACombatManager::ACombatManager()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	CharacterMargin = 100.f;
	CommonAttackMargin = 20.f;
	CurrentCombatState = ECombatState::Startup;

	bWaitingForPawn = false;

	PrimaryActorTick.bCanEverTick = true;
}

void ACombatManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (UArrowComponent* ArrowComp : TeamArrowPositionComp)
	{
		ArrowComp->DestroyComponent();
	}

	TeamArrowPositionComp.Empty();

	if (TeamNums == TeamBasePosition.Num())
	{
		for (int32 i = 0; i < TeamNums; ++i)
		{
			UArrowComponent* ArrowComp = NewObject<UArrowComponent>(this);
			ArrowComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			ArrowComp->SetRelativeTransform(TeamBasePosition[i]);
			ArrowComp->RegisterComponent();
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("team nums not equal team base position nuyms"));
	}

}

void ACombatManager::ToggleToTargetState(ECombatState InTargetState)
{
	CurrentCombatState = InTargetState;
}

void ACombatManager::InitiallizeCombat(const TArray<FCombatTeam>& InAllTeamsInfo)
{
	if (!IsToggleTargetState(ECombatState::Startup)) { return; }

	const FVector CurrentLocation = GetActorLocation();

	checkf(TeamBasePosition.Num() >= TeamNums, TEXT("can't find enough position"));

	FVector AllLocation = FVector::ZeroVector;

	for (int32 i = 0; i < TeamNums; ++i)
	{
		AllLocation = (AllLocation + TeamBasePosition[i].GetLocation()) / 2.f;
	}

	for (int32 i = 0 ; i < TeamNums; ++i)
	{
		FCombatTeamInfo CombatTeamInfo;

		USceneComponent* TeamBaseComp = NewObject<USceneComponent>(this);
		if (TeamBaseComp)
		{
			TeamBaseComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			TeamBaseComp->SetRelativeTransform(TeamBasePosition[i]);
			TeamBaseComp->RegisterComponent();

			const int32 CombatPawnsNum = InAllTeamsInfo[i].AllCombatPawns.Num();
			const FVector CharacterMarginVector = CharacterMargin * TeamBasePosition[i].GetRotation().GetAxisY();
			const FVector CommonAttackMarginVector = CommonAttackMargin * TeamBasePosition[i].GetRotation().GetAxisX();
			const FVector BaseLocation = CurrentLocation + TeamBasePosition[i].GetLocation() - (float)CombatPawnsNum / 2.f * CharacterMarginVector;
			const FRotator BaseRotation = FRotationMatrix::MakeFromX(AllLocation - TeamBasePosition[i].GetLocation()).Rotator();

			for (int32 j = 0; j < CombatPawnsNum; ++j)
			{
				if (!InAllTeamsInfo[i].AllCombatPawns[j]) { continue; }

				FCombatPawnInfo CombatPawnInfo;
				CombatPawnInfo.CombatPawn = InAllTeamsInfo[i].AllCombatPawns[j];
				FVector CombatPawnLocation = BaseLocation + CharacterMarginVector * j;
				CombatPawnInfo.CommonAttackLocation = CombatPawnLocation + CommonAttackMarginVector;
				CombatPawnInfo.CombatPawn->SetActorLocationAndRotation(CombatPawnLocation, BaseRotation);

				CombatTeamInfo.AllCombatPawnInfo.Add(CombatPawnInfo);
			}
		}

		CombatTeamInfo.TeamBaseComps = TeamBaseComp;

		AllTeamsInfo.Add(CombatTeamInfo);
	}


	ToggleToTargetState(ECombatState::BeginCombat);
}



void ACombatManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentCombatState)
	{
		case ECombatState::Startup:
			break;
		case ECombatState::BeginCombat:
			ChooseFirstPawn();
			break;
		case ECombatState::ChoosePawn:
			ChooseNextPawn();
			break;
		case ECombatState::BeginPawnTurn:
			BeginPawnTurn();
			break;
		case ECombatState::Decision:
			Decision(DeltaSeconds);
			break;
		case ECombatState::Action:
			Action(DeltaSeconds);
			break;
		case ECombatState::EndPawnTurn:
			EndPawnTurn();
			break;
		case ECombatState::TurnTeam:
			TurnTeam();
			break;
		case ECombatState::TurnBout:
			TurnBout();
			break;
		case ECombatState::GameOver:
			break;
		case ECombatState::Victory:
			break;
	}
}


void ACombatManager::ChooseFirstPawn()
{

	CurrentTeamNum = -1;
	CurrentBout = 0;
	ToggleToTargetState(ECombatState::TurnTeam);
}

void ACombatManager::ChooseNextPawn()
{
	CurrentPawnNum++;

	checkf(AllTeamsInfo.IsValidIndex(CurrentTeamNum), TEXT("-_- can'f find right team"));

	if (AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo.Num() == CurrentPawnNum)
	{
		ToggleToTargetState(ECombatState::TurnTeam);
	}
	else
	{
		ToggleToTargetState(ECombatState::BeginPawnTurn);
	}
}

void ACombatManager::TurnTeam()
{
	CurrentTeamNum++;
	CurrentPawnNum = 0;

	if (CurrentTeamNum == TeamNums)
	{
		ToggleToTargetState(ECombatState::TurnBout);
	}
	else
	{
		checkf(AllTeamsInfo.IsValidIndex(CurrentTeamNum) && AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo.IsValidIndex(0), TEXT("-_- can't find right pawn"));
		ToggleToTargetState(ECombatState::BeginPawnTurn);
	}
}

void ACombatManager::TurnBout()
{
	CurrentBout++;
	CurrentTeamNum = -1;

	UE_LOG(LogTemp, Log, TEXT("-_- Current Bout is %d, Turn Team"), CurrentBout);
	ToggleToTargetState(ECombatState::TurnTeam);
}

void ACombatManager::BeginPawnTurn()
{
	UE_LOG(LogTemp, Log, TEXT("-_- current team : %d, current pawn: %d"), CurrentTeamNum, CurrentPawnNum);

	AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].OnBeginPawnTurn.Broadcast(AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum]);
	ToggleToTargetState(ECombatState::Decision);
}

void ACombatManager::EndPawnTurn()
{
	AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].OnEndTurnDelegate.Broadcast(AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum]);
	ToggleToTargetState(ECombatState::ChoosePawn);
}


void ACombatManager::Decision(float DeltaSeconds)
{
	if (!bWaitingForPawn)
	{
		bWaitingForPawn = true;
		AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].CombatPawn->BeginMakeDecision();
	}
	else
	{
		if (AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].CombatPawn->MakeDecision(DeltaSeconds))
		{
			bWaitingForPawn = false;
			ToggleToTargetState(ECombatState::Action);
		}
	}
}
void ACombatManager::Action(float DeltaSeconds)
{
	if (!bWaitingForPawn)
	{
		bWaitingForPawn = true;
		AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].CombatPawn->BeginExecuteAction();
	}
	else
	{
		if (AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].CombatPawn->ExecuteAction(DeltaSeconds))
		{
			bWaitingForPawn = false;
			ToggleToTargetState(ECombatState::EndPawnTurn);
		}
	}
}