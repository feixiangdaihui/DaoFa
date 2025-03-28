// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
#include "PhysicalPowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UPhysicalPowerComponent : public UActorComponent, public ISetValueInterface, public IGetValueInterface

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
	void SetRecoverLock(bool lock) { RecoverLock = lock; }

	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void SetCurrentValue(float NewValue) override { CurrentPhysicalPower = FMath::Clamp(NewValue, 0.0f, MaxPhysicalPower); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void SetMaxValue(float NewValue) override { MaxPhysicalPower = FMath::Max(NewValue, 0.0f); SetCurrentValue(MaxPhysicalPower); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void SetPercentage(float NewValue) override { SetCurrentValue(MaxPhysicalPower * FMath::Max(NewValue, 0.0f)); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void SetFull() override { SetCurrentValue(MaxPhysicalPower); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void SetEmpty() override { SetCurrentValue(0.0f); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void AddValue(float Value) override { SetCurrentValue(CurrentPhysicalPower + Value); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual void AddPercentage(float Value) override { SetPercentage(GetPercentage() + Value); }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual bool SubtractValue(float Value) override { SetCurrentValue(CurrentPhysicalPower - Value); return true; }
	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	virtual bool SubtractPercentage(float Value) override { SetPercentage(GetPercentage() - Value); return true; }




};
