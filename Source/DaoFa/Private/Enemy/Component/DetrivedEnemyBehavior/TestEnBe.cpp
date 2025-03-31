// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Component/DetrivedEnemyBehavior/TestEnBe.h"
#include "Enemy/Component/EnemyPackComponent.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "Enemy/BaseEnemy.h"
#include "Creature.h"
#include "General/CreatureBehavior.h"

void UTestEnBe::BehaveWhenTargetIsFrontFar()
{
	if (PackComponent && CreatureBehavior)
	{
		APackObject* PackObject = PackComponent->GetPackObjectByTypeAndIndex(EEquipmentType::FABAO, TestFrontFarFaBaoIndex);
		if(PackObject)
		{
			CreatureBehavior->Spell(PackObject, 0.5f);
		}
	}
}

void UTestEnBe::BehaveWhenTargetIsFrontNear()
{
	if (PackComponent && CreatureBehavior)
	{
		APackObject* PackObject = PackComponent->GetPackObjectByTypeAndIndex(EEquipmentType::FASHU, TestFrontNearFaShuIndex);
		if (PackObject)
		{
			CreatureBehavior->Spell(PackObject, 1.0f);
		}
	}
}

void UTestEnBe::BehaveWhenTargetIsBackNear()
{
	if (PackComponent && CreatureBehavior)
	{
		APackObject* PackObject = PackComponent->GetPackObjectByTypeAndIndex(EEquipmentType::FABAO, TestBackNearrFaBaoIndex);
		if (PackObject)
		{
			CreatureBehavior->Spell(PackObject, 10.0f);
		}
	}
}

void UTestEnBe::BeginPlay()
{
	Super::BeginPlay();

}

UTestEnBe::UTestEnBe()
{
	PrimaryComponentTick.bCanEverTick = true;
	BehaveFrontFarTime = 5.0f;
	BehaveFrontNearTime = 5.0f;
	BehaveBackNearTime = 15.0f;
}
