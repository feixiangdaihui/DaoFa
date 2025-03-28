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

	APackObject* OwnerPackObject;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//分两段时间消耗蓝，如果蓝够则先扣除短按蓝，如果长按并且蓝够再扣除长按蓝，放出长按技能，否则放出短按技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float ShortPressBlueCost = 0.0f;

	//属于在短按基础上的额外消耗
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float LongPressBlueCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	bool OngoingMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float OngoingBlueCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float OngoingInterval = 0.1f;



	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool ShortPressCostBlue();

	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	bool LongPressCostBlue();

	FTimerHandle OngoingTimer;
	//持续技能消耗蓝，参数包含没蓝时调用的函数
	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	void OngoingCostBlue();

	UFUNCTION(BlueprintCallable, Category = "BlueCost")
	void EndOngoingCostBlue();



		
};
