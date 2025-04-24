// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/Component/InteractManage.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/InputOperationComponent.h"
#include "Hud/Widget/InteractWidget.h"
#include "Hud/BaseHud.h"

// Sets default values for this component's properties
UInteractManage::UInteractManage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractManage::BeginPlay()
{
	Super::BeginPlay();






	// ...
	
}


// Called every frame
void UInteractManage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractManage::AskForInteract(FText InteractText, TFunction<void()> InteractFunc) 
{
	if (InteractFunc == nullptr)
	{
		return;
	}
	if (InteractWidget == nullptr)
	{
		APlayerController* OwnerController = Cast<APlayerController>(GetOwner());
		ABaseHud* OwnerHud = OwnerController ? Cast<ABaseHud>(OwnerController->GetHUD()) : nullptr;
		InteractWidget = OwnerHud ? Cast<UInteractWidget>(OwnerHud->GetWidgetByName("InteractWidget")) : nullptr;
	}
	if(InputOperationComponent==nullptr)
	{
		APlayerController* OwnerController = Cast<APlayerController>(GetOwner());
		ABaseCharacter* ControlledCharacter = OwnerController ? Cast<ABaseCharacter>(OwnerController->GetPawn()) : nullptr;
		InputOperationComponent = ControlledCharacter ? ControlledCharacter->GetInputOperationComponent() : nullptr;
	}

	if (InputOperationComponent&& InteractWidget)
	{
		InteractWidget->PopInteractWidget(InteractText);
		InputOperationComponent->OnInteractTriggered.BindLambda([this, InteractFunc]()
		{
			InteractFunc();
			EndInteract();
		});
	}

	
}

void UInteractManage::EndInteract()
{
	if (InputOperationComponent && InteractWidget)
	{
		InteractWidget->EndPop();
		InputOperationComponent->OnInteractTriggered.Unbind();
	}
}

