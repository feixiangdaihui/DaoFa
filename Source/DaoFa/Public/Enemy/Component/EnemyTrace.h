#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyTrace.generated.h"

class UEnemyDetector;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UEnemyTrace : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr< UEnemyDetector> EnemyDetector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float UpdateTargetInterval = 1.0f;

	FTimerHandle UpdateTargetTimer;

	AActor* CurrentTarget = nullptr;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UEnemyDetector* GetEnemyDetector() const { return EnemyDetector; }

	void UpdateTarget();

	AActor* GetCurrentTarget() const { return CurrentTarget; }

};
