#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "SpellCoolComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API USpellCoolComponent : public UActorComponent, public ISetValueInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpellCoolComponent();

private:
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool IsCooling = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellCool")
	float CoolTime = 1.0f;

	float CoolTimeCounter = 0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	void StartCool();


	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	bool IsCoolingNow() { return IsCooling; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	float GetCoolTime() { return CoolTime; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	float GetRemainingPercentage() { return CoolTimeCounter / CoolTime; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	float GetRemainingCoolTime() { return  CoolTimeCounter; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void SetCurrentValue(float Value) override;

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void SetMaxValue(float Value) override{}

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void SetPercentage(float Value) override { SetCurrentValue(Value * CoolTime); }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void SetFull() override { CoolTimeCounter = CoolTime; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void SetEmpty() override { CoolTimeCounter = 0; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void AddValue(float Value) override { SetCurrentValue(CoolTimeCounter + Value); }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual void AddPercentage(float Value) override { SetPercentage(Value * CoolTime+ CoolTimeCounter); }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual bool SubtractValue(float Value) override { SetCurrentValue(CoolTimeCounter - Value); return true; }

	UFUNCTION(BlueprintCallable, Category = "SpellCool")
	virtual bool SubtractPercentage(float Value) override { SetPercentage(CoolTimeCounter - Value); return true; }







};
