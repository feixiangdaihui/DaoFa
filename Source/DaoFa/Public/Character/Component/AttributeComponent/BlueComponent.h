// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "General/Interface/SaveLoadData.h"
#include "BlueComponent.generated.h"

//蓝量耗尽委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlueEmptyDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API  UBlueComponent : public UActorComponent, public IGetValueInterface, public ISetValueInterface, public ISaveLoadData
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float MaxBlue = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blue")
	float CurrentBlue = 100.0f;

	UFUNCTION(BlueprintCallable, Category = "Blue")
	void RecoverBlueBySecond(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float RecoverBlueAmountBySecond = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float BlueDensity = 100.0f;


public:	
	
	void AddBlueDensity(float Value) { BlueDensity += Value; }

	float GetBlueDensity() { return BlueDensity; }

	void SubtractBlueDensity(float Value) { BlueDensity = FMath::Max(BlueDensity - Value, 0.0f); }


	UPROPERTY(BlueprintAssignable, Category = "Blue")
	FOnBlueEmptyDelegate OnBlueEmpty;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// IGetValueInterface
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual float GetCurrentValue() const override { return CurrentBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual float GetMaxValue() const override { return MaxBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual float GetPercentage() const override { return CurrentBlue / MaxBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual bool IsFull() const override { return CurrentBlue == MaxBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual bool IsEmpty() const override { return CurrentBlue == 0; }

	// ISetValueInterface
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void SetCurrentValue(float NewValue) override
	{
		if (NewValue > 0)
		{
			if (NewValue > MaxBlue)
			{
				CurrentBlue = MaxBlue;
			}
			else
			{
				CurrentBlue = NewValue;
			}
		}
		else
		{
			CurrentBlue = 0;
			OnBlueEmpty.Broadcast();
		}
	}	
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void SetMaxValue(float NewValue) override
	{
		MaxBlue = FMath::Max(NewValue, 0.0f);
		if (CurrentBlue > MaxBlue)
		{
			SetCurrentValue(MaxBlue);
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void SetPercentage(float NewValue) override { SetCurrentValue(MaxBlue * NewValue); }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void SetFull() override { CurrentBlue = MaxBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void SetEmpty() override { CurrentBlue = 0; OnBlueEmpty.Broadcast(); }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void AddValue(float Value) override { SetCurrentValue(CurrentBlue + Value); }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual void AddPercentage(float Value) override { SetCurrentValue(CurrentBlue + MaxBlue * Value); }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual bool SubtractValue(float Value) override
	{ 
		if (CurrentBlue >= Value) 
		{ 
			SetCurrentValue(CurrentBlue - Value); 
			return true;
		} 
		return false; 
	}
	UFUNCTION(BlueprintCallable, Category = "Blue")
	virtual bool SubtractPercentage(float Value) override
	{
		if (CurrentBlue >= Value * MaxBlue)
		{
			SetCurrentValue(CurrentBlue - Value * MaxBlue);
			return true;
		}
		return false;
	}


	virtual FJsonObject SaveDataMethod() const override;

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) override;

	virtual FString GetKey() const override { return TEXT("BlueComponent"); }
	

		
};
