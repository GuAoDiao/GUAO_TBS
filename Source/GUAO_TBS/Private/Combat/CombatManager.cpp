// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Combat/CombatPawn.h"
#include "Combat/CombatLayout.h"
#include "TBSPlayerController.h"
#include "TBSGameState.h"

ACombatManager::ACombatManager()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	CharacterMargin = 250.f;
	CommonAttackMargin = 100.f;
	CurrentCombatState = ECombatState::Startup;
	bWaitingForPawn = false;
	bWantedAndCanRunAway = false;
	bIsAutoAttack = false;

	TeamNums = 2;
	TeamBasePosition.Add(FVector(250.f, 0.f, 0.f));
	TeamBasePosition.Add(FVector(-250.f, 0.f, 0.f));

	PrimaryActorTick.bCanEverTick = true;
}

void ACombatManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (UArrowComponent* ArrowComp : TeamArrowPositionComp)
	{
		if (ArrowComp) { ArrowComp->DestroyComponent(); }
	}

	TeamArrowPositionComp.Empty();

	if (TeamNums == TeamBasePosition.Num())
	{
		for (int32 i = 0; i < TeamNums; ++i)
		{
			UArrowComponent* ArrowComp = NewObject<UArrowComponent>(this);
			ArrowComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			ArrowComp->SetRelativeLocation(TeamBasePosition[i]);
			ArrowComp->RegisterComponent();
			TeamArrowPositionComp.Add(ArrowComp);
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

void ACombatManager::InitiallizeCombat(const TArray<FCombatTeam>& InAllTeamsInfo, int32 InPlayerTeam)
{
	if (!IsToggleTargetState(ECombatState::Startup)) { return; }

	checkf(TeamBasePosition.Num() >= TeamNums, TEXT("can't find enough position"));
	
	const FVector CurrentLocation = GetActorLocation();
	// calculate the middle position
	FVector MiddleLocation = FVector::ZeroVector;
	for (int32 i = 0; i < TeamNums; ++i)
	{
		MiddleLocation = i == 0 ? TeamBasePosition[0] : (MiddleLocation + TeamBasePosition[i]) / 2.f;
	}


	MiddleLocation += CurrentLocation;

	SpringArmComp->SetWorldLocation(MiddleLocation);
	SpringArmComp->TargetArmLength=  800.f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.f, -105.f, 0.f));

	// set current player team
	PlayerTeam = InPlayerTeam;

	// initialize all combat team info
	for (int32 i = 0 ; i < TeamNums; ++i)
	{
		FCombatTeamInfo CombatTeamInfo;

		USceneComponent* TeamBaseComp = NewObject<USceneComponent>(this);
		if (TeamBaseComp)
		{
			TeamBaseComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			TeamBaseComp->SetRelativeLocation(TeamBasePosition[i]);
			TeamBaseComp->RegisterComponent();

			const int32 CombatPawnsNum = InAllTeamsInfo[i].AllCombatPawns.Num();
			const FRotator BaseRotation = FRotationMatrix::MakeFromX(MiddleLocation - (CurrentLocation + TeamBasePosition[i])).Rotator();
			const FVector CharacterMarginVector = CharacterMargin * BaseRotation.Quaternion().GetAxisY();
			const FVector CommonAttackMarginVector = CommonAttackMargin * BaseRotation.Quaternion().GetAxisX();

			const FVector PawnBaseLocation = CurrentLocation + TeamBasePosition[i] - (float)(CombatPawnsNum - 1) / 2.f * CharacterMarginVector;
			
			// initialize all combat pawn info
			for (int32 j = 0; j < CombatPawnsNum; ++j)
			{
				if (!InAllTeamsInfo[i].AllCombatPawns[j]) { continue; }

				FCombatPawnInfo CombatPawnInfo;
				CombatPawnInfo.CombatPawn = InAllTeamsInfo[i].AllCombatPawns[j];
				
				CombatPawnInfo.CombatPawn->SetCombatManager(this);
				CombatPawnInfo.CombatPawn->CombatTeam = i;
				CombatPawnInfo.CombatPawn->GetOnCombatPawnDeathDelegate().AddUObject(this, &ACombatManager::CheckCombatState);

				FVector CombatPawnLocation = PawnBaseLocation + CharacterMarginVector * j;
				CombatPawnInfo.CommonAttackLocation = CombatPawnLocation + CommonAttackMarginVector;
				CombatPawnInfo.CombatPawn->SetActorLocationAndRotation(CombatPawnLocation, BaseRotation);
				CombatTeamInfo.AllCombatPawnInfo.Add(CombatPawnInfo);
			}
		}

		CombatTeamInfo.TeamBaseComps = TeamBaseComp;
		CombatTeamInfo.TeamName = InAllTeamsInfo[i].TeamName;

		AllTeamsInfo.Add(CombatTeamInfo);
	}


	ToggleToTargetState(ECombatState::Startup);
}

