#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMove.generated.h"

class UEnemyTrace;
class UCreatureBehavior;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UEnemyMove : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UEnemyTrace* EnemyTrace = nullptr;

	UCreatureBehavior* CreatureBehavior = nullptr;

	static FVector2D MergeDir(FVector2D Dir1, float Weight1, FVector2D Dir2, float Weight2);

	virtual FVector2D CalMoveVec() { return FVector2D::ZeroVector; }

	virtual void Move();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(UEnemyTrace* InEnemyTrace) { EnemyTrace = InEnemyTrace; }


};
