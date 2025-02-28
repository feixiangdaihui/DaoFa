#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyController.generated.h"
class UEnemyDetector;
class ACreature;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UEnemyController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr< UEnemyDetector> EnemyDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	float UpdateTargetInterval = 10.0f;

	FTimerHandle UpdateTargetTimer;

	FTimerHandle RotateTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	float RotateAnglePer = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	float RotateInterval = 0.1f;

	ACreature* CurrentTarget = nullptr;
private:

	void UpdateTarget();

	void RotateToTarget();


	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UEnemyDetector* GetEnemyDetector() const { return EnemyDetector; }

};
