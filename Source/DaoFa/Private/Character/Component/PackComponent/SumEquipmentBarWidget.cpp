// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"






void USumEquipmentBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetChosenEquipmentBar(CurrentChosenIndex);
}

void USumEquipmentBarWidget::WearEquipment( APackObject* Equipment, int SpecificIndex)
{

	switch (Equipment->GetEquipmentType())
	{
	case EEquipmentType::FASHU:
		FaShuEquipmentBar->WearEquipment(Equipment, SpecificIndex);
		break;
	case EEquipmentType::FABAO:
		FaBaoEquipmentBar->WearEquipment(Equipment, SpecificIndex);
		break;
	case EEquipmentType::FULU:
		FuLuEquipmentBar->WearEquipment(Equipment, SpecificIndex);
		break;
	default:
		break;
	}
}

void USumEquipmentBarWidget::TakeOffEquipment(APackObject* Equipment)
{	
	switch (Equipment->GetEquipmentType())
	{
	case EEquipmentType::FASHU:
		FaShuEquipmentBar->TakeOffEquipment(Equipment);
		break;
	case EEquipmentType::FABAO:
		FaBaoEquipmentBar->TakeOffEquipment(Equipment);
		break;
	case EEquipmentType::FULU:
		FuLuEquipmentBar->TakeOffEquipment(Equipment);
		break;
	default:
		break;
	}
}

APackObject* USumEquipmentBarWidget::GetEquipment(int Index)
{
	switch (CurrentChosenIndex)
	{
	case 0:
		return FaShuEquipmentBar->GetEquipment(Index);
	case 1:
		return FaBaoEquipmentBar->GetEquipment(Index);
	case 2:
		return FuLuEquipmentBar->GetEquipment(Index);
	default:
		return nullptr;
	}
}




void USumEquipmentBarWidget::ChangeChosenEquipmentBarToSmall()
{
	if (CurrentChosenIndex == 0)
		CurrentChosenIndex = EQUIPMENTBAR_NUM - 1;
	else
		CurrentChosenIndex--;
	SetChosenEquipmentBar(CurrentChosenIndex);
}

void USumEquipmentBarWidget::ChangeChosenEquipmentBarToBig()
{
	if (CurrentChosenIndex == EQUIPMENTBAR_NUM - 1)
		CurrentChosenIndex = 0;
	else
		CurrentChosenIndex++;
	SetChosenEquipmentBar(CurrentChosenIndex);
}

void USumEquipmentBarWidget::SetChosenEquipmentBar(int Index)
{
	FaShuEquipmentBar->SetChosen(Index == 0);
	FaBaoEquipmentBar->SetChosen(Index == 1);
	FuLuEquipmentBar->SetChosen(Index == 2);
}



