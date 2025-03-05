// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/AttributeComponent/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetCurrentValue(float NewValue)
{
	if (!CanBeHurt)
	{
		if (NewValue <= CurrentHealth)
		{
			return ;
		}
		else
		{
			CurrentHealth = NewValue;
			return ;
		}
	}
	else if (NewValue >0)
	{
		if (NewValue > MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
		else
		{
			CurrentHealth = NewValue;
		}
		return ;
	}
	else
	{
		CurrentHealth = 0;
		OnDeath.Broadcast();
		return ;
	}
}




