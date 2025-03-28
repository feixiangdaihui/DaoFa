// Fill out your copyright notice in the Description page of Project Settings.


#include "General/CalAttackLibrary.h"
#include"Creature.h"
#include "General/DefenseComponent.h"
#include"General/AttackAttributeComponent.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "General/ElementSetting.h"
#include "Character/Component/PackComponent/PODefenseComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Character/Component/PackComponent/PackObject.h"



bool UCalAttackLibrary::IsTest = false;

EInterruptType UCalAttackLibrary::CalculateInterrupt(EInterruptAblity InterruptAblity, EAvoidInterruptAblity AvoidAblity)
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

float UCalAttackLibrary::CalculateDamage(FAttackerInfo AttackerInfo, FDefenderInfo DefenderInfo)
{

	float ElementRestrainMultiplier = UElementSetting::GetElementRestrainMultiplier(AttackerInfo.Element, DefenderInfo.Element);
	float StateDamageMultiplier = UStateComponent::CalCreatureStateDamageMultiplier(AttackerInfo.State, DefenderInfo.State);
	float AttackNum = CalculateAttackNum(AttackerInfo);
	float DefenseNum = CalculateDefenseNum(DefenderInfo);
	float Result = AttackNum * ElementRestrainMultiplier * StateDamageMultiplier / DefenseNum;
	return Result;
}

float UCalAttackLibrary::CalculateAttackNum(FAttackerInfo AttackerInfo)
{
	float BaseDamage = AttackerInfo.BaseDamage;
	float DamageMultiplier = AttackerInfo.DamageMultiplier;
	float BlueDensity = AttackerInfo.BlueDensity;
	float StateDamageMultiplier = UStateComponent::CalCreatureStateDamageMultiplier(AttackerInfo.State, AttackerInfo.OwnerState);
	return BaseDamage * DamageMultiplier * StateDamageMultiplier * BlueDensity;
}

float UCalAttackLibrary::CalculateDefenseNum(FDefenderInfo DefenderInfo)
{
	float Defense = DefenderInfo.Defense;
	return Defense;
}



//返回值是对方的中断方向
EInterruptDir UCalAttackLibrary::CalculateInterruptDir(AActor* SelfActor,AActor* OtherActor)
{
	if (OtherActor&&SelfActor)
	{
		FVector Direction = (SelfActor->GetActorLocation() - OtherActor->GetActorLocation()).GetSafeNormal();
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


FAttackReturnValue UCalAttackLibrary::CalculateAttack(FAttackerInfo AttackerInfo, FDefenderInfo DefenderInfo)
{
	FAttackReturnValue ReturnValue;
	ReturnValue.Damage = CalculateDamage(AttackerInfo, DefenderInfo);
	ReturnValue.InterruptDir = CalculateInterruptDir(AttackerInfo.Attacker, DefenderInfo.Defender);
	ReturnValue.InterruptType = CalculateInterrupt(AttackerInfo.InterruptAblity, DefenderInfo.AvoidAblity);
	if (IsTest)
		UE_LOG(LogTemp, Warning, TEXT("Damage:%f,InterruptType:%d,InterruptDir:%d"), ReturnValue.Damage, ReturnValue.InterruptType, ReturnValue.InterruptDir);
	return ReturnValue;

}

FAttackerInfo UCalAttackLibrary::CreateAttackerInfo(UAttackAttributeComponent* AttackAttributeComponent)
{
	FAttackerInfo AttackerInfo;
	AttackerInfo.BaseDamage = AttackAttributeComponent->BaseDamage;
	AttackerInfo.DamageMultiplier = AttackAttributeComponent->DamageMultiplier;
	AttackerInfo.Element = AttackAttributeComponent->Element;
	AttackerInfo.InterruptAblity = AttackAttributeComponent->InterruptAblity;
	AActor* Owner = AttackAttributeComponent->GetOwner();
	AttackerInfo.Attacker = Owner;
	if (Owner)
	{
		
		APackObject* PackObject = Cast<APackObject>(Owner);
		if (PackObject)
		{
			AttackerInfo.State = PackObject->GetStateComponent()->GetState();
			AttackerInfo.OwnerState = PackObject->GetOwnerCreature()->GetStateComponent()->GetState();
			AttackerInfo.BlueDensity = PackObject->GetOwnerCreature()->GetBlueComponent()->GetBlueDensity();
		}

	}
	return AttackerInfo;
}

FDefenderInfo UCalAttackLibrary::CreateDefenderInfo(UDefenseComponent* DefenseComponent)
{
	FDefenderInfo DefenderInfo;
	DefenderInfo.Defense = DefenseComponent->Defense;
	DefenderInfo.Element = DefenseComponent->DefenseElement;
	DefenderInfo.AvoidAblity = DefenseComponent->AvoidAblity;
	AActor* Owner = DefenseComponent->GetOwner();
	DefenderInfo.Defender = Owner;
	if (Owner)
	{
		ACreature* Creature = Cast<ACreature>(Owner);
		if (Creature)
		{
			DefenderInfo.State = Creature->GetStateComponent()->GetState();
		}
		else
		{
			APackObject* PackObject = Cast<APackObject>(Owner);
			if (PackObject)
			{
				DefenderInfo.State = PackObject->GetStateComponent()->GetState();
			}
		}
	}
	return DefenderInfo;
}



