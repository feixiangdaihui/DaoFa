// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hud/Interface/InitWidgetByCharacter.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class DAOFA_API UInteractWidget : public UUserWidget, public IInitWidgetByCharacter
{
	GENERATED_BODY()

public:
	virtual void InitWidgetByCharacter(ABaseCharacter* Character) override;
};
