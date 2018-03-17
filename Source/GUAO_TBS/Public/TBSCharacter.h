// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilePawn.h"
#include "TBSCharacter.generated.h"

class AGridManager;
class FGridPathFinding;

UCLASS()
class GUAO_TBS_API ATBSCharacter : public ATilePawn
{
	GENERATED_BODY()

public:
	ATBSCharacter();

	virtual void OnConstruction(const FTransform& Transform) override;
	void RebindInputComponent(UInputComponent* InInputComp);
	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;
	UPROPERTY()
	class USplineComponent* MovePathComp;
	//////////////////////////////////////////////////////////////////////////
	/// Visual Angel
public:
	void ZoomIn();
	void ZoomOut();

	void RotatingAngleOfView(float AxisValue);
	void ResetAngleOfView();
	void MoveHorizontal(float AxisValue);
	void MoveVertical(float AxisValue);
private:
	float ScrollRoof;
	float ScrollFloor;

	float CameraScrollSpeed;
	float CameraMoveSpeed;
	float CameraRotateSpeed;


protected:
	void ClickedTile();

	bool FindCurrentMouseOverTileIndex(int32& OutIndex);

	bool bDisableClickTile;
	int32 SelectTilePawnIndex;
	float SplineHeight;

	FGridPathFinding* GridPathFinding;

	bool bIsMoving;
	float CurrentSplineDistance;
	float PawnMovementSpeedAcceleration;
	float PawnMaxSpeed;

	virtual void StartMovement();
	virtual void TickMovement(float DeltaSeconds);
	virtual void EndMovement();
};
