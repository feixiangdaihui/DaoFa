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
	if (IsRun)
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
	if (DodgeLockTimer > 0)
	{
		DodgeLockTimer -= DeltaTime;
	}
	if (RunLockTimer > 0)
	{
		RunLockTimer -= DeltaTime;
	}

	// ...
}

void UPhysicalPowerComponent::UpdateInput(InputAnimation Input)
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
		IsRun = true;
		break;
	case InputAnimation::Jump:

		LossPhysicalPower(JumpLoss);
		JumpLockTimer = JumpLockTime;
		break;
	case InputAnimation::Dodge:
		LossPhysicalPower(DodgeLoss);
		DodgeLockTimer = DodgeLockTime;
		break;
	default:
		break;
	}
}

bool UPhysicalPowerComponent::CheckInput(InputAnimation Input)
{
	switch (Input)
	{
	case InputAnimation::Run:
		if (IsEmpty())
		{
			RunLockTimer = RunLockTime;
			return false;
		}
		if (RunLockTimer > 0)
			return false;
		break;
	case InputAnimation::Jump:
		if (JumpLockTimer > 0)
			return false;
		if (CurrentPhysicalPower < JumpLoss)
			return false;
		break;
	case InputAnimation::Dodge:
		if (DodgeLockTimer > 0)
			return false;
		if (CurrentPhysicalPower < DodgeLoss)
			return false;
		break;
	default:
		break;
	}
	return true;
}


