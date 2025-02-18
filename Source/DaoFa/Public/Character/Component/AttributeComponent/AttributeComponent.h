// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Interface/InputUpdateInterface.h"
#include "AttributeComponent.generated.h"

class UHealthComponent;
class UPhysicalPowerComponent;
class UBlueComponent;
class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ABaseCharacter* OwnerCharacter;
	


public:	

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	TObjectPtr<UPhysicalPowerComponent> PhysicalPowerComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	TObjectPtr<UBlueComponent> BlueComponent;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// IInputUpdateInterface
		
};
