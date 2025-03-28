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
			CreatureBehavior->Spell(PackObject, true);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PackObject]()
				{
					CreatureBehavior->Spell(PackObject, false);
				}, 0.5f, false);
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
			CreatureBehavior->Spell(PackObject, true);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PackObject]()
				{
					CreatureBehavior->Spell(PackObject, false);
				}, 1.5f, false);
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
			CreatureBehavior->Spell(PackObject, true);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PackObject]()
				{
					CreatureBehavior->Spell(PackObject, false);
				}, 10.0f, false);
		}
	}
}

void UTestEnBe::BeginPlay()
{
	Super::BeginPlay();
	ACreature* Owner = Cast<ACreature>(GetOwner());
	if (Owner)
	{
		PackComponent = Cast<UEnemyPackComponent>(Owner->GetPackComponent());
		CreatureBehavior = Owner->GetCreatureBehavior();
		if(!PackComponent)
			UE_LOG(LogTemp, Warning, TEXT("%s PackComponent is nullptr"), *Owner->GetName());
		if (!CreatureBehavior)
			UE_LOG(LogTemp, Warning, TEXT("%s CreatureBehavior is nullptr"), *Owner->GetName());
	}
}
