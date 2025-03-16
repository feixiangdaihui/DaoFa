// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/EquipmentBarWidget.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "SumEquipmentBarWidget.generated.h"

#define EQUIPMENTBAR_NUM 3


/**
 * 
 */
UCLASS()
class DAOFA_API USumEquipmentBarWidget : public UUserWidget
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



public:

    virtual void NativeConstruct() override;

	void SetEquipmentBar(int Index, TArray<APackObject*> EquipmentBar);

	//蓝图中实现
	
	void SetChosenEquipmentBar(int Index);

	
};
