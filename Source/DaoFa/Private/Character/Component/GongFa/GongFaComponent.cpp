#include "Character/Component/GongFa/GongFaComponent.h"
#include "Character/Component/GongFa/BaseMainGongFa.h"

// Sets default values for this component's properties
UGongFaComponent::UGongFaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGongFaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UGongFaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGongFaComponent::SetMainGongFa(TSubclassOf<UBaseMainGongFa> MainGongFaClass)
{
	if (MainGongFaClass)
	{
		MainGongFa = NewObject<UBaseMainGongFa>(this, MainGongFaClass);
	}
}


