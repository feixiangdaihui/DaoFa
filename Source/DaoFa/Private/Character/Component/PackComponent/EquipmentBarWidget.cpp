// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/EquipmentBarWidget.h"
#include "Character/Component/PackComponent/ShowTrigger.h"

void UEquipmentBarWidget::WearEquipment(TScriptInterface<IShowTrigger> Equipment, int Index)
{

	
	if (Index >= 0 && Index < Size)
	{
		for (int i = 0; i < EquipmentBar.Num(); i++)
		{
			if (EquipmentBar[i].GetObject() == Equipment.GetObject())
			{
				if (i != Index)
				{
					if(EquipmentBar[Index]!=nullptr)
					{
						EquipmentBar[i] = EquipmentBar[Index];
						OnEquipmentWear(i);
					}
					else
						TakeOffEquipment(Equipment);
					EquipmentBar[Index] = Equipment;
					OnEquipmentWear(Index);
				}
				return;
			}
		}
		EquipmentBar[Index] = Equipment;
		OnEquipmentWear(Index);
	}
}

void UEquipmentBarWidget::TakeOffEquipment(TScriptInterface<IShowTrigger> Equipment)
{

	for (int i = 0; i < EquipmentBar.Num(); i++)
	{
		if (EquipmentBar[i].GetObject() == Equipment.GetObject())
		{
			EquipmentBar[i] = nullptr;
			OnEquipmentTakeOff(i);
		}
	}
}




void UEquipmentBarWidget::TriggeredByLongPress(int Index)
{
	if (Index >= 0 && Index < Size)
	{
		if (EquipmentBar[Index].GetObject())
		{
			EquipmentBar[Index]->TriggeredByLongPress();
		}
	}
}

void UEquipmentBarWidget::TriggeredByShortPress(int Index)
{
	if (Index >= 0 && Index < Size)
	{
		if (EquipmentBar[Index].GetObject())
		{
			EquipmentBar[Index]->TriggeredByShortPress();
		}
	}
}

bool UEquipmentBarWidget::IsEquipmentValid(int Index)
{
	return EquipmentBar[Index].GetObject() != nullptr;
}

UEquipmentBarWidget::UEquipmentBarWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	EquipmentBar.Init(nullptr, Size);
}

