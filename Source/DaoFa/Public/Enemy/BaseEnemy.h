// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "BaseEnemy.generated.h"

class UEnemyController;
/**
 * 
 */
UCLASS()
class DAOFA_API ABaseEnemy : public ACreature
{
	GENERATED_BODY()

protected: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FText ObjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UEnemyController> EnemyController;


public:

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	FText GetObjectName() const { return ObjectName; }

	ABaseEnemy();
	

};
