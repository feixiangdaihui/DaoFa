#include "Enemy/Component/EnemyController.h"
#include "Enemy/Component/EnemyTrace.h"
#include "Enemy/Component/EnemyRotator.h"
#include "Enemy/Component/EnemyBehavior.h"
#include"Creature.h"
#include "Character/Animation/BaseAnimInstance.h"
#include "Enemy/Component/EnemyMove.h"
// Sets default values for this component's properties
UEnemyController::UEnemyController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	EnemyTrace = CreateDefaultSubobject<UEnemyTrace>(TEXT("EnemyTrace"));
	EnemyRotator = CreateDefaultSubobject<UEnemyRotator>(TEXT("EnemyRotator"));
	EnemyBehavior = CreateDefaultSubobject<UEnemyBehavior>(TEXT("EnemyBehavior"));
	EnemyMove = CreateDefaultSubobject<UEnemyMove>(TEXT("EnemyMove"));

	EnemyRotator->Init(this,EnemyTrace);	

}

// Called when the game starts
void UEnemyController::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACreature>(GetOwner());
	if (Owner)
	{
		BaseAnimInstance = Cast<UBaseAnimInstance>(Owner->GetMesh()->GetAnimInstance());
		if (!BaseAnimInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s BaseAnimInstance is nullptr"), *Owner->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is nullptr"));
	}
	

	// ...
}

// Called every frame
void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyController::SetEnemyBehavior(TSubclassOf<UEnemyBehavior> InEnemyBehavior)
{
	if (InEnemyBehavior)
	{
		EnemyBehavior = NewObject<UEnemyBehavior>(this, InEnemyBehavior);
		EnemyBehavior->RegisterComponent();
		EnemyBehavior->Init(EnemyTrace);
	}
}

void UEnemyController::SetEnemyMove(TSubclassOf<UEnemyMove> InEnemyMove)
{
	if (InEnemyMove)
	{
		EnemyMove = NewObject<UEnemyMove>(this, InEnemyMove);
		EnemyMove->RegisterComponent();
		EnemyMove->Init(EnemyTrace);
	}
}


bool UEnemyController::CanRotateToTarget() const
{
	if (BaseAnimInstance)
	{
		return BaseAnimInstance->GetSequenceState() != AnimationType::Idle;
	}
	return false;
}

