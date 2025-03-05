// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/DetrivedFaBao/Defense/JinZhongZhao.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "General/CalAttackLibrary.h"
#include "General/DefenseComponent.h"
#include "General/CreatureBehavior.h"
#include "Creature.h"
#include "Character/Component/PackComponent/BlueCostComponent.h"
#include "Components/CapsuleComponent.h"


AJinZhongZhao::AJinZhongZhao()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//设置碰撞
	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	CapsuleComponent->SetGenerateOverlapEvents(true);
	RootComponent = CapsuleComponent;


	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	//overlap
	StaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	StaticMeshComponent->SetGenerateOverlapEvents(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	//绑定死亡事件
	HealthComponent->OnDeath.AddDynamic(this, &AJinZhongZhao::OnDeath);

	DefenseComponent = CreateDefaultSubobject<UDefenseComponent>(TEXT("DefenseComponent"));

	IsLongPressPermit = false;

	BlueCostComponent->OngoingMode = true;
	BlueCostComponent->OngoingBlueCost = 0.2;
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

void AJinZhongZhao::BeAttacked(APackObject* PackObject, float DamageMultiplier)
{
	FAttackReturnValue ReturnValue = UCalAttackLibrary::CalculateAttack(PackObject, DefenseComponent, StateComponent->GetState(), HealthComponent, DamageMultiplier);
	HealthComponent->SubtractValue(ReturnValue.Damage);
	
}


