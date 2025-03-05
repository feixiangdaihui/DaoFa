// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "HealthComponent.generated.h"

// 死亡委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);


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

	//死亡委托
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

	//是否可以被伤害，但不包括免疫debuff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool CanBeHurt = true;

	//是否可以被治疗
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool CanBeHealed = true;

	//是否可以被影响，主要用于免疫debuff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool CanBeInfluenced = true;

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
	virtual void SetCurrentValue(float NewValue) override;

	//如果新的值小于当前值，是一种debuff，如果新的值大于当前值，是一种buff
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetMaxValue(float NewValue) override 
	{
		if (CanBeInfluenced)
		{
			MaxHealth = FMath::Max(NewValue, 0.0f);

			if (CurrentHealth > MaxHealth)
			{
				SetCurrentValue(MaxHealth);
			}
		}
		else
		{
			MaxHealth = FMath::Max(NewValue, MaxHealth);
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetPercentage(float NewValue) override { SetCurrentValue(MaxHealth * NewValue); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetFull() override { SetCurrentValue(MaxHealth); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetEmpty() override { SetCurrentValue(0); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddValue(float Value) override { SetCurrentValue(CurrentHealth + Value); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void AddPercentage(float Value) override { SetCurrentValue(CurrentHealth + MaxHealth * Value); }
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool SubtractValue(float Value) override
	{ 
		SetCurrentValue(CurrentHealth - Value);
		return true;
	}
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool SubtractPercentage(float Value) override
	{
		SetCurrentValue(CurrentHealth - MaxHealth * Value);
		return true;
	}



};
