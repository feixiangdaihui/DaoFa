// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Character/Component/PackComponent/EquipmentBarComponent.h"
#include "Character/BaseCharacter.h"





void USumEquipmentBarWidget::OnEquipmentBarChange()
{
	FaShuEquipmentBar->SetEquipmentBar(EquipmentBarComponent->GetEquipmentBar(0));
	FaBaoEquipmentBar->SetEquipmentBar(EquipmentBarComponent->GetEquipmentBar(1));
	FuLuEquipmentBar->SetEquipmentBar(EquipmentBarComponent->GetEquipmentBar(2));
	SetChosenEquipmentBar(EquipmentBarComponent->GetCurrentChosenIndex());
}

void USumEquipmentBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}




void USumEquipmentBarWidget::SetChosenEquipmentBar(int Index)
{
	FaShuEquipmentBar->SetChosen(Index == 0);
	FaBaoEquipmentBar->SetChosen(Index == 1);
	FuLuEquipmentBar->SetChosen(Index == 2);
}



void USumEquipmentBarWidget::InitWidgetByCharacter(ABaseCharacter* Character)
{
	EquipmentBarComponent = Character->GetEquipmentBarComponent();
	EquipmentBarComponent->OnEquipmentBarChange.AddDynamic(this, &USumEquipmentBarWidget::OnEquipmentBarChange);
	OnEquipmentBarChange();

}



