// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/InteractWidget.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/InputOperationComponent.h"
#include"PlayerController/BasePlayerController.h"





void UInteractWidget::PopInteractWidget(FText InteractText)
{

	UpdateText(InteractText);
	SetVisibility(ESlateVisibility::Visible);

}

void UInteractWidget::EndPop()
{
	SetVisibility(ESlateVisibility::Hidden); 
}

