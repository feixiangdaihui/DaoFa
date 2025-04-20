// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackWidget.h"
#include "Character/BaseCharacter.h"
#include"PlayerController/BasePlayerController.h"

void UPackWidget::OpenClosePack()
{
	APlayerController* PlayerController= GetOwningLocalPlayer()->GetPlayerController(GetWorld());
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(PlayerController);

	if (BasePlayerController)
	{
		if (GetVisibility() == ESlateVisibility::Visible)
		{
			BasePlayerController->QueryForGamePause(false);
			ClosePack();
		}
		else
		{
			BasePlayerController->QueryForGamePause(true);
			OpenPack();
		}
	}
}
void UPackWidget::InitWidgetByCharacter(ABaseCharacter* Character)
{
	if (Character)
	{
		PackComponent = Character->GetPackComponent();
		SetVisibility(ESlateVisibility::Hidden);
	}
}

