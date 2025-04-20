// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/EquipmentBarWidget.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "Hud/Interface/InitWidgetByCharacter.h"
#include "SumEquipmentBarWidget.generated.h"



class UEquipmentBarComponent;
/**
 * 
 */
UCLASS()
class DAOFA_API USumEquipmentBarWidget : public UUserWidget, public IInitWidgetByCharacter
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipmentBar")
	UEquipmentBarComponent* EquipmentBarComponent;

	UFUNCTION()
	void OnEquipmentBarChange();


	void SetChosenEquipmentBar(int Index);

public:

    virtual void NativeConstruct() override;


	virtual void InitWidgetByCharacter(ABaseCharacter* Character) override;
};
