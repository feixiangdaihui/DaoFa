// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "General/DefenseComponent.h"
#include "General/StateComponent.h"
#include"General/CalAttackLibrary.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "General/CreatureBehavior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"
#include "Character/Component/GongFa/GongFaComponent.h"


// Sets default values
ACreature::ACreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));
	PhysicalPowerComponent = CreateDefaultSubobject<UPhysicalPowerComponent>(TEXT("PhysicalPowerComponent"));


	DefenseComponent = CreateDefaultSubobject<UDefenseComponent>(TEXT("DefenseComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	CreatureBehavior = CreateDefaultSubobject<UCreatureBehavior>(TEXT("CreatureBehavior"));
	StateComponent->InitStateComponent(BlueComponent);

	GongFaComponent = CreateDefaultSubobject<UGongFaComponent>(TEXT("GongFaComponent"));
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float ACreature::BeAttacked(FAttackReturnValue AttackReturnValue)
{
	float Percent = HealthComponent->GetCurrentValue()/ AttackReturnValue.Damage  ;
	HealthComponent->SubtractValue(AttackReturnValue.Damage);
	return FMath::Clamp(Percent, 0.0f, 1.0f);
}

FDefenderInfo ACreature::GetDefenderInfo()
{
	return UCalAttackLibrary::CreateDefenderInfo(DefenseComponent);
}

void ACreature::SetSpeedToWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACreature::SetSpeedToRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACreature::SetUnbeatable(bool NewValue)
{
	HealthComponent->CanBeHurt = !NewValue;
}



