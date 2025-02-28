#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "General/ElementSetting.h"
#include "General/AttackAttributeComponent.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "DefenseComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UDefenseComponent : public UActorComponent, public ISetValueInterface
{
	GENERATED_BODY()

	friend class UCalAttackLibrary;
public:
	// Sets default values for this component's properties
	UDefenseComponent();

	void SetDefenseElement(GElement NewElement) { DefenseElement = NewElement; }

	void SetAvoidInterruptAblity(EAvoidInterruptAblity NewAvoidAblity) { AvoidAblity = NewAvoidAblity; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense")
	GElement DefenseElement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense")
	EAvoidInterruptAblity AvoidAblity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense")
	float StartToBeInterruptedPercent = 1.0f;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void SetCurrentValue(float NewValue) override
	{
		if (NewValue <= 0)
			Defense = 0;
		else
			Defense = NewValue;
	};
	//无效
	virtual void SetMaxValue(float NewValue) override {};

	//百分比削减抗性
	virtual void SetPercentage(float NewValue) override
	{
		SetCurrentValue(NewValue * Defense);
	}
	//无效
	virtual void SetFull() override{};
	//削减抗性为0
	virtual void SetEmpty() override { Defense = 0; };

	//增加抗性
	virtual void AddValue(float Value) override
	{
		Defense += Value;
	};

	//增加百分比抗性
	virtual void AddPercentage(float Value) override
	{
		Defense += Value * Defense;
	};

	//减少抗性
	virtual bool SubtractValue(float Value) override
	{
		SetCurrentValue(Defense - Value);
		return true;
	};

	//减少百分比抗性
	virtual bool SubtractPercentage(float Value) override
	{
		SetPercentage(Defense - Value);
		return true;
	};




};
