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

	//分两段时间消耗蓝，如果蓝够则先扣除短按蓝，如果长按并且蓝够再扣除长按蓝，放出长按技能，否则放出短按技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float ShortPressBlueCost = 0.0f;

	//属于在短按基础上的额外消耗
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float LongPressBlueCost = 0.0f;


public:
	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool CheckShortPressBlueCost();

	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool CheckLongPressBlueCost();
	


		
};
