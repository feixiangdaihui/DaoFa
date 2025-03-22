#include "Enemy/Component/EnemyBehavior.h"
#include "Enemy/Component/EnemyTrace.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UEnemyBehavior::UEnemyBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UEnemyBehavior::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(BehaviorTimer, this, &UEnemyBehavior::UpdateBehavior, UpdateBehaviorInterval, true);
	// ...

}




DistanceType UEnemyBehavior::CalDistanceType(const FVector& TargetLocation, const FVector& OwnerLocation, DirectionType Dir)
{
	float Distance = FVector::Dist(TargetLocation, OwnerLocation);
	switch (Dir)
	{
	case DirectionType::Front:
		if (Distance < FrontDistanceNear)
		{
			return DistanceType::Near;
		}
		else
		{
			return DistanceType::Far;
		}
		break;
	case DirectionType::Back:
		if (Distance < BackDistanceNear)
		{
			return DistanceType::Near;
		}
		else
		{
			return DistanceType::Far;
		}
		break;
	case DirectionType::Side:
		if (Distance < SideDistanceNear)
		{
			return DistanceType::Near;
		}
		else
		{
			return DistanceType::Far;
		}
		break;
	default:
		return DistanceType::Far;
		break;
	}
}

DirectionType UEnemyBehavior::CalDirectionType(const FRotator& LookRotator)
{
	float Yaw = LookRotator.Yaw;
	//绝对值
	Yaw = FMath::Abs(Yaw);
	if (Yaw<FrontAngleDomain / 2 )
	{
		return DirectionType::Front;
	}
	else if ( Yaw>180-BackAngleDomain / 2 )
	{
		return DirectionType::Back;
	}
	else
	{
		return DirectionType::Side;
	}
}

FRotator UEnemyBehavior::WorldToLocalRotation(const FRotator& WorldRot, const FTransform& OwnerTransForm)
{
	FTransform ChildWorldTransform(WorldRot, FVector::ZeroVector);
	FTransform LocalTransform = ChildWorldTransform.GetRelativeTransform(OwnerTransForm);
	FRotator RelativeRot = LocalTransform.Rotator();
	return RelativeRot;
}

void UEnemyBehavior::UpdateBehavior()
{
	if (EnemyTrace)
	{
		AActor* CurrentTarget = Cast<AActor>(EnemyTrace->GetCurrentTarget());
		if (CurrentTarget)
		{
			FVector TargetLocation = CurrentTarget->GetActorLocation();
			FVector OwnerLocation = GetOwner()->GetActorLocation();
			FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);
			LookRotator = WorldToLocalRotation(LookRotator, GetOwner()->GetTransform());
			DirectionType Dir = CalDirectionType(LookRotator);
			DistanceType Distance = CalDistanceType(TargetLocation, OwnerLocation, Dir);
			if(IsTest)
			{
				UE_LOG(LogTemp, Warning, TEXT("Dir:%d,Distance:%d"), (uint8)Dir, (uint8)Distance);
			}
			switch (Dir)
			{
			case DirectionType::Front:
				if (Distance == DistanceType::Near)
				{
					BehaveWhenTargetIsFrontNear();
				}
				else
				{
					BehaveWhenTargetIsFrontFar();
				}
				break;
			case DirectionType::Back:
				if (Distance == DistanceType::Near)
				{
					BehaveWhenTargetIsBackNear();
				}
				else
				{
					BehaveWhenTargetIsBackFar();
				}
				break;
			case DirectionType::Side:
				if (Distance == DistanceType::Near)
				{
					BehaveWhenTargetIsSideNear();
				}
				else
				{
					BehaveWhenTargetIsSideFar();
				}
				break;
			default:
				break;
			}
		}

	}

}

// Called every frame
void UEnemyBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

