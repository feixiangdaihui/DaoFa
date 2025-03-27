#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "General/Interface/Attacker.h"
#include "CastFaShuProjectile.generated.h"


//overlap委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnProjectileHit, ACastFaShuProjectile*, FaShuProjectile, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, const FHitResult&, SweepResult);


class UProjectileMovementComponent;
class UCapsuleComponent;
class UNiagaraComponent;
class UNiagaraSystem;
UCLASS()
class DAOFA_API ACastFaShuProjectile : public AActor, public IAttacker
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACastFaShuProjectile();
	UPROPERTY(BlueprintAssignable, Category = "CastFaShu")
	FOnProjectileHit OnProjectileHit;
private:
	float SpellMaxDistance;
	FVector StartLocation;


protected:


	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	TObjectPtr<UNiagaraSystem> EndNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	float EndNiagaraTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	EAttackerType AttackerType = EAttackerType::BLOCK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	FAttackerInfo AttackerInfo;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	void BeginSpell(FVector EndLocation, float Speed, float MaxDistance, FAttackerInfo InAttackerInfo);

	void Explode(const FVector& HitLocation);

	virtual FAttackerInfo GetAttackerInfo() override { return AttackerInfo; }

	virtual EAttackerType GetAttackerType() override { return AttackerType; }


	
};
