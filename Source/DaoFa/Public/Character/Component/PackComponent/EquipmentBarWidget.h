// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentBarWidget.generated.h"
class APackObject;
/**
 * 
 */
UCLASS()
class DAOFA_API UEquipmentBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentBar")
	TArray<APackObject*> EquipmentBar;

	


	//蓝图实现
	UFUNCTION(BlueprintImplementableEvent, Category = "EquipmentBar")
	void UpdateEquipmentBar();




public:

	UFUNCTION(BlueprintImplementableEvent, Category = "EquipmentBar")
	void SetChosen(bool IsChosen);

	UFUNCTION(BlueprintCallable, Category = "EquipmentBar")
	void SetEquipmentBar(TArray<APackObject*> InEquipmentBar) { EquipmentBar = InEquipmentBar; UpdateEquipmentBar(); }



	
};
