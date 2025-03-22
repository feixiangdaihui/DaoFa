#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyBehavior.generated.h"


enum class DirectionType : uint8
{
	Front,
	Back,
	Side
};
enum class DistanceType : uint8
{
	Near,
	Far
};

class UEnemyTrace;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UEnemyBehavior : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyBehavior();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UEnemyTrace* EnemyTrace = nullptr;


	FTimerHandle BehaviorTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float UpdateBehaviorInterval = 0.1f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float FrontDistanceNear = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float BackDistanceNear = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float SideDistanceNear = 1000.0f;

	//以角色为中心的前方扇形角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float FrontAngleDomain = 120.0f;
	//以角色为中心的后方扇形角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float BackAngleDomain = 120.0f;



	virtual void BehaveWhenTargetIsFrontNear(){}
	virtual void BehaveWhenTargetIsFrontFar(){}
	virtual void BehaveWhenTargetIsBackNear(){}
	virtual void BehaveWhenTargetIsBackFar(){}
	virtual void BehaveWhenTargetIsSideNear(){}
	virtual void BehaveWhenTargetIsSideFar(){}


	DistanceType CalDistanceType(const FVector& TargetLocation, const FVector& OwnerLocation, DirectionType Dir);

	DirectionType CalDirectionType(const FRotator& LookRotator);

	static FRotator WorldToLocalRotation(const FRotator& WorldRot, const FTransform& OwnerTransForm);

	void UpdateBehavior();

	bool IsTest = false;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitEnemyBehavior(UEnemyTrace* InEnemyTrace) { EnemyTrace = InEnemyTrace; }


};
