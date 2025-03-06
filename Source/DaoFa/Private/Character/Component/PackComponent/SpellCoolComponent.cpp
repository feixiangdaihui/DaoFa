#include "Character/Component/PackComponent/SpellCoolComponent.h"

// Sets default values for this component's properties
USpellCoolComponent::USpellCoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpellCoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void USpellCoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsCooling)
	{
		SetCurrentValue(CoolTimeCounter - DeltaTime);
	}
	// ...
}

void USpellCoolComponent::StartCool()
{
	IsCooling = true;
	CoolTimeCounter = CoolTime;
}

void USpellCoolComponent::SetCurrentValue(float Value)
{
	CoolTimeCounter = FMath::Max(0.0f,FMath::Min(Value, CoolTime));
	if (CoolTimeCounter == 0)
	{
		IsCooling = false;
	}
}
