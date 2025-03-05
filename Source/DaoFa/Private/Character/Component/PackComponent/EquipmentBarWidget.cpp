// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/EquipmentBarWidget.h"

void UEquipmentBarWidget::WearEquipment(APackObject* Equipment, int Index)
{

	
	if (Index >= 0 && Index < Size)
	{
		for (int i = 0; i < EquipmentBar.Num(); i++)
		{
			if (EquipmentBar[i]  == Equipment )
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

void UEquipmentBarWidget::TakeOffEquipment(APackObject* Equipment)
{

	for (int i = 0; i < EquipmentBar.Num(); i++)
	{
		if (EquipmentBar[i]  == Equipment )
		{
			EquipmentBar[i] = nullptr;
			OnEquipmentTakeOff(i);
		}
	}
}








UEquipmentBarWidget::UEquipmentBarWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	EquipmentBar.Init(nullptr, Size);
}

