// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlueCostComponent.generated.h"

class ISetValueInterface;
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

	TScriptInterface<ISetValueInterface> BlueValue;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool BlueCost(float CostValue);

	


		
};
