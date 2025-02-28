// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/PackWidget.h"
#include "PlayerController/BasePlayerController.h"
#include "Hud/Widget/RealTimeWidget.h"
#include "Character/Component/AttributeComponent/AttributeComponent.h"
#include "Hud/Widget/EnemyInfoWidget.h"

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
			OwnerCharacter->InitSumEquipmentBar(SumEquipmentBarWidget);
		}
		PackWidget = CreateWidget<UPackWidget>(GetWorld(), PackWidgetClass);
		if (PackWidget)
			PackWidget->InitPackWidget(OwnerCharacter->GetPackComponent());

		RealTimeWidget = CreateWidget<URealTimeWidget>(GetWorld(), RealTimeWidgetClass);
		if (RealTimeWidget)
		{
			RealTimeWidget->AddToViewport();
			RealTimeWidget->InitRealTimeWidget(OwnerCharacter->GetAttributeComponent()->GetHealthValue(), OwnerCharacter->GetAttributeComponent()->GetBlueValue(), OwnerCharacter->GetAttributeComponent()->GetPhysicalPowerValue());
		}

		EnemyInfoWidget = CreateWidget<UEnemyInfoWidget>(GetWorld(), EnemyInfoWidgetClass);
		if (EnemyInfoWidget)
		{
			EnemyInfoWidget->AddToViewport();
			EnemyInfoWidget->InitEnemyInfoWidget(OwnerCharacter->GetEnemyDetector());
		}

		OwnerController = Cast<ABasePlayerController>(GetOwningPlayerController());
	}





}

void ABaseHud::DrawHUD()
{
	Super::DrawHUD();

}
void ABaseHud::OpenPack()
{
	if (OwnerController)
	{
		OwnerController->GatherToPauseGame();
	}
	if (PackWidget)
		PackWidget->OpenPack();
}

void ABaseHud::ClosePack()
{
	if (OwnerController)
	{
		OwnerController->GatherToUnPauseGame();
	}
	if (PackWidget)
		PackWidget->ClosePack();
}