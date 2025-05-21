// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "General/Interface/SaveLoadData.h"
#include "ReputationComponent.generated.h"

class UFaceComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UReputationComponent : public UActorComponent, public ISaveLoadData
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReputationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reputation")
	TObjectPtr<UFaceComponent> FaceComponent;

	float ReputationValue = 0.0f;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddValue(float Value);

	UFaceComponent* GetFaceComponent() const
	{
		return FaceComponent;
	}

	void SubtractValue(float Value);

	UFUNCTION(BlueprintCallable, Category = "Reputation")
	float GetReputationValue() const
	{
		return ReputationValue;
	}

	virtual FJsonObject SaveDataMethod() const override;

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) override;

	virtual FString GetKey() const override
	{
		return TEXT("ReputationComponent");
	}


};
