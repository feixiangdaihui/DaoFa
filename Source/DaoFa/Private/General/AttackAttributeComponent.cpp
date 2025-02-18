// Fill out your copyright notice in the Description page of Project Settings.


#include "General/AttackAttributeComponent.h"

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





EInterruptType UAttackAttributeComponent::CalculateInterrupt(float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity)
{
	if (ActualDamagePercent >= INTERRUPT_START_PERCENT)
	{
		switch (AvoidAblity)
		{
		case EAvoidInterruptAblity::ABSOLUTE:
			if (InterruptAblity == EInterruptAblity::HEAVY)
				return EInterruptType::PARTIAL;
			else
				return EInterruptType::NONE;
			break;
		case EAvoidInterruptAblity::RELATIVE:
			if (InterruptAblity == EInterruptAblity::HEAVY)
				return EInterruptType::FULL;
			else if (InterruptAblity == EInterruptAblity::LIGHT)
				return EInterruptType::PARTIAL;
			else
				return EInterruptType::NONE;
		case EAvoidInterruptAblity::NONE:
			if (InterruptAblity == EInterruptAblity::NONE)
				return EInterruptType::NONE;
			else
				return EInterruptType::FULL;
			break;
		default:
			return EInterruptType::NONE;
			break;
		}
	}
	else
		return EInterruptType::NONE;
}

float UAttackAttributeComponent::CalculateDamage(float Defense, GElement DefenseElement, float DamageMultiplier)
{
	return 0.0f;
}

//返回值是对方的中断方向
EInterruptDir UAttackAttributeComponent::CalculateInterruptDir(AActor* OtherActor)
{
	if (OtherActor)
	{
		FVector Direction = (GetOwner()->GetActorLocation() - OtherActor->GetActorLocation()).GetSafeNormal();
		FVector Forward = OtherActor->GetActorForwardVector();
		FVector Right = OtherActor->GetActorRightVector();
		FVector Up = OtherActor->GetActorUpVector();

		float ForwardDot = FVector::DotProduct(Direction, Forward);
		float RightDot = FVector::DotProduct(Direction, Right);
		float UpDot = FVector::DotProduct(Direction, Up);

		if (FMath::Abs(UpDot) > FMath::Abs(ForwardDot) && FMath::Abs(UpDot) > FMath::Abs(RightDot))
		{
			return UpDot > 0 ? EInterruptDir::UP : EInterruptDir::DOWN;
		}
		else if (FMath::Abs(RightDot) > FMath::Abs(ForwardDot))
		{
			return RightDot > 0 ? EInterruptDir::RIGHT : EInterruptDir::LEFT;
		}
		else
		{
			return ForwardDot > 0 ? EInterruptDir::FRONT : EInterruptDir::BACK;
		}
	}
	else
		return EInterruptDir::ERROR;
}

FAttackReturnValue UAttackAttributeComponent::CalculateAttack(float Defense, GElement DefenseElement, float DamageMultiplier, float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, AActor* OtherActor)
{
	FAttackReturnValue ReturnValue;
	ReturnValue.Damage = CalculateDamage(Defense, DefenseElement, DamageMultiplier);
	ReturnValue.InterruptDir = CalculateInterruptDir(OtherActor);
	ReturnValue.InterruptType = CalculateInterrupt(ActualDamagePercent, AvoidAblity);
	return ReturnValue;
}







