// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Component/EnemyBehavior.h"
#include "TestEnBe.generated.h"
class UEnemyPackComponent;
class UCreatureBehavior;
/**
 * 
 */
UCLASS()
class DAOFA_API UTestEnBe : public UEnemyBehavior
{
	GENERATED_BODY()
private:
	UEnemyPackComponent* PackComponent;
	UCreatureBehavior* CreatureBehavior;
	int TestFrontFarFaBaoIndex = 1;
	int TestFrontNearFaShuIndex = 0;
	int TestBackNearrFaBaoIndex = 0;
protected:
	virtual void BehaveWhenTargetIsFrontFar() override;
	virtual void BehaveWhenTargetIsFrontNear() override;
	virtual void BehaveWhenTargetIsBackNear() override;

public:
	virtual void BeginPlay() override;
	UTestEnBe();
	
};
