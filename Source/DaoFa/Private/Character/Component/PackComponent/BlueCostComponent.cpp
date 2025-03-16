// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Creature.h"
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
	AActor* CreatureActor = GetOwner()->GetOwner();
	ACreature* Creature = Cast<ACreature>(CreatureActor);
	if (Creature)
	{
		BlueValue = Creature->GetBlueComponent();
	}

	// ...
	
}


// Called every frame
void UBlueCostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}




bool UBlueCostComponent::ShortPressCostBlue()
{
	return BlueValue->SubtractValue(ShortPressBlueCost);
}
bool UBlueCostComponent::LongPressCostBlue()
{
	return BlueValue->SubtractValue(LongPressBlueCost);
}



void UBlueCostComponent::OngoingCostBlue()
{
    if (OngoingMode)
    {
        if (BlueValue->SubtractValue(OngoingBlueCost))
        {
			GetWorld()->GetTimerManager().SetTimer(OngoingTimer, [this]() {BlueValue->SubtractValue(OngoingBlueCost); }, OngoingInterval, true);
        }
    }
}

void UBlueCostComponent::EndOngoingCostBlue()
{
	GetWorld()->GetTimerManager().ClearTimer(OngoingTimer);
}






