// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TBSPropsTypes.h"

#include "GamePropsComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUAO_TBS_API UGamePropsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGamePropsComponent();
	
	int32 GetPropsNum(int32 PropsID) const;
	void AddProps(int32 PropsID, int32 PropsNum);
	void UseSingleProps(int32 PropsID);
	void UseMultiProps(int32 PropsID, int32 PropsNum);
	void RemoveProps(int32 PropsID, int32 PropsNum);
	const TArray<FPropsStoreItemInfo>& GetPropsStoreInfo() const { return PropsStoreBag; }

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropsStoreInfoUpdate, const TArray<FPropsStoreItemInfo>& /* PropsStoreBag */);
	FOnPropsStoreInfoUpdate OnPropsStoreInfoUpdate;

protected:
	int32 MaxPropsNum;
	TArray<FPropsStoreItemInfo> PropsStoreBag;
};
