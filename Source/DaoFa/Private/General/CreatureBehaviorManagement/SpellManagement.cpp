#include "General/CreatureBehaviorManagement/SpellManagement.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "Character/Component/PackComponent/SpellCoolComponent.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
// Sets default values for this component's properties
USpellManagement::USpellManagement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USpellManagement::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void USpellManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USpellManagement::CheckForSpell(APackObject* Equipment)
{
	if (Equipment->GetSpellInfo().SpellCoolComponent->IsCoolingNow())
		return false;

	FPackObjectSpellInfo SpellInfo = Equipment->GetSpellInfo();
	switch (SpellInfo.EquipmentSpellType)
	{
	case EEquipmentSpellType::Continuous:
		if (GetBlueValue->IsEmpty())
			return false;
		return true;
	case EEquipmentSpellType::OnlyLongPress:
		return true;
	case EEquipmentSpellType::ShortAndLongPress:
		if (GetBlueValue->GetCurrentValue() >= SpellInfo.ShortPressBlueCost)
			return true;
		return false;
	default:
		return false;
		
	}
}

void USpellManagement::SpellBegin(APackObject* Equipment)
{
	FPackObjectSpellInfo SpellInfo = Equipment->GetSpellInfo();
	Equipment->SetCanBeWearOrTakeOff(false);
	SpellBeginTimeMap.Add(Equipment, GetWorld()->GetTimeSeconds());
	switch (SpellInfo.EquipmentSpellType)
	{
	case EEquipmentSpellType::Continuous:
		Equipment->TriggeredByShortPress();
		break;
	case EEquipmentSpellType::OnlyShortPress:
		SetBlueValue->SubtractValue(SpellInfo.LongPressBlueCost);
		break;
	case EEquipmentSpellType::ShortAndLongPress:
		SetBlueValue->SubtractValue(SpellInfo.ShortPressBlueCost);
		break;
	default:
		break;
	}
}

bool USpellManagement::SpellLoop(APackObject* Equipment, float DeltaTime)
{
	FPackObjectSpellInfo SpellInfo = Equipment->GetSpellInfo();
	switch (SpellInfo.EquipmentSpellType)
	{
	case EEquipmentSpellType::Continuous:
		if (!SetBlueValue->SubtractValue(SpellInfo.OngoingBlueCostBySecond * DeltaTime))
		{
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}



bool USpellManagement::SpellEnd(APackObject* Equipment)
{
	FPackObjectSpellInfo SpellInfo = Equipment->GetSpellInfo();
	float BeginTime=0.0f;
	if (SpellBeginTimeMap.Contains(Equipment))
	{
		BeginTime = SpellBeginTimeMap[Equipment];
		SpellBeginTimeMap.Remove(Equipment);
	}
	else
	{
		return false;
	}
	//先设为可穿戴，再触发，因为触发函数可能会改变可穿戴状态，但是这里太过耦合，先放在这里
	Equipment->SetCanBeWearOrTakeOff(true);
	switch (SpellInfo.EquipmentSpellType)
	{
	case EEquipmentSpellType::Continuous:
		Equipment->TriggeredByShortPress();
		break;

	case EEquipmentSpellType::OnlyLongPress:
		if (BeginTime && GetWorld()->GetTimeSeconds() - BeginTime > SpellInfo.LongPressTime && GetBlueValue->GetCurrentValue() >= SpellInfo.LongPressBlueCost)
		{
			Equipment->TriggeredByLongPress();
			SetBlueValue->SubtractValue(SpellInfo.LongPressBlueCost);
		}
		break;

	case EEquipmentSpellType::ShortAndLongPress:
		if (BeginTime && GetWorld()->GetTimeSeconds() - BeginTime > SpellInfo.LongPressTime && GetBlueValue->GetCurrentValue() >= SpellInfo.LongPressBlueCost)
		{
			Equipment->TriggeredByLongPress();
			SetBlueValue->SubtractValue(SpellInfo.LongPressBlueCost);
		}
		else
		{
			Equipment->TriggeredByShortPress();
		}

		break;
	case EEquipmentSpellType::OnlyShortPress:
		Equipment->TriggeredByShortPress();
		break;
	default:
		break;
	}
	return true;
}
