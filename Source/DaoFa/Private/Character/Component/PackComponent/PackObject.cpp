// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackObject.h"
#include "Creature.h"
#include "Character/Component/PackComponent/SpellCoolComponent.h"
#include"General/StateComponent.h"
// Sets default values
APackObject::APackObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	SpellCoolComponent = CreateDefaultSubobject<USpellCoolComponent>(TEXT("SpellCoolComponent"));

}


// Called every frame
void APackObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APackObject::AttachToCreature(ACreature* Creature)
{
	SetOwner(Creature);
	AttachToActor(Creature, FAttachmentTransformRules::SnapToTargetIncludingScale);
	OwnerCreature = Creature;
}

void APackObject::AttachToCreatureByActor(AActor* Actor)
{
	ACreature* Temp = Cast<ACreature>(Actor);
	if (!Temp)
	{
		AttachToActor(Actor, FAttachmentTransformRules::SnapToTargetIncludingScale);
		SetOwner(Actor);
		//打印类名
		UE_LOG(LogTemp, Warning, TEXT("AttachToCreatureByActor %s ,NULL"), *Actor->GetClass()->GetName());
	}
	AttachToCreature(Temp);
}

