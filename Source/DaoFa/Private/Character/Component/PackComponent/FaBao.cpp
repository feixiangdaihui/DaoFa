// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/FaBao.h"


// Sets default values
AFaBao::AFaBao()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	EquipmentType = EEquipmentType::FABAO;





}

// Called when the game starts or when spawned
void AFaBao::BeginPlay()
{
	Super::BeginPlay();
}

void AFaBao::TriggeredByLongPress()
{
	Super::TriggeredByLongPress();
	CanBeWearOrTakeOff = false;
}

void AFaBao::TriggeredByShortPress()
{
	Super::TriggeredByShortPress();
	CanBeWearOrTakeOff = false;
}

// Called every frame
void AFaBao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFaBao::AttachToCreature(ACreature* Creature)
{
	Super::AttachToCreature(Creature);
	CanBeWearOrTakeOff = true;
}



