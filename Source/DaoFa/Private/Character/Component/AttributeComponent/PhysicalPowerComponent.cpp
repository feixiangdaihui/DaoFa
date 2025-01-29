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

void UPhysicalPowerComponent::RunLossPhysicalPower(float DeltaTime)
{
	if (IsRun)
	{
		CurrentPhysicalPower -= RunLossPhysicalPowerAmountBySecond * DeltaTime;
		if (CurrentPhysicalPower < 0)
		{
			CurrentPhysicalPower = 0;
		}
	}
}


bool UPhysicalPowerComponent::LossPhysicalPower(float value)
{
	if (CurrentPhysicalPower >= value)
	{
		CurrentPhysicalPower -= value;
		return true;
	}
	return false;
}

// Called every frame
void UPhysicalPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RecoverPhysicalPowerBySecond(DeltaTime);
	RunLossPhysicalPower(DeltaTime);
	if (JumpLockTimer > 0)
	{
		JumpLockTimer -= DeltaTime;
	}

	// ...
}

bool UPhysicalPowerComponent::UpdateInput(InputAnimation Input, int val)
{
	
	switch (Input)
	{
	case::InputAnimation::Idle:
		IsRun = false;
		break;
	case::InputAnimation::Walk:
		IsRun = false;
		break;
	case::InputAnimation::EndRun:
		IsRun = false;
		break;
	case InputAnimation::Run:
		if (IsEmpty())
		{
			return false;
		}
		IsRun = true;
		break;
	case InputAnimation::Jump:
		if (JumpLockTimer > 0)
			return false;
		if (LossPhysicalPower(JumpLoss))
		{
			JumpLockTimer = JumpLockTime;
			return true;
		}
		break;
	case InputAnimation::Dodge:
		return LossPhysicalPower(DodgeLoss);
		break;
	default:
		break;
	}
	return true;
}

