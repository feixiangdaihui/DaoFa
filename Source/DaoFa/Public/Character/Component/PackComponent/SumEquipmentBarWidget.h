// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/EquipmentBarWidget.h"
#include "Character/Interface/UpdateEquipmentInterface.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "SumEquipmentBarWidget.generated.h"

#define EQUIPMENTBAR_NUM 3


/**
 * 
 */
UCLASS()
class DAOFA_API USumEquipmentBarWidget : public UUserWidget, public IUpdateEquipmentInterface
{
	GENERATED_BODY()

protected:
	
	//绑定控件
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEquipmentBarWidget> FaShuEquipmentBar;
	UPROPERTY( meta = (BindWidget))
	TObjectPtr<UEquipmentBarWidget> FaBaoEquipmentBar;
	UPROPERTY( meta = (BindWidget))
	TObjectPtr<UEquipmentBarWidget> FuLuEquipmentBar;

	int CurrentChosenIndex = 0;

public:

    virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	virtual void WearEquipment( APackObject* Equipment, int SpecificIndex = -1) override;

	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	virtual void TakeOffEquipment(APackObject* Equipment) override;

	void TriggeredByLongPress(EEquipmentType TypeIndex, int SpecificIndex);

	void TriggeredByShortPress(EEquipmentType TypeIndex, int SpecificIndex);


	void ChangeChosenEquipmentBarToSmall();

	void ChangeChosenEquipmentBarToBig();

	//蓝图中实现
	
	void SetChosenEquipmentBar(int Index);
	
};
