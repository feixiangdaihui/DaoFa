#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyController.generated.h"

class UEnemyTrace;
class UEnemyRotator;
class UEnemyBehavior;
class UBaseAnimInstance;
class ACreature;
class UEnemyMove;
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UEnemyTrace> EnemyTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UEnemyRotator> EnemyRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UEnemyBehavior> EnemyBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UEnemyMove> EnemyMove;


	UBaseAnimInstance* BaseAnimInstance = nullptr;

	ACreature* Owner = nullptr;


private:


	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetEnemyBehavior(TSubclassOf<UEnemyBehavior> InEnemyBehavior);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetEnemyMove(TSubclassOf<UEnemyMove> InEnemyMove);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool CanRotateToTarget() const;

};
