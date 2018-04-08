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

	//////////////////////////////////////////////////////////////////////////
	/// Base Comp
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

	bool bCanMoveViewport;
private:
	float ScrollRoof;
	float ScrollFloor;

	float CameraScrollSpeed;
	float CameraMoveSpeed;
	float CameraRotateSpeed;

	//////////////////////////////////////////////////////////////////////////
	/// Clicked Tile To Move or Talk With NPC or Fight With Enemy
protected:
	void ClickedTile();

	bool FindCurrentMouseOverTileIndex(int32& OutIndex);

	bool bDisableClickTile;
	int32 SelectTilePawnIndex;

	FGridPathFinding* GridPathFinding;
	//////////////////////////////////////////////////////////////////////////
	/// Movement 
protected:
	void StartMovement();
	void TickMovement(float DeltaSeconds);
	void EndMovement();

	UPROPERTY(BlueprintReadOnly)
	float CurrentSpeed;

	bool bIsMoving;
	float CurrentSplineDistance;
	float SplineHeight;

	float PawnMovementSpeedAcceleration;
	float PawnMaxSpeed;

	//////////////////////////////////////////////////////////////////////////
	/// _Dialogue
public:
	void OpenDialogue(int32 DialogueID);
};
