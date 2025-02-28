// Fill out your copyright notice in the Description page of Project Settings.


#include "General/EnemyDetector.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Creature.h"

// Sets default values for this component's properties
UEnemyDetector::UEnemyDetector()
{
    PrimaryComponentTick.bCanEverTick = true;
	EnemyClasses.Add(ACreature::StaticClass());

}

void UEnemyDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(IsTesting)
        DrawDebug();
}

TArray<AActor*> UEnemyDetector::DetectEnemies()
{
    if(IsTesting)
		UE_LOG(LogTemp, Warning, TEXT("Detecting Enemies..."));
    TArray<AActor*> DetectedEnemies;
    TArray<AActor*> IgnoredActors;
    IgnoredActors.Add(GetOwner());

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

    TArray<FHitResult> HitResults;
    UKismetSystemLibrary::SphereTraceMultiForObjects(
        GetWorld(),
        GetOwner()->GetActorLocation(),
        GetOwner()->GetActorLocation(),
        DetectionRadius,
        ObjectTypes,
        false,
        IgnoredActors,
        EDrawDebugTrace::None,
        HitResults,
        true
    );

    for (const FHitResult& Hit : HitResults)
    {
        AActor* PotentialEnemy = Hit.GetActor();
        if(IsTesting)
			UE_LOG(LogTemp, Warning, TEXT("Potential Enemy: %s"), *PotentialEnemy->GetName());
        if (PotentialEnemy && IsInViewCone(PotentialEnemy->GetActorLocation()))
        {
			if (EnemyClasses.IsEmpty())
			{
				DetectedEnemies.Add(PotentialEnemy);
			}
            else for (auto EnemyClass : EnemyClasses)
            {
                if (PotentialEnemy->IsA(EnemyClass))
                {
                    DetectedEnemies.Add(PotentialEnemy);
                    break;
                }
            }
        }
    }
    return DetectedEnemies;
}

bool UEnemyDetector::IsInViewCone(const FVector& TargetLocation) const
{
    FVector OwnerLocation = GetOwner()->GetActorLocation();
    FVector ForwardVector = GetOwner()->GetActorForwardVector();
    FVector ToTarget = (TargetLocation - OwnerLocation).GetSafeNormal();

    // 水平角度检测
    float HorizontalDot = FVector::DotProduct(ForwardVector, ToTarget);
    float HorizontalAngleDeg = FMath::RadiansToDegrees(FMath::Acos(HorizontalDot));

    // 垂直角度检测
    FVector HorizontalProjection = FVector(ToTarget.X, ToTarget.Y, 0).GetSafeNormal();
    float VerticalDot = FVector::DotProduct(ToTarget, HorizontalProjection);
    float VerticalAngleDeg = FMath::RadiansToDegrees(FMath::Acos(VerticalDot));

    return (HorizontalAngleDeg <= HorizontalAngle) && (VerticalAngleDeg <= VerticalAngle);
}

void UEnemyDetector::DrawDebug() const
{
    if (!GetWorld()) return;

    const FVector Origin = GetOwner()->GetActorLocation();
    const FVector Forward = GetOwner()->GetActorForwardVector();
    const float Radius = DetectionRadius * FMath::Sin(FMath::DegreesToRadians(HorizontalAngle));

    // 绘制扇形区域
    DrawDebugCone(
        GetWorld(),
        Origin,
        Forward,
        DetectionRadius,
        FMath::DegreesToRadians(HorizontalAngle),
        FMath::DegreesToRadians(VerticalAngle),
        32,
        FColor::Green,
        false,
        -1,
        0,
        2
    );
}

