// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/PackWidget.h"
#include "Character/Component/PackComponent/PackComponent.h"
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


