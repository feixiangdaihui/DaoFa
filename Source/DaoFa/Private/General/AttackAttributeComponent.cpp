// Fill out your copyright notice in the Description page of Project Settings.


#include "General/AttackAttributeComponent.h"
#include "General/CalAttackLibrary.h"
#include "General/Interface/BeAttacked.h"

// Sets default values for this component's properties
UAttackAttributeComponent::UAttackAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAttackAttributeComponent::SetDamageMultiplier(float Multiplier, bool bIsPermanent, float Duration)
{
	if (bIsPermanent)
	{
		DamageMultiplier = Multiplier;
	}
	else
	{
		float Temp = DamageMultiplier;
		DamageMultiplier = Multiplier;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Temp]() { DamageMultiplier = Temp; }, Duration, false);
	}
}

void UAttackAttributeComponent::MultiplyDamageMultiplier(float Multiplier, bool bIsPermanent, float Duration)
{
	if (bIsPermanent)
	{
		DamageMultiplier *= Multiplier;
	}
	else
	{
		float Temp = DamageMultiplier;
		DamageMultiplier *= Multiplier;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Temp]() { DamageMultiplier = Temp; }, Duration, false);
	}
}

void UAttackAttributeComponent::Attack(IBeAttacked* BeAttacked)
{
	if(AActor* Other=Cast<AActor>(BeAttacked))
	{
		FAttackReturnValue ReturnValue = UCalAttackLibrary::CalculateAttack(UCalAttackLibrary::CreateAttackerInfo(this), BeAttacked->GetDefenderInfo());
		float Temp=BeAttacked->BeAttacked(ReturnValue);
		if (IsAttenuation&& Temp >= 0 && Temp <= 1)
		{
			BaseDamage *=(1-Temp);
			if (BaseDamage <= 0)
			{
				BaseDamage = 0;
				OnAttenuationComplete.Broadcast(GetOwner());
			}

		}
	}
}


FAttackAttributeInfo UAttackAttributeComponent::GetAttackAttributeInfo()
{
	FAttackAttributeInfo Info;
	Info.BaseDamage = BaseDamage;
	Info.Element = Element;
	Info.InterruptAblity = InterruptAblity;
	return Info;
}












