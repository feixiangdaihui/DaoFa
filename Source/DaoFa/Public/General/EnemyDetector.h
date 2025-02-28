// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDetector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UEnemyDetector : public UActorComponent
{
	GENERATED_BODY()



public:
    // Sets default values for this component's properties
    UEnemyDetector();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    float DetectionRadius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    float HorizontalAngle = 45.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    float VerticalAngle = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    TArray<TSubclassOf<AActor>> EnemyClasses;

    UFUNCTION(BlueprintCallable)

    TArray<AActor*> DetectEnemies();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
    bool IsTesting = false;


    //tick
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

    bool IsInViewCone(const FVector& TargetLocation) const;
    void DrawDebug() const;


		
};
