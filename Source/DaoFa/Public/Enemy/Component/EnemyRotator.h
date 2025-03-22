#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyRotator.generated.h"

class UEnemyTrace;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float RotateInterval = 0.1f;

	UEnemyTrace* EnemyTrace = nullptr;

	void RotateToTarget();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitEnemyRotator(UEnemyTrace* InEnemyTrace) { EnemyTrace = InEnemyTrace; }
};
