// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/FaBao.h"
#include "FeiJian.generated.h"
class UEnemyDetector;
class UCapsuleComponent;
class UProjectileMovementComponent;
class ACreature;
/**
 * 
 */
UCLASS()
class DAOFA_API AFeiJian : public AFaBao
{
	GENERATED_BODY()
protected:



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	TObjectPtr<UEnemyDetector> ShortPressEnemyDetector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	TObjectPtr<UEnemyDetector>	LongPressEnemyDetector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	TObjectPtr< UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float UpDistance = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float SpellSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float MaxSpellDistance = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float ShortPressBlueCost = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float LongPressBlueCost = 20;

public:
	AFeiJian();
	virtual void AttachToCharacter(class ACreature* Creature) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
private:
	bool IsInHand = true;
	bool IsLongPressHurt = false;
	bool IsShortPressHurt = false;
	FVector StartLocation;
	bool IsSpell = false;
	ACreature* Owner;
	bool IsGoHome = false;
	


	virtual void TriggeredByShortPress() override;

	virtual void TriggeredByLongPress() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EndSpell();

	void BeginSpell(FVector EndLocation);


	
};
