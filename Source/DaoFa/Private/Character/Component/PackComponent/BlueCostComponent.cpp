// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Creature.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Character/Component/PackComponent/PackObject.h"


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
	OwnerPackObject = Cast<APackObject>(GetOwner());
	if(!OwnerPackObject)
	{
		UE_LOG(LogTemp, Error, TEXT("%s OwnerPackObject is nullptr"), *this->GetName());
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
	if(ACreature* OwnerCreature= OwnerPackObject->GetOwnerCreature())
	{
		if (UBlueComponent* BlueComponent = OwnerCreature->GetBlueComponent())
		{
			return BlueComponent->SubtractValue(ShortPressBlueCost);
		}
	}
	return false;
}
bool UBlueCostComponent::LongPressCostBlue()
{
	if (ACreature* OwnerCreature = OwnerPackObject->GetOwnerCreature())
	{
		if (UBlueComponent* BlueComponent = OwnerCreature->GetBlueComponent())
		{
			return BlueComponent->SubtractValue(LongPressBlueCost);
		}
	}
	return false;
}



void UBlueCostComponent::OngoingCostBlue()
{
    if (OngoingMode)
    {
		if (ACreature* OwnerCreature = OwnerPackObject->GetOwnerCreature())
		{
			if (UBlueComponent* BlueComponent = OwnerCreature->GetBlueComponent())
			{
				GetWorld()->GetTimerManager().SetTimer(OngoingTimer, [this, BlueComponent]()
					{if (!BlueComponent->SubtractValue(OngoingBlueCost))
					{
						OwnerPackObject->TriggeredEnd();
						EndOngoingCostBlue();
					}
						; }, OngoingInterval, true);
			}
		}
    }
}

void UBlueCostComponent::EndOngoingCostBlue()
{
	GetWorld()->GetTimerManager().ClearTimer(OngoingTimer);
}






