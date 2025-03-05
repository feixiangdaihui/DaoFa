// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "General/Interface/BeAttacked.h"
#include "Creature.generated.h"
class UAttributeComponent;
class UPackComponent;
class UDefenseComponent;
class UStateComponent;
class APackObject;
class UCreatureBehavior;
UCLASS()
class DAOFA_API ACreature : public ACharacter, public IBeAttacked
{
	GENERATED_BODY()



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	TObjectPtr<UAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pack")
	TObjectPtr<UPackComponent> PackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Defense")
	TObjectPtr<UDefenseComponent> DefenseComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	TObjectPtr<UStateComponent> StateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behavior")
	TObjectPtr<UCreatureBehavior> CreatureBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	float WalkSpeed = 250.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	float RunSpeed = 500.f;

public:
	// Sets default values for this character's properties
	ACreature();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UAttributeComponent* GetAttributeComponent() { return AttributeComponent.Get(); }
	UPackComponent* GetPackComponent() { return PackComponent.Get(); }
	UDefenseComponent* GetDefenseComponent()  const{ return DefenseComponent.Get(); }
	UStateComponent* GetStateComponent() { return StateComponent.Get(); }
	UCreatureBehavior* GetCreatureBehavior() { return CreatureBehavior.Get(); }

	virtual void BeAttacked(APackObject* PackObject, float DamageMultiplier) override;

	UFUNCTION()
	void SetSpeedToWalk();

	UFUNCTION()
	void SetSpeedToRun();

	void SetUnbeatable(bool NewValue);

};
