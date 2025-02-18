// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackWidget.generated.h"
class UPackComponent;
/**
 * 
 */
class USumEquipmentBarWidget;
UCLASS()
class DAOFA_API UPackWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Pack")
	UPackComponent* PackComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Pack")
	USumEquipmentBarWidget* SumEquipmentBarWidget;

public:
	//蓝图实现
	UFUNCTION(BlueprintImplementableEvent, Category = "Pack")
	void OpenPack();
	UFUNCTION(BlueprintImplementableEvent, Category = "Pack")
	void ClosePack();
	void InitPackWidget(UPackComponent* InPackComponent);

};
