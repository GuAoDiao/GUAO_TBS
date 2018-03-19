// Fill out your copyright notice in the Description page of Project Settings.

#include "TBSPlayerController.h"
#include "TBSCharacter.h"

ATBSPlayerController::ATBSPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
}

void ATBSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetViewportRightBottomPosition();
}

void ATBSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveViewportFromMouse();
}

void ATBSPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InputComponent)
	{
		InputComponent->ClearActionBindings();
		InputComponent->AxisBindings.Empty();

		RebindInputComponent(InputComponent);

		OwnerTBSCharacter = Cast<ATBSCharacter>(InPawn);
		if (OwnerTBSCharacter) { OwnerTBSCharacter->RebindInputComponent(InputComponent); }
	}
}


void ATBSPlayerController::RebindInputComponent(UInputComponent* InInputComp)
{

}


void ATBSPlayerController::GetViewportRightBottomPosition()
{
	int32 ViewportWidth, ViewportHeight;
	GetViewportSize(ViewportWidth, ViewportHeight);

	ViewportRightPosition = ViewportWidth - 5.f;
	ViewportBottomPosition = ViewportHeight - 5.f;
}

void ATBSPlayerController::MoveViewportFromMouse()
{
	if (OwnerTBSCharacter)
	{
		GetViewportRightBottomPosition();

		float MouseX, MouseY;
		GetMousePosition(MouseX, MouseY);

		if (MouseX == 0.f)
		{
			OwnerTBSCharacter->MoveHorizontal(-1.f);
		}
		else if (MouseX >= ViewportRightPosition)
		{
			OwnerTBSCharacter->MoveHorizontal(1.f);
		}

		if (MouseY == 0.f)
		{
			OwnerTBSCharacter->MoveVertical(1.f);
		}
		else if (MouseY >= ViewportBottomPosition)
		{
			OwnerTBSCharacter->MoveVertical(-1.f);
		}
	}
}