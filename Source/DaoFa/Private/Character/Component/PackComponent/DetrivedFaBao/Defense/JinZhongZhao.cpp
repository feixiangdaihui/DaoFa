// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/DetrivedFaBao/Defense/JinZhongZhao.h"
#include "General/CalAttackLibrary.h"
#include "General/CreatureBehavior.h"
#include "Creature.h"
#include "Components/CapsuleComponent.h"
#include "Character/Component/PackComponent/SpellCoolComponent.h"
#include "Character/Component/PackComponent/PODefenseComponent.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"

AJinZhongZhao::AJinZhongZhao()
{
	PODefenseComponent = CreateDefaultSubobject<UPODefenseComponent>(TEXT("PODefenseComponent"));
	EquipmentModeType = EEquipmentModeType::Defense;
	PODefenseComponent->GetHealthComponent()->OnDeath.AddDynamic(this, &AJinZhongZhao::OnDeath);


	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//设置碰撞
	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	CapsuleComponent->SetGenerateOverlapEvents(true);
	RootComponent = CapsuleComponent;


	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	//overlap
	StaticMeshComponent->SetCollisionProfileName(TEXT("NOCollision"));
	StaticMeshComponent->SetGenerateOverlapEvents(true);


	SpellInfo.EquipmentSpellType = EEquipmentSpellType::Continuous;
	SpellInfo.OngoingBlueCostBySecond = 1;
}

void AJinZhongZhao::TriggeredByShortPress()
{
	if (IsSpell)
	{
		AttachToCreature(OwnerCreature);
		OwnerCreature->GetCreatureBehavior()->SetMoveForbid(false);
		IsSpell = false;
	}
	else
	{
		StaticMeshComponent->SetVisibility(true);
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		OwnerCreature->GetCreatureBehavior()->SetMoveForbid(true);
		IsSpell = true;
		SpellCoolComponent->StartCool();
	}
}


void AJinZhongZhao::OnDeath()
{
	OnPackObjectExhausted.Broadcast(this);
	Destroy();
}

void AJinZhongZhao::AttachToCreature(ACreature* Creature)
{
	Super::AttachToCreature(Creature);
	StaticMeshComponent->SetVisibility(false);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IsSpell = false;
}

void AJinZhongZhao::BeAttacked(FAttackReturnValue AttackReturnValue)
{
	PODefenseComponent->GetHealthComponent()->SubtractValue(AttackReturnValue.Damage);
}

FDefenderInfo AJinZhongZhao::GetDefenderInfo()
{
	return UCalAttackLibrary::CreateDefenderInfo(PODefenseComponent->GetDefenseComponent());
}




