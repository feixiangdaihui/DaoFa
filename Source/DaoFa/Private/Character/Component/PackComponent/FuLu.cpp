// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/FuLu.h"

// Sets default values
AFuLu::AFuLu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EquipmentType = EEquipmentType::FULU;
}

// Called when the game starts or when spawned
void AFuLu::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuLu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

