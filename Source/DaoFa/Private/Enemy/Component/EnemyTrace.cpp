#include "Enemy/Component/EnemyTrace.h"
#include "General/EnemyDetector.h"
#include "Character/BaseCharacter.h"
// Sets default values for this component's properties
UEnemyTrace::UEnemyTrace()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	EnemyDetector = CreateDefaultSubobject<UEnemyDetector>(TEXT("EnemyDetector"));
	EnemyDetector->DetectionRadius = 3000.0f;
	EnemyDetector->HorizontalAngle = 90.0f;
	EnemyDetector->VerticalAngle = 90.0f;
	EnemyDetector->EnemyClasses.Empty();
	EnemyDetector->EnemyClasses.Add(ABaseCharacter::StaticClass());
	// ...
	// ...
}

// Called when the game starts
void UEnemyTrace::BeginPlay()
{
	Super::BeginPlay();


	GetWorld()->GetTimerManager().SetTimer(UpdateTargetTimer, this, &UEnemyTrace::UpdateTarget, UpdateTargetInterval, true);
	// ...

}

// Called every frame
void UEnemyTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyTrace::UpdateTarget()
{
	TArray<AActor*> Enemies = EnemyDetector->DetectEnemies();
	if (Enemies.Num() > 0)
	{
		CurrentTarget = Enemies[0];
	}
}

FVector2D UEnemyTrace::GetDirAgainstTarget(bool IsAgainst)
{
	if (CurrentTarget)
	{
		FVector TargetLocation = CurrentTarget->GetActorLocation();
		FVector OwnerLocation = GetOwner()->GetActorLocation();
		FVector Dir = TargetLocation - OwnerLocation;
		if (IsAgainst)
		{
			Dir = -Dir;
		}
		return FVector2D(Dir.X, Dir.Y);
	}
	return FVector2D::ZeroVector;
}

FVector2D UEnemyTrace::GetDirVerticalToTarget(bool IsLeft)
{
	if (CurrentTarget)
	{
		FVector2D Dir = GetDirAgainstTarget();
		FVector2D VerticalDir = FVector2D(Dir.Y, -Dir.X);
		if (IsLeft)
		{
			VerticalDir = -VerticalDir;
		}
		return VerticalDir;
	}
	return FVector2D::ZeroVector;
}



float UEnemyTrace::GetDistanceToTarget()
{
	if (CurrentTarget)
	{
		FVector TargetLocation = CurrentTarget->GetActorLocation();
		FVector OwnerLocation = GetOwner()->GetActorLocation();
		return FVector::Dist(TargetLocation, OwnerLocation);
	}
	return -1.0f;
}