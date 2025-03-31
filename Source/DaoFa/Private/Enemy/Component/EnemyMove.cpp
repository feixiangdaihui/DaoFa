#include "Enemy/Component/EnemyMove.h"
#include "Enemy/Component/EnemyTrace.h"
#include "General/CreatureBehavior.h"
#include "Creature.h"

// Sets default values for this component's properties
UEnemyMove::UEnemyMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UEnemyMove::BeginPlay()
{
	Super::BeginPlay();

	ACreature* Owner = Cast<ACreature>(GetOwner());
	if (Owner)
	{
		CreatureBehavior = Owner->GetCreatureBehavior();
		if (!CreatureBehavior)
			UE_LOG(LogTemp, Warning, TEXT("%s CreatureBehavior is nullptr"), *Owner->GetName());
	}
	// ...

}


FVector2D UEnemyMove::MergeDir(FVector2D Dir1, float Weight1, FVector2D Dir2, float Weight2)
{
	FVector2D Dir = Dir1 * Weight1 + Dir2 * Weight2;
	Dir.Normalize();
	return Dir;
}

void UEnemyMove::Move()
{
	FVector2D MovementVector = CalMoveVec();
	if (MovementVector.Size() > 0)
	{
		CreatureBehavior->Walk(MovementVector);
	}
}




// Called every frame
void UEnemyMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move();

	// ...
}
