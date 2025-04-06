#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "DurabilityComponent.generated.h"

//委托：耐久度为0时触发
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDurabilityExhausted, UDurabilityComponent*, DurabilityComponent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UDurabilityComponent : public UActorComponent, public ISetValueInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDurabilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
	float MaxDurability = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
	float CurrentDurability = 100.0f;




public:
	UPROPERTY(BlueprintAssignable, Category = "Durability")
	FOnDurabilityExhausted OnDurabilityExhausted;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetCurrentValue() const { return CurrentDurability; }

	UFUNCTION(BlueprintCallable, Category = "Durability")
	void SetCurrentValue(float NewValue) override
	{
		CurrentDurability = FMath::Clamp(NewValue, 0.0f, MaxDurability);
		if (CurrentDurability <= 0.0f)
		{
			OnDurabilityExhausted.Broadcast(this);
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	void SetMaxValue(float NewValue) override
	{
		MaxDurability = FMath::Max(NewValue, 0.0f);
		if (CurrentDurability > MaxDurability)
		{
			SetCurrentValue(MaxDurability);
		}
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	void SetPercentage(float NewValue) override
	{
		SetCurrentValue(NewValue * MaxDurability);
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	void SetFull() override
	{
		SetCurrentValue(MaxDurability);
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	void SetEmpty() override
	{
		SetCurrentValue(0.0f);
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	void AddValue(float Value) override
	{
		SetCurrentValue(CurrentDurability + Value);
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	void AddPercentage(float Value) override
	{
		SetCurrentValue(CurrentDurability + Value * MaxDurability);
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	bool SubtractValue(float Value) override
	{
		SetCurrentValue(CurrentDurability - Value);
		return CurrentDurability > 0.0f;
	}
	UFUNCTION(BlueprintCallable, Category = "Durability")
	bool SubtractPercentage(float Value) override
	{
		SetCurrentValue(CurrentDurability - Value * MaxDurability);
		return CurrentDurability > 0.0f;
	}


};
