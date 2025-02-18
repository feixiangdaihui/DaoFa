// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
#include "Character/Interface/InputUpdateInterface.h"
#include "PhysicalPowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UPhysicalPowerComponent : public UActorComponent, public IGetValueInterface, public IInputUpdateInterface

{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicalPowerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float MaxPhysicalPower=100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalPower")
	float CurrentPhysicalPower = 100.0f;


	//每秒回复体力
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	void RecoverPhysicalPowerBySecond(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float RecoverPhysicalPowerAmountBySecond = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	bool RecoverLock = false;

	//跑步消耗体力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float RunLossPhysicalPowerAmountBySecond = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	void RunLossPhysicalPower(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	bool IsRun = false;

	//跑步锁
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float RunLockTime = 1.0f;
	float RunLockTimer = 0.0;


	//一次性消耗体力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float JumpLoss = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float DodgeLoss = 10.0f;

	//消耗体力
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	bool LossPhysicalPower(float value);

	//跳跃锁
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float JumpLockTime = 1.0f;
	float JumpLockTimer = 0.0;

	//翻滚锁
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float DodgeLockTime = 1.0f;
	float DodgeLockTimer = 0.0;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual float GetCurrentValue() const override { return CurrentPhysicalPower; }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual float GetMaxValue() const override { return MaxPhysicalPower; }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual float GetPercentage() const override { return CurrentPhysicalPower / MaxPhysicalPower; }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual bool IsFull() const override { return CurrentPhysicalPower == MaxPhysicalPower; }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual bool IsEmpty() const override { return CurrentPhysicalPower == 0; }

	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void UpdateInput(InputAnimation Input) override;
	virtual bool CheckInput(InputAnimation Input) override;



		
};
