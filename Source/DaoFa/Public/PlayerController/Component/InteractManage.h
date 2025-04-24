// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractManage.generated.h"

class UInputOperationComponent;
class UInteractWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UInteractManage : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractManage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UInputOperationComponent* InputOperationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UInteractWidget* InteractWidget;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AskForInteract(FText InteractText, TFunction<void()> InteractFunc) ;

	void EndInteract();
		
};
