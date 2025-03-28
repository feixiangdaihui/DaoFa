// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackComponent.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Character/Component/PackComponent/PackWidget.h"
#include"PlayerController/BasePlayerController.h"
#include "Character/Component/PackComponent/EquipmentBarComponent.h"
#include "Character/Component/PackComponent/PackObject.h"
// Sets default values for this component's properties
UPackComponent::UPackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	// ...
}


// Called when the game starts
void UPackComponent::BeginPlay()
{
	Super::BeginPlay();


	OwnerController = GetOwner()->GetInstigatorController<ABasePlayerController>();
	EquipmentBarComponent = GetOwner()->FindComponentByClass<UEquipmentBarComponent>();

	// ...
	
}




void UPackComponent::OnPackObjectExhausted(APackObject* PackObject)
{
	TakeOffEquipment(PackObject);
}

// Called every frame
void UPackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPackComponent::WearEquipmentByClass(TSubclassOf<APackObject> EquipmentClass, int SpecificIndex)
{
	APackObject* Equipment = GetWorld()->SpawnActor<APackObject>(EquipmentClass);
	if (Equipment)
	{
		WearEquipment(Equipment, SpecificIndex);
	}
}

void UPackComponent::WearEquipment( APackObject* Equipment, int SpecificIndex)
{
	Equipment->AttachToCreatureByActor(GetOwner());
	int Size = Equipment->GetSizeInPack();
	if (Size + CurrentSize > SumSize)
	{
		return;
	}
	CurrentSize += Size;
	Equipment->OnPackObjectExhausted.AddDynamic(this, &UPackComponent::OnPackObjectExhausted);
	switch (Equipment->GetEquipmentType())
	{
	case EEquipmentType::FASHU:
		FaShuArray.Add(Equipment);
		SpecificIndex = FaShuArray.Num() - 1;
		break;
	case EEquipmentType::FABAO:
		FaBaoArray.Add(Equipment);
		SpecificIndex = FaBaoArray.Num() - 1;
		break;
	case EEquipmentType::FULU:
		FuLuArray.Add(Equipment);
		SpecificIndex = FuLuArray.Num() - 1;
		break;
	default:
		break;
	}
	if (EquipmentBarComponent)
	{
		EquipmentBarComponent->WearEquipment(Equipment, SpecificIndex);
	}
	
}

void UPackComponent::TakeOffEquipment(APackObject* Equipment)
{
	CurrentSize -= Equipment->GetSizeInPack();
	if (EquipmentBarComponent)
	{
		EquipmentBarComponent->TakeOffEquipment(Equipment);
	}
	switch (Equipment->GetEquipmentType())
	{
	case EEquipmentType::FASHU:
		FaShuArray.Remove(Equipment);

		break;
	case EEquipmentType::FABAO:
		FaBaoArray.Remove(Equipment);
		break;
	case EEquipmentType::FULU:
		FuLuArray.Remove(Equipment);
		break;
	default:
		break;
	}


}














TArray<APackObject*> UPackComponent::GetArrayByType(EEquipmentType TypeIndex)
{
	switch (TypeIndex)
	{
	case EEquipmentType::FASHU:
		return FaShuArray;
	case EEquipmentType::FABAO:
		return FaBaoArray;
	case EEquipmentType::FULU:
		return FuLuArray;
	default:
		break;
	}
	return TArray<TObjectPtr<APackObject>>();
}

APackObject* UPackComponent::GetPackObjectByTypeAndIndex(EEquipmentType TypeIndex, int Index)
{
	TArray<APackObject*> TempArray = GetArrayByType(TypeIndex);
	if (TempArray.IsValidIndex(Index))
	{
		return TempArray[Index];
	}
	return nullptr;
}



