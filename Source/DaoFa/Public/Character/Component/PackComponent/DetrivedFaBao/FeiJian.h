// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/FaBao.h"
#include "General/Interface/Attacker.h"
#include "FeiJian.generated.h"
class UEnemyDetector;
class UCapsuleComponent;
class UProjectileMovementComponent;
class ACreature;
class UAttackAttributeComponent;
/**
 * 
 */
UCLASS()
class DAOFA_API AFeiJian : public AFaBao, public IAttacker
{
	GENERATED_BODY()
protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	TObjectPtr<UAttackAttributeComponent> AttackAttributeComponent;

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
	float ShortSpellSpeed = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float LongSpellSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	float MaxSpellDistance = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeiJian")
	EAttackerType AttackerType = EAttackerType::NOBLOCK;

public:
	AFeiJian();
	virtual void AttachToCreature(class ACreature* Creature) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual UAttackAttributeComponent* GetAttackAttributeComponent() override { return AttackAttributeComponent; }

	virtual EAttackerType GetAttackerType() override { return AttackerType; }
private:
	bool IsInHand = true;
	bool IsLongPressHurt = false;
	bool IsShortPressHurt = false;
	FVector StartLocation;
	bool IsSpell = false;
	bool IsGoHome = false;
	


	virtual void TriggeredByShortPress() override;

	virtual void TriggeredByLongPress() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EndSpell();

	void BeginSpell(FVector EndLocation,float Speed);


	
};
