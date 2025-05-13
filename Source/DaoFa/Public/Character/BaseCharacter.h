// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputOperationComponent;
class UAttributeComponent;
class UPackComponent;
class UEnemyDetector;
class UEquipmentBarComponent;
class UReputationComponent;
UCLASS()
class DAOFA_API ABaseCharacter : public ACreature
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyDetector", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyDetector> EnemyDetector;

	

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipmentBar")
	TObjectPtr<UEquipmentBarComponent> EquipmentBarComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputOperationComponent> InputOperationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reputation")
	TObjectPtr<UReputationComponent> ReputationComponent;


	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UInputOperationComponent* GetInputOperationComponent() const { return InputOperationComponent; }
	// Called to bind functionality to input


	UEnemyDetector* GetEnemyDetector() const { return EnemyDetector; }


	virtual FString GetKey() const override { return TEXT("BaseCharacter"); }

	UEquipmentBarComponent* GetEquipmentBarComponent() const { return EquipmentBarComponent; }

	UReputationComponent* GetReputationComponent() const { return ReputationComponent; }


};
