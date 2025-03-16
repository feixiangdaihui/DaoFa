// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/PackWidget.h"
#include "PlayerController/BasePlayerController.h"
#include "Hud/Widget/RealTimeWidget.h"
#include "Hud/Widget/EnemyInfoWidget.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Character/Component/PackComponent/EquipmentBarComponent.h"

ABaseHud::ABaseHud()
{
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
		SumEquipmentBarWidget = CreateWidget<USumEquipmentBarWidget>(GetWorld(), SumEquipmentBarWidgetClass);
		if(SumEquipmentBarWidget)
		{
			SumEquipmentBarWidget->AddToViewport();
			OwnerCharacter->GetEquipmentBarComponent()->InitSumEquipmentBarWidget(SumEquipmentBarWidget);
		}



		RealTimeWidget = CreateWidget<URealTimeWidget>(GetWorld(), RealTimeWidgetClass);
		if (RealTimeWidget)
		{
			RealTimeWidget->AddToViewport();
			RealTimeWidget->InitRealTimeWidget(OwnerCharacter->GetHealthComponent(), OwnerCharacter->GetHealthComponent(), OwnerCharacter->GetHealthComponent());
		}


		EnemyInfoWidget = CreateWidget<UEnemyInfoWidget>(GetWorld(), EnemyInfoWidgetClass);
		if (EnemyInfoWidget)
		{
			EnemyInfoWidget->AddToViewport();
			EnemyInfoWidget->InitEnemyInfoWidget(OwnerCharacter->GetEnemyDetector());
		}

		PackWidget = CreateWidget<UPackWidget>(GetWorld(), PackWidgetClass);
		if (PackWidget)
		{
			PackWidget->InitPackWidget(OwnerCharacter->GetPackComponent());
			PackWidget->AddToViewport();
			PackWidget->SetVisibility(ESlateVisibility::Hidden);
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
	if (PackWidget)
	{
		PackWidget->OpenClosePack();
	}
}
