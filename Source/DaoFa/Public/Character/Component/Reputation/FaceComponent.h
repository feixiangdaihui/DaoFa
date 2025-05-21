// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "General/Interface/SaveLoadData.h"
#include "FaceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UFaceComponent : public UActorComponent, public ISaveLoadData
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
	bool SubtractValue(float Value)
	{
		if (FaceValue < Value)
			return false;
		FaceValue -= Value;
		return true;
	}
	UFUNCTION(BlueprintCallable, Category = "Face")
	float GetCurrentValue() const
	{
		return FaceValue;
	}

	virtual FJsonObject SaveDataMethod() const override
	{
		TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
		SaveData->SetNumberField(TEXT("FaceValue"), FaceValue);
		return *SaveData;
	}

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) override
	{
		if (JsonObject.IsValid())
		{
			FaceValue = JsonObject->GetNumberField(TEXT("FaceValue"));
			if (FaceValue < 0.0f)
			{
				FaceValue = 0.0f;
			}
		}
	}
	virtual FString GetKey() const override
	{
		return TEXT("FaceComponent");
	}

		
};
