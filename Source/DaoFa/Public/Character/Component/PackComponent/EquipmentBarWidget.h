// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentBarWidget.generated.h"
class APackObject;
class UTexture2D;
/**
 * 
 */
UCLASS()
class DAOFA_API UEquipmentBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:


	UEquipmentBarWidget(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentBar")
	int CurrentIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentBar")
	int Size = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentBar")
	TArray<APackObject*> EquipmentBar;

	


	//蓝图实现
	UFUNCTION(BlueprintImplementableEvent, Category = "EquipmentBar")
	void OnEquipmentWear(int Index);

	UFUNCTION(BlueprintImplementableEvent, Category = "EquipmentBar")
	void OnEquipmentTakeOff(int Index);



public:

	UFUNCTION(BlueprintImplementableEvent, Category = "EquipmentBar")
	void SetChosen(bool IsChosen);

	UFUNCTION(BlueprintCallable, Category = "EquipmentBar")
	virtual void  WearEquipment(APackObject* Equipment, int Index);
	
	virtual void TakeOffEquipment(APackObject* Equipment);

	UFUNCTION(BlueprintCallable, Category = "EquipmentBar")
	bool TriggeredBegin(int Index);

	UFUNCTION(BlueprintCallable, Category = "EquipmentBar")
	bool TriggeredEnd(int Index);


	
};
