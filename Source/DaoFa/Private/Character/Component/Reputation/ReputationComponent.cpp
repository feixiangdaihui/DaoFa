// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Reputation/ReputationComponent.h"
#include "Character/Component/Reputation/FaceComponent.h"


// Sets default values for this component's properties
UReputationComponent::UReputationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FaceComponent = CreateDefaultSubobject<UFaceComponent>(TEXT("FaceComponent"));

	// ...
}


// Called when the game starts
void UReputationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UReputationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UReputationComponent::AddValue(float Value)
{
	if (Value < 0.0f)
		Value = 0.0f;
	ReputationValue += Value;
	FaceComponent->AddValue(Value);
}

void UReputationComponent::SubtractValue(float Value)
{
	ReputationValue -= Value;
	if (ReputationValue < 0.0f)
		ReputationValue = 0.0f;
	FaceComponent->SubtractValue(Value);
}

FJsonObject UReputationComponent::SaveDataMethod() const
{
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	SaveData->SetNumberField(TEXT("ReputationValue"), ReputationValue);

	return *SaveData;
}

void UReputationComponent::LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		ReputationValue = JsonObject->GetNumberField(TEXT("ReputationValue"));
	}
}

