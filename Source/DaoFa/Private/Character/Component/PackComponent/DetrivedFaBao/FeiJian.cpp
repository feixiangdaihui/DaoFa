// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/DetrivedFaBao/FeiJian.h"
#include "General/EnemyDetector.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Creature.h"
AFeiJian::AFeiJian()
{
	LongPressEnemyDetector = CreateDefaultSubobject<UEnemyDetector>(TEXT("LongPressEnemyDetector"));
	LongPressEnemyDetector->DetectionRadius = 3000;
	LongPressEnemyDetector->HorizontalAngle = 360;
	LongPressEnemyDetector->VerticalAngle = 360;
	ShortPressEnemyDetector = CreateDefaultSubobject<UEnemyDetector>(TEXT("ShortPressEnemyDetector"));
	ShortPressEnemyDetector->DetectionRadius = 3000;
	ShortPressEnemyDetector->HorizontalAngle = 360;
	ShortPressEnemyDetector->VerticalAngle = 360;


	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionProfileName(TEXT("Trigger"));
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AFeiJian::OnOverlapBegin);

	//将胶囊体设置为根组件
	RootComponent = CapsuleComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	ProjectileMovementComponent->MaxSpeed = 3000;
	//取消重力
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	
	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetEnableGravity(false);
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetEnableGravity(false);


}

void AFeiJian::AttachToCharacter(ACreature* Creature)
{
	Super::AttachToCharacter(Creature);
	StaticMeshComponent->SetVisibility(false);
	IsInHand = true;
	IsGoHome = false;
	IsSpell = false;
	IsShortPressHurt = false;
	IsLongPressHurt = false;
}


void AFeiJian::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComponent->Deactivate();
}

void AFeiJian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSpell)
	{
		//计算飞剑飞行距离
		float Distance = (StartLocation - GetActorLocation()).Size();
		if (Distance > MaxSpellDistance)
		{
			IsSpell = false;
			EndSpell();
		}
	}
}


void AFeiJian::TriggeredByShortPress()
{
	Super::TriggeredByShortPress();
	TArray<AActor*> DetectedEnemies;
	if (IsInHand)
	{
		//移动到角色面前
		FVector NewLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 150;
		SetActorLocation(NewLocation);
		StaticMeshComponent->SetVisibility(true);

		IsInHand = false;

		
	}
	DetectedEnemies = ShortPressEnemyDetector->DetectEnemies();
	FVector EndLocation = GetActorLocation() + GetActorForwardVector() * 1000;
	for (auto Enemy : DetectedEnemies)
	{
		if (Enemy != GetOwner())
		{
			EndLocation = Enemy->GetActorLocation();
			break;
		}
	}
	//发射飞剑
	IsShortPressHurt = true;
	//调整方向
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EndLocation);
	SetActorRotation(NewRotation);
	//保证竖着
	AddActorLocalRotation(FRotator(-90, 0, 0));



	BeginSpell(EndLocation, ShortSpellSpeed);
	

}
void AFeiJian::TriggeredByLongPress() 
{
	Super::TriggeredByLongPress();
	if (IsInHand)
	{
		TArray<AActor*> DetectedEnemies = ShortPressEnemyDetector->DetectEnemies();
		if (!DetectedEnemies.IsEmpty())
		{
			FVector EndLocation;
			for (auto Enemy : DetectedEnemies)
			{
				if (Enemy != GetOwner())
				{
					EndLocation = Enemy->GetActorLocation();
					//飞剑变大
					SetActorScale3D(FVector(2, 2, 2));
					//透明度变化
					StaticMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Alpha"), 0.5);
					//调整位置
					SetActorLocation(EndLocation + FVector(0, 0, UpDistance));
					IsInHand = false;
					IsLongPressHurt = true;
					StaticMeshComponent->SetVisibility(true);
					//调整方向
					AddActorLocalRotation(FRotator(180, 0, 0));
					//飞剑从天而降
					BeginSpell(EndLocation,LongSpellSpeed);
					break;
				}
			}
			
		}
	}
	else
	{
		FVector EndLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 10;
		//发射飞剑
		IsShortPressHurt = true;
		//调整方向
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EndLocation);
		SetActorRotation(NewRotation);
		//保证竖着
		AddActorLocalRotation(FRotator(-90, 0, 0));
		BeginSpell(EndLocation,ShortSpellSpeed);
		IsGoHome = true;
		
	}

}

void AFeiJian::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (IsSpell)
	{
		ACreature* Creature = Cast<ACreature>(OtherActor);
		if (Creature)
		{
			//如果是拥有者，收回
			if (Creature == Owner)
			{
				EndSpell();
				AttachToCharacter(Creature);
			}
			else
			{
				if (IsShortPressHurt)
					Creature->BeAttacked(this, POAttackAttributeComponent->GetShortPressDamageMultiplier());
				else if (IsLongPressHurt)
					Creature->BeAttacked(this, POAttackAttributeComponent->GetLongPressDamageMultiplier());
			}

		}
		else
			EndSpell();
	}

}

//结束施法
//针对飞行的记录，ProjectileMovementComponent的处理
void AFeiJian::EndSpell()
{
	ProjectileMovementComponent->Deactivate();
	if(IsShortPressHurt)
	{
		AddActorLocalRotation(FRotator(90, 0, 0));
		IsSpell = false;
		IsShortPressHurt = false;
	}
	if(IsLongPressHurt)
	{
		//变回原先大小
		SetActorScale3D(FVector(1, 1, 1));
		//透明度变回
		IsLongPressHurt = false;
		AttachToCharacter(Owner);
	}
	if (IsGoHome)
	{
		AttachToCharacter(Owner);
	}
}

//开始施法
//针对飞行的记录，ProjectileMovementComponent的处理，并且处理判断飞行距离
void AFeiJian::BeginSpell(FVector EndLocation,float Speed)
{
	IsSpell = true;
	ProjectileMovementComponent->Velocity = (EndLocation - GetActorLocation()).GetSafeNormal() * Speed;
	ProjectileMovementComponent->Activate();
	StartLocation = GetActorLocation();
	if (GetOwner())
	{
		Owner = Cast<ACreature>(GetOwner());
		//不再随着角色变换
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}



