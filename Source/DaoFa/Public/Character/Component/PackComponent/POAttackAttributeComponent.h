// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/AttackAttributeComponent.h"
#include "POAttackAttributeComponent.generated.h"

/**
 * 
 */
UCLASS()
class DAOFA_API UPOAttackAttributeComponent : public UAttackAttributeComponent
{
	GENERATED_BODY()
	friend class APackObject;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float ShortPressDamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float LongPressDamageMultiplier = 1.5f;
public:
	FAttackReturnValue CalculateLongPressAttack(float Defense, GElement DefenseElement, float DamageMultiplier, float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, AActor* OtherActor);

	FAttackReturnValue CalculateShortPressAttack(float Defense, GElement DefenseElement, float DamageMultiplier, float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, AActor* OtherActor);
};
