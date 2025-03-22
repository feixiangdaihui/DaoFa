// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "BaseEnemy.generated.h"

class APackObject;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttacked,APackObject*,Attacker);
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
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UEnemyController> EnemyController;


public:
	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FOnAttacked OnAttacked;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	FText GetName() const { return Name; }

	ABaseEnemy();
	
	virtual void BeAttacked(APackObject* PackObject, float DamageMultiplier) override;

};
