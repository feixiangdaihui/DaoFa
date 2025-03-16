// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"






void USumEquipmentBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USumEquipmentBarWidget::SetEquipmentBar(int Index, TArray<APackObject*> EquipmentBar)
{
	switch (Index)
	{
	case 0:
		FaShuEquipmentBar->SetEquipmentBar(EquipmentBar);
		break;
	case 1:
		FaBaoEquipmentBar->SetEquipmentBar(EquipmentBar);
		break;
	case 2:
		FuLuEquipmentBar->SetEquipmentBar(EquipmentBar);
		break;
	default:
		break;
	}
}



void USumEquipmentBarWidget::SetChosenEquipmentBar(int Index)
{
	FaShuEquipmentBar->SetChosen(Index == 0);
	FaBaoEquipmentBar->SetChosen(Index == 1);
	FuLuEquipmentBar->SetChosen(Index == 2);
}



