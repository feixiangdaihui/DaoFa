// Fill out your copyright notice in the Description page of Project Settings.


#include "General/Component/InteractComponent.h"
#include "PlayerController/BasePlayerController.h"
#include "PlayerController/Component/InteractManage.h"
#include "Character/BaseCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InteractSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractSphereComponent"));
	//设置
	InteractSphereComponent->SetSphereRadius(500.0f);

	InteractSphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	InteractSphereComponent->SetGenerateOverlapEvents(true);
	InteractSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnComponentBeginOverlap);
	InteractSphereComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnEndOverlap);
	InteractSphereComponent->SetupAttachment(this);
	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	InteractSphereComponent->RegisterComponent();
	AActor* Owner = GetOwner();

	if (Owner)
	{

		ABasePlayerController* Controller = Cast<ABasePlayerController>(Owner->GetWorld()->GetFirstPlayerController());
		if (Controller)
		{
			InteractManage = Controller->GetInteractManage();
		}
	}

	// ...

}

// Update the call to `AskForInteract` to use a lambda function instead of a member function pointer.
void UInteractComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsInteractable)
	{
		if (Cast<ABaseCharacter>(OtherActor))
		{
			if (InteractManage)
			{
				// Use a lambda to wrap the member function call
				InteractManage->AskForInteract(InteractText, [this]() { 	OnInteractTriggered.ExecuteIfBound(); });
			}
		}
	}
	else
	{
		return;
	}
}

void UInteractComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ABaseCharacter>(OtherActor))
	{
		if (InteractManage)
		{
			// Use a lambda to wrap the member function call
			InteractManage->EndInteract();
		}
	}
}