void ACombatManager::CheckCombatState()
{
	int32 SurvivingTeams = -1;

	for (int32 i = 0; i < AllTeamsInfo.Num(); ++i)
	{
		for (const FCombatPawnInfo& CombatPawnInfo : AllTeamsInfo[i].AllCombatPawnInfo)
		{
			if (CombatPawnInfo.CombatPawn && !CombatPawnInfo.CombatPawn->IsCombatPawnDead())
			{
				if (SurvivingTeams == i) { continue; }
				else if (SurvivingTeams == -1) { SurvivingTeams = i; continue; }
				else { return; }
			}
		}
	}

	WinTeam = SurvivingTeams;
	ToggleToTargetState(ECombatState::FightEnd);
}

void ACombatManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentCombatState)
	{
		case ECombatState::Startup:
			Startup();
			break;
		case ECombatState::BeginCombat:
			BeginCombat();
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
		case ECombatState::RunAway:
			RunAway();
			break;
		case ECombatState::FightEnd:
			FightEnd();
			break;
		case ECombatState::Results:
			break;
	}
}

void ACombatManager::Startup()
{
	if (!CombatLayout && CombatLayoutClass)
	{
		CombatLayout = CreateWidget<UCombatLayout>(GetGameInstance(), CombatLayoutClass);
		if (CombatLayout)
		{
			CombatLayout->CombatManager = this;
			CombatLayout->UpdateAutoAttackToggleDisplay(bIsAutoAttack);
			CombatLayout->AddToViewport();
		}
	}

	ToggleToTargetState(ECombatState::BeginCombat);
}

void ACombatManager::BeginCombat()
{
	CurrentTeamNum = -1;
	CurrentBout = 0;
	ToggleToTargetState(ECombatState::TurnTeam);
}

void ACombatManager::ChooseNextPawn()
{
	checkf(AllTeamsInfo.IsValidIndex(CurrentTeamNum), TEXT("-_- can'f find right team"));

	while (true)
	{
		CurrentPawnNum++;

		if (AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo.Num() == CurrentPawnNum)
		{
			ToggleToTargetState(ECombatState::TurnTeam);
			return;
		}
		else
		{
			ACombatPawn* CombatPawn = AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].CombatPawn;
			if (CombatPawn && !CombatPawn->IsCombatPawnDead())
			{
				if (CombatLayout) { CombatLayout->OnChangePawn(AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].CombatPawn->CombatPawnName); }
				ToggleToTargetState(ECombatState::BeginPawnTurn);
				return;
			}
		}
	}
}

void ACombatManager::TurnTeam()
{
	CurrentTeamNum++;
	CurrentPawnNum = -1;

	if (CurrentTeamNum == TeamNums)
	{
		ToggleToTargetState(ECombatState::TurnBout);
	}
	else
	{
		if (CombatLayout) { CombatLayout->OnChangeTeam(AllTeamsInfo[CurrentTeamNum].TeamName); }
		ToggleToTargetState(ECombatState::ChoosePawn);
	}
}

void ACombatManager::TurnBout()
{
	CurrentBout++;
	CurrentTeamNum = -1;

	if (CombatLayout) { CombatLayout->OnChangeBount(CurrentBout); }
	ToggleToTargetState(ECombatState::TurnTeam);
}

void ACombatManager::BeginPawnTurn()
{
	AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum].OnBeginPawnTurn.Broadcast(AllTeamsInfo[CurrentTeamNum].AllCombatPawnInfo[CurrentPawnNum]);
	ToggleToTargetState(ECombatState::Decision);
}

void ACombatManager::EndPawnTurn()
{
	if (bWantedAndCanRunAway)
	{
		ToggleToTargetState(ECombatState::RunAway);
		return;
	}


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


void ACombatManager::RunAway()
{
	if (CombatLayout) { CombatLayout->OnRunAwaySuccess(); }

	WinTeam = -1;
	ToggleToTargetState(ECombatState::Results);
}

void ACombatManager::FightEnd()
{
	if (CombatLayout) { CombatLayout->OnGameOver(AllTeamsInfo[WinTeam].TeamName, WinTeam == PlayerTeam); }
	ToggleToTargetState(ECombatState::Results);
}


void ACombatManager::CloseCombat()
{
	if (CombatLayout) { CombatLayout->RemoveFromParent(); }

	ATBSGameState* OwnerTBSGameState = GetWorld() ? GetWorld()->GetGameState<ATBSGameState>() : nullptr;
	if (OwnerTBSGameState)
	{
		OwnerTBSGameState->CloseCombat(WinTeam, WinTeam == PlayerTeam);
	}
}

bool ACombatManager::TryToRunAway(ACombatPawn* InCombatPawn)
{
	if (InCombatPawn)
	{
		if (FMath::RandRange(0.f, 1000.f) / 10.f < InCombatPawn->Luck)
		{
			bWantedAndCanRunAway = true;
		}
		else
		{
			bWantedAndCanRunAway = false;
			if (CombatLayout) { CombatLayout->OnRunAwayFailured(); }
		}

		return true;
	}

	return false;
}