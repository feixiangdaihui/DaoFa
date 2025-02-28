// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Character/Component/AttributeComponent/AttributeComponent.h"
#include "Creature.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"


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
	AActor* CreatureActor = GetOwner()->GetOwner();
	ACreature* Creature = Cast<ACreature>(CreatureActor);
	if (Creature)
	{
		BlueValue = Creature->GetAttributeComponent()->SetBlueValue();
	}

	// ...
	
}


// Called every frame
void UBlueCostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBlueCostComponent::BlueCost(float CostValue)
{
	return BlueValue->SubtractValue(CostValue);
}








