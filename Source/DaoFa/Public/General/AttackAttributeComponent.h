// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "General/ElementSetting.h"
#include "AttackAttributeComponent.generated.h"

const float INTERRUPT_START_PERCENT = 1.0f;
UENUM()
enum class EInterruptType
{
	FULL,
	PARTIAL,
	NONE
};

UENUM()
enum class EInterruptDir
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	FRONT,
	BACK,
	ERROR
};

UENUM()
enum class EInterruptAblity
{
	HEAVY,
	LIGHT,
	NONE
};

UENUM()
enum class EAvoidInterruptAblity
{
	ABSOLUTE,
	RELATIVE,
	NONE
};

USTRUCT()
struct FAttackReturnValue
{
	GENERATED_BODY()
public:
	float Damage;
	EInterruptType InterruptType;
	EInterruptDir InterruptDir;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UAttackAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackAttributeComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float BaseDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackMutiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float CriticalHitChance = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float CriticalHitMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	GElement Element = GElement::Matel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	EInterruptAblity InterruptAblity = EInterruptAblity::NONE;

public:
	EInterruptType CalculateInterrupt(float ActualDamagePercent,EAvoidInterruptAblity AvoidAblity);
	
	virtual float CalculateDamage(float Defense, GElement DefenseElement, float DamageMultiplier);
	
	EInterruptDir CalculateInterruptDir(AActor* OtherActor);

	virtual FAttackReturnValue CalculateAttack(float Defense, GElement DefenseElement, float DamageMultiplier, float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, AActor* OtherActor);


};
