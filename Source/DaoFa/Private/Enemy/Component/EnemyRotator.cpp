#include "Enemy/Component/EnemyRotator.h"
#include "Enemy/Component/EnemyTrace.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy/Component/EnemyController.h"

// Sets default values for this component's properties
UEnemyRotator::UEnemyRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UEnemyRotator::BeginPlay()
{
	Super::BeginPlay();
	// ...

}

void UEnemyRotator::RotateToTarget(float DeltaTime)
{
	if(EnemyTrace)
	{
		AActor* CurrentTarget = Cast<AActor>(EnemyTrace->GetCurrentTarget());
		if (CurrentTarget)
		{
			FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation());
			FRotator CurrentRot = GetOwner()->GetActorRotation();
			const FRotator HorizontalRot(0, TargetRot.Yaw, 0);
			FRotator NewRot = FMath::RInterpTo(CurrentRot, HorizontalRot, DeltaTime, RotateAnglePerSecond);
			GetOwner()->SetActorRotation(NewRot);
		}
	}
}


// Called every frame
void UEnemyRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (EnemyController && EnemyController->CanRotateToTarget())
	{
		RotateToTarget(DeltaTime);
	}
	// ...
}


