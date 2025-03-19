#include "Character/Component/GongFa/BaseMainGongFa.h"
#include"Character/Component/PackComponent/SpellCoolComponent.h"

// Sets default values for this component's properties
UBaseMainGongFa::UBaseMainGongFa()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	FSpellCoolComponent = CreateDefaultSubobject<USpellCoolComponent>(TEXT("FSpellCoolComponent"));
	SSpellCoolComponent = CreateDefaultSubobject<USpellCoolComponent>(TEXT("SSpellCoolComponent"));

	// ...
}

// Called when the game starts
void UBaseMainGongFa::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UBaseMainGongFa::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseMainGongFa::FirstAttack()
{

	FSpellCoolComponent->StartCool();

}

bool UBaseMainGongFa::CheckFirstAttack()
{
	if (FSpellCoolComponent)
		return !FSpellCoolComponent->IsCoolingNow();
	return false;
}

bool UBaseMainGongFa::CheckSecondAttack()
{
	if (SSpellCoolComponent)
		return !SSpellCoolComponent->IsCoolingNow();
	return false;
}

void UBaseMainGongFa::SecondAttack()
{
	SSpellCoolComponent->StartCool();
}
