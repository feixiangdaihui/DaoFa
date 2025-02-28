// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackObject.h"
#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/PackComponent/POAttackAttributeComponent.h"
#include"General/StateComponent.h"
// Sets default values
APackObject::APackObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlueCostComponent = CreateDefaultSubobject<UBlueCostComponent>(TEXT("BlueCostComponent"));
	POAttackAttributeComponent = CreateDefaultSubobject<UPOAttackAttributeComponent>(TEXT("AttackAttributeComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
}

// Called when the game starts or when spawned
void APackObject::BeginPlay()
{
	Super::BeginPlay();
	OwnerCreature = Cast<ACreature>(GetOwner());
	if (!OwnerCreature)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerCreature is nullptr"));
	}
	

}

// Called every frame
void APackObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APackObject::AttachToCharacter(ACreature* Creature)
{
	AttachToActor(Creature, FAttachmentTransformRules::SnapToTargetIncludingScale);
	OwnerCreature = Creature;
}




FPackObjectInfo APackObject::GetPackObjectInfo()
{
	FPackObjectInfo PackObjectInfo;
	PackObjectInfo.Icon = Icon;
	PackObjectInfo.Name = Name;
	PackObjectInfo.Description = Description;
	PackObjectInfo.Quantity = Quantity;
	PackObjectInfo.SizeInPack = SizeInPack;
	PackObjectInfo.EquipmentType = EquipmentType;
	PackObjectInfo.BaseDamage = POAttackAttributeComponent->BaseDamage;
	PackObjectInfo.AttackMutiplier = POAttackAttributeComponent->AttackMutiplier;
	PackObjectInfo.CriticalHitChance = POAttackAttributeComponent->CriticalHitChance;
	PackObjectInfo.CriticalHitMultiplier = POAttackAttributeComponent->CriticalHitMultiplier;
	PackObjectInfo.Element = POAttackAttributeComponent->Element;
	PackObjectInfo.InterruptAblity = POAttackAttributeComponent->InterruptAblity;
	PackObjectInfo.ShortPressDamageMultiplier = POAttackAttributeComponent->ShortPressDamageMultiplier;
	PackObjectInfo.LongPressDamageMultiplier = POAttackAttributeComponent->LongPressDamageMultiplier;
	return PackObjectInfo;
}
