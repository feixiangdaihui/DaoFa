// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"


// Sets default values for this component's properties
UBlueCostComponent::UBlueCostComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBlueCostComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlueCostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBlueCostComponent::BlueCostAtStart(UBlueComponent* BlueComponent)
{
	return BlueComponent->SubtractValue(StartBlueCost);
}

bool UBlueCostComponent::BlueCostOnGoing(UBlueComponent* BlueComponent, float DeltaTime)
{
	return BlueComponent->SubtractValue(OnGoingBlueCostBySecond * DeltaTime);
}

bool UBlueCostComponent::BlueCostInTheEnd(UBlueComponent* BlueComponent)
{
	return BlueComponent->SubtractValue(EndBlueCost);
}





