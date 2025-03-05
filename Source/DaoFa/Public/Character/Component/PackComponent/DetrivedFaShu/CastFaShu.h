// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/FaShu.h"
#include "CastFaShu.generated.h"


class ACastFaShuProjectile;
class UEnemyDetector;

/**
 * 
 */
UCLASS()
class DAOFA_API ACastFaShu : public AFaShu
{
	GENERATED_BODY()
	
public:
	ACastFaShu();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	TSubclassOf<ACastFaShuProjectile> CastFaShuProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	TObjectPtr< UEnemyDetector> EnemyDetector;

	//炮弹释放的起始位置(相对于释放者)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	float SpellSpeed = 3000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	float SpellMaxDistance = 3000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	float DamageMutiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	float SpellInterval = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CastFaShu")
	int SpellNumber = 5;
	int SpellNumberCounter = 0;

	FTimerHandle SpellTimerHandle;


	virtual void BaseCastSpell();

	virtual AActor* FindTarget();

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);



private:
	bool IsSpell;


	virtual void TriggeredByLongPress() override;





	
	
};
