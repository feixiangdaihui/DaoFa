#include "Character/Component/PackComponent/DetrivedFaShu/CastFaShuProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "General/AttackAttributeComponent.h"
// Sets default values
ACastFaShuProjectile::ACastFaShuProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//忽略重力
	ProjectileMovementComponent->ProjectileGravityScale = 0;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCollisionProfileName(TEXT("Overlapall"));
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACastFaShuProjectile::OnOverlapBegin);
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetEnableGravity(false);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	AttackAttributeComponent = CreateDefaultSubobject<UAttackAttributeComponent>(TEXT("AttackAttributeComponent"));
	AttackAttributeComponent->OnAttenuationComplete.AddDynamic(this, &ACastFaShuProjectile::OnAttenuationComplete);


}





void ACastFaShuProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ExplodeLocation = SweepResult.ImpactPoint;
	OnProjectileHit.Broadcast(this, OtherActor, OtherComp, SweepResult);
}


void ACastFaShuProjectile::OnAttenuationComplete(AActor* AttenuationObject)
{
	Explode();
}

// Called every frame
void ACastFaShuProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FVector::Dist(StartLocation, GetActorLocation()) > SpellMaxDistance)
	{
		Destroy();
	}

}





void ACastFaShuProjectile::BeginSpell(FVector EndLocation, float Speed, float MaxDistance, AActor* OwnerFaShu)
{
	SetActorRotation((EndLocation - GetActorLocation()).Rotation());
	ProjectileMovementComponent->Velocity = (EndLocation - GetActorLocation()).GetSafeNormal() * Speed;
	SpellMaxDistance = MaxDistance;
	StartLocation = GetActorLocation();
	ProjectileMovementComponent->Activate();
	SetOwner(OwnerFaShu);
}

void ACastFaShuProjectile::Explode(const FVector& HitLocation)
{
	if (EndNiagaraSystem)
	{
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EndNiagaraSystem, HitLocation, GetActorRotation());
	}
	Destroy();
}



