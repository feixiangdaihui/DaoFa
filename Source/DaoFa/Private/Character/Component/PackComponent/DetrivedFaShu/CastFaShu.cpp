// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/DetrivedFaShu/CastFaShu.h"
#include "Character/Component/PackComponent/DetrivedFaShu/CastFaShuProjectile.h"
#include "General/EnemyDetector.h"
#include "Creature.h"
ACastFaShu::ACastFaShu()
{
	
	EnemyDetector = CreateDefaultSubobject<UEnemyDetector>(TEXT("EnemyDetector"));
	EnemyDetector->DetectionRadius = 3000;
	EnemyDetector->HorizontalAngle = 360;
	EnemyDetector->VerticalAngle = 360;

	EnemyDetector->EnemyClasses.Empty();
	EnemyDetector->EnemyClasses.Add(ACreature::StaticClass());

	//需要蓄力，只有长按才能发射
	IsShortPressPermit = false;

	StartLocation = FVector(0, 0, 0);
	

}


void ACastFaShu::BaseCastSpell()
{
	if (CastFaShuProjectileClass)
	{
		ACastFaShuProjectile* CastFaShuProjectile = GetWorld()->SpawnActor<ACastFaShuProjectile>(CastFaShuProjectileClass, GetOwner()->GetActorLocation()+StartLocation, FRotator::ZeroRotator);
		if (CastFaShuProjectile)
		{
			FVector EndLocation;
			if(FindTarget())
				EndLocation = FindTarget()->GetActorLocation();
			else
				EndLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * SpellMaxDistance;
			CastFaShuProjectile->BeginSpell(EndLocation, SpellSpeed,SpellMaxDistance);
			CastFaShuProjectile->OnProjectileHit.AddDynamic(this, &ACastFaShu::OnOverlapBegin);
		}
	}
}

AActor* ACastFaShu::FindTarget()
{
	TArray<AActor*> Enemys=EnemyDetector->DetectEnemies();
	for (auto Enemy :Enemys)
	{
		if (Enemy != GetOwner())
		{
			return Enemy;
		}

	}
	return nullptr;
}

void ACastFaShu::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	ACreature* Creature = Cast<ACreature>(OtherActor);
	if (Creature)
	{
		Creature->BeAttacked(this, DamageMutiplier);
	}
}


void ACastFaShu::TriggeredByLongPress()
{
	IsSpell = true;
	GetWorldTimerManager().SetTimer(SpellTimerHandle, [this]() {
		if (SpellNumberCounter++ == SpellNumber)
		{
			IsSpell = false;
			SpellNumberCounter = 0;
			GetWorldTimerManager().ClearTimer(SpellTimerHandle);
		}
		else
		{
			BaseCastSpell();
		}}, SpellInterval, true);
}
