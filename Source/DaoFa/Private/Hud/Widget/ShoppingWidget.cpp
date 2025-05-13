// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/ShoppingWidget.h"
#include "PlayerController/BasePlayerController.h"

void UShoppingWidget::Pop(ABusinessman* InBusinessman)
{
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	if (BasePlayerController)
	{
		BasePlayerController->QueryForGamePause(true);
	}
	Businessman = InBusinessman;
	SetVisibility(ESlateVisibility::Visible);
	BPPop(InBusinessman);
}

void UShoppingWidget::EndPop()
{
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	if (BasePlayerController)
	{
		BasePlayerController->QueryForGamePause(false);
	}
	SetVisibility(ESlateVisibility::Hidden);
}

