// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hud/Interface/InitWidgetByCharacter.h"
#include "PackWidget.generated.h"
class UPackComponent;
/**
 * 
 */
class USumEquipmentBarWidget;
UCLASS()
class DAOFA_API UPackWidget : public UUserWidget, public IInitWidgetByCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Pack")
	UPackComponent* PackComponent;

	UFUNCTION(BlueprintImplementableEvent, Category = "Pack")
	void OpenPack();
	UFUNCTION(BlueprintImplementableEvent, Category = "Pack")
	void ClosePack();
public:
	
	void OpenClosePack();


	virtual void InitWidgetByCharacter(ABaseCharacter* Character) override;

};
