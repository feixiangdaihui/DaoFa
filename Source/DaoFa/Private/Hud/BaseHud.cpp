// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "Character/Component/PackComponent/PackWidget.h"
#include "PlayerController/BasePlayerController.h"

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
			PackWidget->InitPackWidget(OwnerCharacter->PackComponent);

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