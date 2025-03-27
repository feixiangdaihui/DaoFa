// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/DetrivedFaShu/CastFaShu.h"
#include "Character/Component/PackComponent/DetrivedFaShu/CastFaShuProjectile.h"
#include "General/EnemyDetector.h"
#include "Creature.h"
#include "Character/Component/PackComponent/SpellCoolComponent.h"
ACastFaShu::ACastFaShu()
{
	AttackAttributeComponent = CreateDefaultSubobject<UAttackAttributeComponent>(TEXT("AttackAttributeComponent"));
	EquipmentModeType = EEquipmentModeType::Attack;


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
			CastFaShuProjectile->BeginSpell(EndLocation, SpellSpeed, SpellMaxDistance, UCalAttackLibrary::CreateAttackerInfo(AttackAttributeComponent));
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

void ACastFaShu::OnOverlapBegin(ACastFaShuProjectile* FaShuProjectile, AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		FaShuProjectile->Explode(SweepResult.ImpactPoint);
		return;
	}
	IBeAttacked* BeAttacked = Cast<IBeAttacked>(OtherActor);
	if (BeAttacked)
	{
		AttackAttributeComponent->AttackByAttackerInfo(FaShuProjectile->GetAttackerInfo(), BeAttacked);
		return;
	}
	IAttacker* Attacker = Cast<IAttacker>(OtherActor);
	if (Attacker)
	{
		EAttackCompareType CompareType = UCompareAttackLibrary::CompareAttack(FaShuProjectile, Attacker);
		if (CompareType!=EAttackCompareType::GREATER)
		{
			FaShuProjectile->Destroy();
		}
		return;
	}
	
}




void ACastFaShu::TriggeredByLongPress()
{
	SpellCoolComponent->StartCool();
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
