// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/AttributeComponent/BlueComponent.h"

// Sets default values for this component's properties
UBlueComponent::UBlueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBlueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UBlueComponent::RecoverBlueBySecond(float DeltaTime)
{
	//每秒回复蓝量
	CurrentBlue += RecoverBlueAmountBySecond * DeltaTime;
	if (CurrentBlue > MaxBlue)
	{
		CurrentBlue = MaxBlue;
	}
}

// Called every frame
void UBlueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RecoverBlueBySecond(DeltaTime);
	// ...
}

FJsonObject UBlueComponent::SaveDataMethod() const
{
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	SaveData->SetNumberField(TEXT("MaxBlue"), MaxBlue);
	SaveData->SetNumberField(TEXT("CurrentBlue"), CurrentBlue);
	SaveData->SetNumberField(TEXT("BlueDensity"), BlueDensity);
	SaveData->SetNumberField(TEXT("RecoverBlueAmountBySecond"), RecoverBlueAmountBySecond);
	return *SaveData;
}

void UBlueComponent::LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject)
{
	MaxBlue = JsonObject->GetNumberField(TEXT("MaxBlue"));
	CurrentBlue = JsonObject->GetNumberField(TEXT("CurrentBlue"));
	BlueDensity = JsonObject->GetNumberField(TEXT("BlueDensity"));
	RecoverBlueAmountBySecond = JsonObject->GetNumberField(TEXT("RecoverBlueAmountBySecond"));
}

