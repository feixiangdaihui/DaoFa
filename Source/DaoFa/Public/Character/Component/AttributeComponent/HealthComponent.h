// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UHealthComponent : public UActorComponent, public IGetValueInterface, public ISetValueInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 100.0f;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual float GetCurrentValue() const override { return CurrentHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual float GetMaxValue() const override { return MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual float GetPercentage() const override { return CurrentHealth / MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool IsFull() const override { return CurrentHealth == MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool IsEmpty() const override { return CurrentHealth == 0; }


	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetCurrentValue(float NewValue) override
	{
		if (NewValue >= 0 )
		{
			if (NewValue > MaxHealth)
			{
				CurrentHealth = MaxHealth;
			}
			else
			{
				CurrentHealth = NewValue;
			}
		}
		else
		{
			CurrentHealth = 0;
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetMaxValue(float NewValue) override 
	{ 
		MaxHealth = FMath::Max(NewValue, 0.0f);
		if (CurrentHealth > MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetPercentage(float NewValue) override { SetCurrentValue(MaxHealth * NewValue); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetFull() override { CurrentHealth = MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetEmpty() override { CurrentHealth = 0; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddValue(float Value) override { SetCurrentValue(CurrentHealth + Value); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddPercentage(float Value) override { SetCurrentValue(CurrentHealth + MaxHealth * Value); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool SubtractValue(float Value) override
	{ 
		if (CurrentHealth - Value < 0)
		{
			CurrentHealth = 0;
			return false;
		}
		else
		{
			CurrentHealth -= Value;
			return true;
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool SubtractPercentage(float Value) override
	{
		if (CurrentHealth - Value * MaxHealth < 0)
		{
			CurrentHealth = 0;
			return false;
		}
		else
		{
			CurrentHealth -= Value * MaxHealth;
			return true;
		}

	}



};
