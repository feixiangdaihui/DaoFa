// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FaceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UFaceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFaceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face")
	float FaceValue = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddValue(float Value)
	{
		if (Value < 0.0f)
			Value = 0.0f;
		FaceValue += Value;
	}
	void SubtractValue(float Value)
	{
		FaceValue -= Value;
		if (FaceValue < 0.0f)
			FaceValue = 0.0f;
	}
	float GetCurrentValue() const
	{
		return FaceValue;
	}


		
};
