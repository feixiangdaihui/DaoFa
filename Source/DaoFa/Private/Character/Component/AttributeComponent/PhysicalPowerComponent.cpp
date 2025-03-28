// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"

// Sets default values for this component's properties
UPhysicalPowerComponent::UPhysicalPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPhysicalPowerComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

void UPhysicalPowerComponent::RecoverPhysicalPowerBySecond(float DeltaTime)
{
	if (RecoverLock)
	{
		return;
	}
	//每秒回复体力
	CurrentPhysicalPower += RecoverPhysicalPowerAmountBySecond * DeltaTime;
	if (CurrentPhysicalPower > MaxPhysicalPower)
	{
		CurrentPhysicalPower = MaxPhysicalPower;
	}
}



// Called every frame
void UPhysicalPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RecoverPhysicalPowerBySecond(DeltaTime);
	// ...
}




