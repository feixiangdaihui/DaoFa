// Fill out your copyright notice in the Description page of Project Settings.


#include "General/CalAttackLibrary.h"
#include"Creature.h"
#include "General/DefenseComponent.h"
#include"General/AttackAttributeComponent.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "General/ElementSetting.h"
#include "Character/Component/PackComponent/PODefenseComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"


bool UCalAttackLibrary::IsTest = false;

EInterruptType UCalAttackLibrary::CalculateInterrupt(EInterruptAblity InterruptAblity,float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, float StartToBeInterruptedPercent)
{
	if (ActualDamagePercent >= StartToBeInterruptedPercent)
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

float UCalAttackLibrary::CalculateDamage(APackObject* SelfPackObejct, ACreature* OtherCreature, float DamageMultiplier)
{
	return CalculateDamage(SelfPackObejct, OtherCreature->GetDefenseComponent(), OtherCreature->GetStateComponent()->GetState(), DamageMultiplier);
	
}

float UCalAttackLibrary::CalculateDamage(APackObject* SelfPackObejct, UDefenseComponent* DefenseComponent, FState OtherState, float DamageMultiplier)
{
	
	UPOAttackAttributeComponent* POAttackAttributeComponent = SelfPackObejct->GetPOAttackAttributeComponent();
	float BaseDamage = POAttackAttributeComponent->BaseDamage;
	GElement DefenseElement = DefenseComponent->DefenseElement;
	FState PackObjectState = SelfPackObejct->GetStateComponent()->GetState();
	FState OwnerState = SelfPackObejct->GetOwnerCreature()->GetStateComponent()->GetState();
	float Defense = DefenseComponent->Defense;
	float ElementMultiplier = UElementSetting::GetElementRestrainMultiplier(POAttackAttributeComponent->Element, DefenseElement);
	float OtherStateMultiplier = UStateComponent::CalCreatureStateDamageMultiplier(PackObjectState, OtherState);
	float OwnerStateMultiplier = UStateComponent::CalItemCreatureStateDamageMultiplier(OwnerState, PackObjectState);
	float BlueDensity = 0.0f;
	ACreature* OwnerCreature = SelfPackObejct->GetOwnerCreature();
	if (OwnerCreature)
		BlueDensity = OwnerCreature->GetBlueComponent()->GetBlueDensity();
	float Damage = BaseDamage * DamageMultiplier * ElementMultiplier / Defense * OtherStateMultiplier * OwnerStateMultiplier*BlueDensity;

	if (IsTest)
		UE_LOG(LogTemp, Warning, TEXT("BaseDamage:%f,DamageMultiplier:%f,ElementMultiplier:%f,Defense:%f,OtherStateMultiplier:%f,OwnerStateMultiplier:%f,BlueDensity:%f,Damage:%f"), BaseDamage, DamageMultiplier, ElementMultiplier, Defense, OtherStateMultiplier, OwnerStateMultiplier, BlueDensity, Damage);
	return Damage;
}



//返回值是对方的中断方向
EInterruptDir UCalAttackLibrary::CalculateInterruptDir(AActor* SelfActor,AActor* OtherActor)
{
	if (OtherActor)
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



FAttackReturnValue UCalAttackLibrary::CalculateAttack( APackObject* SelfPackObejct, ACreature* OtherCreature,  float DamageMultiplier)
{
	return CalculateAttack(SelfPackObejct, OtherCreature->GetDefenseComponent(), OtherCreature->GetStateComponent()->GetState(), OtherCreature->GetHealthComponent(), DamageMultiplier);
}

FAttackReturnValue UCalAttackLibrary::CalculateAttack(APackObject* SelfPackObejct, UDefenseComponent* DefenseComponent, FState OtherState, UHealthComponent* HealthComponent, float DamageMultiplier)
{
	if (!SelfPackObejct || !DefenseComponent || !HealthComponent)
	{
		return FAttackReturnValue();
	}
	if (SelfPackObejct->GetEquipmentModeType() == EEquipmentModeType::Defense)
	{
		return FAttackReturnValue();
	}

	FAttackReturnValue ReturnValue;
	UPOAttackAttributeComponent* POAttackAttributeComponent = SelfPackObejct->GetPOAttackAttributeComponent();
	ReturnValue.Damage = CalculateDamage(SelfPackObejct, DefenseComponent,OtherState, DamageMultiplier);
	ReturnValue.InterruptDir = CalculateInterruptDir(SelfPackObejct, DefenseComponent->GetOwner());
	ReturnValue.InterruptType = CalculateInterrupt(POAttackAttributeComponent->InterruptAblity, ReturnValue.Damage / HealthComponent->GetMaxValue(), DefenseComponent->AvoidAblity, DefenseComponent->StartToBeInterruptedPercent);
	if (IsTest)
		UE_LOG(LogTemp, Warning, TEXT("Damage:%f,InterruptType:%d,InterruptDir:%d"), ReturnValue.Damage, ReturnValue.InterruptType, ReturnValue.InterruptDir);
	return ReturnValue;

}

FAttackReturnValue UCalAttackLibrary::CalculateAttack(APackObject* SelfPackObejct, UPODefenseComponent* DefenseComponent, FState OtherState, float DamageMultiplier)
{
	return CalculateAttack(SelfPackObejct, DefenseComponent->GetDefenseComponent(), OtherState, DefenseComponent->GetHealthComponent(), DamageMultiplier);
}
