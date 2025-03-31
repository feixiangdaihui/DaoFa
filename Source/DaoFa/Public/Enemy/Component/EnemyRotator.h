#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyRotator.generated.h"

class UEnemyTrace;
class UEnemyController;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UEnemyRotator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	


	FTimerHandle RotateTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float RotateAnglePerSecond = 1.0f;

	UEnemyTrace* EnemyTrace = nullptr;

	UEnemyController* EnemyController = nullptr;

	void RotateToTarget(float DeltaTime);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(UEnemyController* InEnemyController, UEnemyTrace* InEnemyTrace) { EnemyController = InEnemyController; EnemyTrace = InEnemyTrace; }
};
