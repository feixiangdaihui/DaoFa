// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/POAttackAttributeComponent.h"



FAttackReturnValue UPOAttackAttributeComponent::CalculateLongPressAttack(float Defense, GElement DefenseElement, float DamageMultiplier, float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, AActor* OtherActor)
{
	return CalculateAttack(Defense, DefenseElement, DamageMultiplier*LongPressDamageMultiplier, ActualDamagePercent, AvoidAblity, OtherActor);
}

FAttackReturnValue UPOAttackAttributeComponent::CalculateShortPressAttack(float Defense, GElement DefenseElement, float DamageMultiplier, float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, AActor* OtherActor)
{
	return CalculateAttack(Defense, DefenseElement, DamageMultiplier * ShortPressDamageMultiplier, ActualDamagePercent, AvoidAblity, OtherActor);
}
