#include "Character/Component/PackComponent/EquipmentBarComponent.h"
#include "Character/Component/PackComponent/PackObject.h"
// Sets default values for this component's properties
UEquipmentBarComponent::UEquipmentBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	for (int i = 0; i < EQUIPMENTBAR_NUM; i++)
	{
		for (int j = 0; j < EQUIPMENTBAR_SIZE; j++)
			EquipmentBar[i][j] = nullptr;
	}

	// ...
}

// Called when the game starts
void UEquipmentBarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UEquipmentBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentBarComponent::WearEquipment(APackObject* Equipment, int SpecificIndex)
{
	int Index = static_cast<int>(Equipment->GetEquipmentType());
	if (SpecificIndex >= 0 && SpecificIndex < EQUIPMENTBAR_SIZE)
	{
		for (int i = 0; i <EQUIPMENTBAR_NUM; i++)
		{
			if (EquipmentBar[Index][i] == Equipment)
			{
				if (i != SpecificIndex)
				{
					if (EquipmentBar[Index][SpecificIndex] != nullptr)
					{
						EquipmentBar[Index][i] = EquipmentBar[Index][SpecificIndex];
					}
					else
						TakeOffEquipment(Equipment);
					EquipmentBar[Index][SpecificIndex] = Equipment;
					OnEquipmentBarChange.Broadcast();
				}
				return;
			}
		}
		EquipmentBar[Index][SpecificIndex] = Equipment;
		OnEquipmentBarChange.Broadcast();
	}
}

void UEquipmentBarComponent::TakeOffEquipment(APackObject* Equipment)
{
	int Index = static_cast<int>(Equipment->GetEquipmentType());
	for (int i = 0; i < EQUIPMENTBAR_SIZE; i++)
	{
		if (EquipmentBar[Index][i] == Equipment)
		{
			EquipmentBar[Index][i] = nullptr;
			OnEquipmentBarChange.Broadcast();
			return;
		}
	}
}


void UEquipmentBarComponent::ChangeChosenEquipmentBarToSmall()
{
	if (CurrentChosenIndex == 0)
		CurrentChosenIndex = EQUIPMENTBAR_NUM - 1;
	else
		CurrentChosenIndex--;
	OnEquipmentBarChange.Broadcast();


}

void UEquipmentBarComponent::ChangeChosenEquipmentBarToBig()
{
	if (CurrentChosenIndex == EQUIPMENTBAR_NUM - 1)
		CurrentChosenIndex = 0;
	else
		CurrentChosenIndex++;
	OnEquipmentBarChange.Broadcast();
}
