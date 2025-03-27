// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackObject.h"
#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Character/BaseCharacter.h"
#include "General/AttackAttributeComponent.h"
#include "Character/Component/PackComponent/SpellCoolComponent.h"
#include"General/StateComponent.h"
#include "Character/Component/PackComponent/PODefenseComponent.h"
#include "General/DefenseComponent.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
// Sets default values
APackObject::APackObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BlueCostComponent = CreateDefaultSubobject<UBlueCostComponent>(TEXT("BlueCostComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	SpellCoolComponent = CreateDefaultSubobject<USpellCoolComponent>(TEXT("SpellCoolComponent"));
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

void APackObject::AttachToCreature(ACreature* Creature)
{
	AttachToActor(Creature, FAttachmentTransformRules::SnapToTargetIncludingScale);
	OwnerCreature = Creature;
}

bool APackObject::TriggeredBegin()
{
	CanBeWearOrTakeOff = false;
	if (SpellCoolComponent->IsCoolingNow())
	{
		return false;
	}


	if (!IsLongPressPermit )
	{
		BlueCostComponent->OngoingCostBlue();
		TriggeredByShortPress();
		LongPressTimeCounter = GetWorld()->GetTimeSeconds();
		return true;
	}

	if (BlueCostComponent->ShortPressCostBlue())
	{
		LongPressTimeCounter = GetWorld()->GetTimeSeconds();
		return true;
	}
	else
		return false;
}

bool APackObject::TriggeredEnd()
{
	CanBeWearOrTakeOff = true;

	if (LongPressTimeCounter == 0)
		return false;


	if (!IsLongPressPermit)
	{
		TriggeredByShortPress();
		BlueCostComponent->EndOngoingCostBlue();
	}
	else
	{
		LongPressTimeCounter = GetWorld()->GetTimeSeconds() - LongPressTimeCounter;
		if (LongPressTimeCounter > LongPressTime && BlueCostComponent->LongPressCostBlue())
		{
			TriggeredByLongPress();
		}
		else if (IsShortPressPermit)
			TriggeredByShortPress();
		else
		{
			LongPressTimeCounter = 0;
			return false;
		}
	}
	LongPressTimeCounter = 0;
	return true;
}




FPackObjectInfo APackObject::GetPackObjectInfo() const 
{
	FPackObjectInfo PackObjectInfo;
	PackObjectInfo.Icon = Icon;
	PackObjectInfo.Name = Name;
	PackObjectInfo.Description = Description;
	PackObjectInfo.Quantity = Quantity;
	PackObjectInfo.SizeInPack = SizeInPack;
	PackObjectInfo.EquipmentType = EquipmentType;
	PackObjectInfo.EquipmentModeType = EquipmentModeType;
	if (IsValid(AttackAttributeComponent))
	{
		PackObjectInfo.AttackAttributeInfo = AttackAttributeComponent->GetAttackAttributeInfo();
	}
	if (IsValid(PODefenseComponent))
	{
		PackObjectInfo.DefenseAttributeInfo = PODefenseComponent->GetDefenseComponent()->GetDefenseAttributeInfo();
		PackObjectInfo.MaxHealth = PODefenseComponent->GetHealthComponent()->GetMaxValue();
		PackObjectInfo.CurrentHealth = PODefenseComponent->GetHealthComponent()->GetCurrentValue();

	}
	return PackObjectInfo;
}

