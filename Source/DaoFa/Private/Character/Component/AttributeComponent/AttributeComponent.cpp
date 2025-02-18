// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/AttributeComponent/AttributeComponent.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Character/BaseCharacter.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	PhysicalPowerComponent = CreateDefaultSubobject<UPhysicalPowerComponent>(TEXT("PhysicalPowerComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));


	// ...
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	// ...
	
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


