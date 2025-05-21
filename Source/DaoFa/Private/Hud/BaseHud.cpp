// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include "Character/BaseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/PackWidget.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "PlayerController/BasePlayerController.h"
#include "Hud/Widget/RealTimeWidget.h"
#include "Hud/Widget/InteractWidget.h"
#include "Hud/Widget/EnemyInfoWidget.h"
#include "Hud/Widget/ShoppingWidget.h"
#include "Hud/Widget/ReputationWidget.h"


ABaseHud::ABaseHud()
{

	WidgetMap.Add("SumEquipmentBarWidget", { USumEquipmentBarWidget::StaticClass(), nullptr });
	WidgetMap.Add("RealTimeWidget", { URealTimeWidget::StaticClass(), nullptr });
	WidgetMap.Add("ReputationWidget", { UReputationWidget::StaticClass(), nullptr });
	WidgetMap.Add("EnemyInfoWidget", { UEnemyInfoWidget::StaticClass(), nullptr });
	WidgetMap.Add("InteractWidget", { UInteractWidget::StaticClass(), nullptr });
	WidgetMap.Add("ShoppingWidget", { UShoppingWidget::StaticClass(), nullptr });
	WidgetMap.Add("PackWidget", { UPackWidget::StaticClass(), nullptr });

}

void ABaseHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ABaseHud::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ABaseCharacter>(GetOwningPawn());
	if (OwnerCharacter)
	{

		for (auto& WidgetPair : WidgetMap)
		{
			if (WidgetPair.Value.WidgetClass)
			{
				auto Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetPair.Value.WidgetClass);
				if (Widget)
				{
					Widget->AddToViewport();
					if (Widget->Implements<UInitWidgetByCharacter>())
					{
						InitWidgetByCharacterArray.Add(Widget);
					}
					WidgetPair.Value.Widget = Widget;
				}

			}
		}


		for (TScriptInterface<IInitWidgetByCharacter> Widget : InitWidgetByCharacterArray)
		{
			Widget->InitWidgetByCharacter(OwnerCharacter);
		}

		OwnerController = Cast<ABasePlayerController>(GetOwningPlayerController());
	}

	


	
}

void ABaseHud::DrawHUD()
{
	Super::DrawHUD();

}
void ABaseHud::OpenClosePack()
{
	UPackWidget* PackWidget = Cast<UPackWidget>(GetWidgetByName("PackWidget"));
	if (PackWidget)
	{
		PackWidget->OpenClosePack();
	}
}
