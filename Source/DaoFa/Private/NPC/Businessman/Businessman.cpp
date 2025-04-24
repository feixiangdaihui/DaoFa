// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Businessman/Businessman.h"
#include "NPC/Businessman/BusinessmanPackComponent.h"
#include "General/Component/InteractComponent.h"
#include "Hud/Widget/ShoppingWidget.h"
#include "Hud/BaseHud.h"
#include "Components/SphereComponent.h"
#include "PlayerController/BasePlayerController.h"

void ABusinessman::BeginPlay()
{
	Super::BeginPlay();
	InteractComponent->OnInteractTriggered.BindUObject(this, &ABusinessman::OpenShoppingWidget);
}

ABusinessman::ABusinessman()
{
	PrimaryActorTick.bCanEverTick = true;
	BusinessmanPackComponent = CreateDefaultSubobject<UBusinessmanPackComponent>(TEXT("BusinessmanPackComponent"));
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
}

void ABusinessman::OpenShoppingWidget()
{
	if (BusinessmanPackComponent)
	{
		ABaseHud* BaseHud = Cast<ABaseHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (BaseHud)
		{
			UShoppingWidget* ShoppingWidget = Cast<UShoppingWidget>(BaseHud->GetWidgetByName("ShoppingWidget"));
			if(ShoppingWidget)
			{
				ShoppingWidget->PopShoppingWidget(BusinessmanPackComponent);
				ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
				if (BasePlayerController)
				{
					BasePlayerController->QueryForGamePause(true);
				}
			}
		}


	}
}
