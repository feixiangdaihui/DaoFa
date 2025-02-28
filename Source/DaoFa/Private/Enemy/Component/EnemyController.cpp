#include "Enemy/Component/EnemyController.h"
#include "General/EnemyDetector.h"
#include "Creature.h"
#include "Character/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values for this component's properties
UEnemyController::UEnemyController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	EnemyDetector = CreateDefaultSubobject<UEnemyDetector>(TEXT("EnemyDetector"));
	EnemyDetector->DetectionRadius = 3000.0f;
	EnemyDetector->HorizontalAngle = 90.0f;
	EnemyDetector->VerticalAngle =90.0f;
	EnemyDetector->EnemyClasses.Empty();
	EnemyDetector->EnemyClasses.Add(ABaseCharacter::StaticClass());
	// ...
}

// Called when the game starts
void UEnemyController::BeginPlay()
{
	Super::BeginPlay();

	//定时器
	
	GetWorld()->GetTimerManager().SetTimer(UpdateTargetTimer, this, &UEnemyController::UpdateTarget, UpdateTargetInterval, true);
	GetWorld()->GetTimerManager().SetTimer(RotateTimer, this, &UEnemyController::RotateToTarget, RotateInterval, true);

	// ...

}

void UEnemyController::UpdateTarget()
{
	TArray<AActor*> Enemies = EnemyDetector->DetectEnemies();
	if (Enemies.Num() > 0)
	{
		ACreature* NewTarget = Cast<ACreature>(Enemies[0]);
		if (NewTarget != CurrentTarget)
		{
			CurrentTarget = NewTarget;
		}
	}
}

void UEnemyController::RotateToTarget()
{
	if (CurrentTarget)
	{
		FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation());
		FRotator CurrentRot = GetOwner()->GetActorRotation();
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, RotateInterval, RotateAnglePer);
		GetOwner()->SetActorRotation(NewRot);
	}
}

// Called every frame
void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
