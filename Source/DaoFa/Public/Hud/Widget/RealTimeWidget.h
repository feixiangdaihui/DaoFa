// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hud/Interface/InitWidgetByCharacter.h"
#include "RealTimeWidget.generated.h"

class UMyProgressBar;
class IGetValueInterface;
/**
 * 
 */
UCLASS()
class DAOFA_API URealTimeWidget : public UUserWidget, public IInitWidgetByCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	TObjectPtr<UMyProgressBar> HealthValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blue")
	TObjectPtr<UMyProgressBar> BlueValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physical")
	TObjectPtr<UMyProgressBar> PhysicalPowerValue;

public:

	virtual void InitWidgetByCharacter(ABaseCharacter* Character) override;
	virtual void NativeConstruct() override;
};
