// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/FaBao.h"


// Sets default values
AFaBao::AFaBao()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	EquipmentType = EEquipmentType::FABAO;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	





}

// Called when the game starts or when spawned
void AFaBao::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFaBao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFaBao::AttachToCharacter(ABaseCharacter* Character)
{
	Super::AttachToCharacter(Character);
	//设置骨骼体不可见
	SkeletalMeshComponent->SetVisibility(false);
}

