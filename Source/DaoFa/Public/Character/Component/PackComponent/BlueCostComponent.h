// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlueCostComponent.generated.h"

class UBlueComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UBlueCostComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlueCostComponent();
	friend class APackObject;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float StartBlueCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float OnGoingBlueCostBySecond = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float EndBlueCost = 0.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool BlueCostAtStart(UBlueComponent* BlueComponent);
	
	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool BlueCostOnGoing(UBlueComponent* BlueComponent, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool BlueCostInTheEnd(UBlueComponent* BlueComponent);

		
};
