// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "Businessman.generated.h"


class UInteractComponent;
class UBusinessmanPackComponent;
/**
 * 
 */
UCLASS()
class DAOFA_API ABusinessman : public ACreature
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	ABusinessman();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Businessman")
	TObjectPtr<UBusinessmanPackComponent> BusinessmanPackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Businessman")
	TObjectPtr<UInteractComponent> InteractComponent;

	void OpenShoppingWidget();


};
