// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackWidget.h"
#include "Character/Component/PackComponent/PackComponent.h"
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
void UPackWidget::InitPackWidget(UPackComponent* InPackComponent)
{
	if (InPackComponent)
	{
		PackComponent = InPackComponent;
		SumEquipmentBarWidget = PackComponent->GetSumEquipmentBarWidget();
	}
	else
		UE_LOG(LogTemp, Error, TEXT("InPackComponent is nullptr"));
}


