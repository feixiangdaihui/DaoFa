// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hud/Interface/InitWidgetByCharacter.h"
#include "ReputationWidget.generated.h"

/**
 * 
 */
class UReputationComponent;
class UFaceComponent;
UCLASS()
class DAOFA_API UReputationWidget : public UUserWidget, public IInitWidgetByCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reputation")
	TObjectPtr<UReputationComponent> ReputationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reputation")
	TObjectPtr<UFaceComponent> FaceComponent;
	
public:
	virtual void InitWidgetByCharacter(ABaseCharacter* Character) override;
	
};
