// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hud/Interface/InitSumEquipmentBarInterface.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputOperationComponent;
class UAttributeComponent;
class UPackComponent;
UCLASS()
class DAOFA_API ABaseCharacter : public ACharacter, public IInitSumEquipmentBarInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float WalkSpeed = 250.f;
	float RunSpeed = 500.f;





	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputOperationComponent> InputOperationComponent;
	// Called to bind functionality to input
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	TObjectPtr<UAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pack")
	TObjectPtr<UPackComponent> PackComponent;

	UFUNCTION()
	void SetSpeedToWalk();

	UFUNCTION()
	void SetSpeedToRun();

	virtual void InitSumEquipmentBar(USumEquipmentBarWidget* SumEquipmentBarWidget) override;


};
