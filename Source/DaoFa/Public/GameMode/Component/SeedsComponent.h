// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "General/Interface/SaveLoadData.h"
#include "SeedsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API USeedsComponent : public UActorComponent, public ISaveLoadData
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USeedsComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	uint32 Seed = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FJsonObject SaveDataMethod() const override
	{
		TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
		SaveData->SetNumberField(TEXT("Seed"), Seed);
		return *SaveData;
	}

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) override
	{
		if (JsonObject.IsValid())
		{
			Seed = JsonObject->GetNumberField(TEXT("Seed"));
			if (Seed <= 0)
			{
				Seed = FDateTime::Now().GetMillisecond();
			}
		}
	}

	virtual FString GetKey() const override
	{
		return TEXT("SeedsComponent");
	}

	UFUNCTION(BlueprintCallable, Category = "Seeds")
	FRandomStream GetRandomStream() const
	{
		return FRandomStream(Seed);
	}
};
