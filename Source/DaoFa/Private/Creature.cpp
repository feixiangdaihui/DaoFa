// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "Character/Component/AttributeComponent/AttributeComponent.h"
#include "Character/Component/PackComponent/PackComponent.h"
#include "General/DefenseComponent.h"
#include "General/StateComponent.h"
#include"General/CalAttackLibrary.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"

// Sets default values
ACreature::ACreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	PackComponent = CreateDefaultSubobject<UPackComponent>(TEXT("PackComponent"));
	DefenseComponent = CreateDefaultSubobject<UDefenseComponent>(TEXT("DefenseComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
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

void ACreature::BeAttacked(APackObject* PackObject, float DamageMultiplier)
{
	FAttackReturnValue ReturnValue = UCalAttackLibrary::CalculateAttack(PackObject, this, DamageMultiplier);
	AttributeComponent->GetHealthComponent()->SubtractValue(ReturnValue.Damage);

}



