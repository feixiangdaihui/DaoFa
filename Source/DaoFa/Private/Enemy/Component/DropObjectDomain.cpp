// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Component/DropObjectDomain.h"
#include "Components/SphereComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/PackComponent/PackObject.h"
#include"Character/Component/PackComponent/PackComponent.h"
// Sets default values
ADropObjectDomain::ADropObjectDomain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ADropObjectDomain::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADropObjectDomain::OnOverlapBegin);
}

// Called every frame
void ADropObjectDomain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropObjectDomain::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor);
	if (Character)
	{
		for (auto ObjectClass : DropObjects)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = Character;
			APackObject* PackObject = GetWorld()->SpawnActor<APackObject>(ObjectClass, Character->GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
			PackObject->AttachToCharacter(Character);
			Character->PackComponent->WearEquipment(PackObject);
		}
	}
}

