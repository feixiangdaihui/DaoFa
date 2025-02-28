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



void USumEquipmentBarWidget::TriggeredByLongPress( int SpecificIndex)
{
	switch (CurrentChosenIndex)
	{
	case 0:
		FaShuEquipmentBar->TriggeredByLongPress(SpecificIndex);
		break;
	case 1:
		FaBaoEquipmentBar->TriggeredByLongPress(SpecificIndex);
		break;
	case 2:
		FuLuEquipmentBar->TriggeredByLongPress(SpecificIndex);
		break;
	default:
		break;
	}
}

void USumEquipmentBarWidget::TriggeredByShortPress( int SpecificIndex)
{
	switch (CurrentChosenIndex)
	{
	case 0:
		FaShuEquipmentBar->TriggeredByShortPress(SpecificIndex);
		break;
	case 1:
		FaBaoEquipmentBar->TriggeredByShortPress(SpecificIndex);
		break;
	case 2:
		FuLuEquipmentBar->TriggeredByShortPress(SpecificIndex);
		break;
	default:
		break;
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

bool USumEquipmentBarWidget::IsEquipmentValid(int Index)
{
	switch (CurrentChosenIndex)
	{
	case 0:
		return FaShuEquipmentBar->IsEquipmentValid(Index);
		break;
	case 1:
		return FaBaoEquipmentBar->IsEquipmentValid(Index);
		break;
	case 2:
		return FuLuEquipmentBar->IsEquipmentValid(Index);
		break;
	default:
		break;
	}
	return false;
}

