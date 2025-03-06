#include "Character/Component/PackComponent/PODefenseComponent.h"
#include "General/DefenseComponent.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"

// Sets default values for this component's properties
UPODefenseComponent::UPODefenseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	DefenseComponent = CreateDefaultSubobject<UDefenseComponent>(TEXT("DefenseComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// ...
}

// Called when the game starts
