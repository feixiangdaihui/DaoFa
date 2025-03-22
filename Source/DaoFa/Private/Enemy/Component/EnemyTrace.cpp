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
