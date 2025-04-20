// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/RealTimeWidget.h"
#include "Hud/Widget/MyProgressBar.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"


void URealTimeWidget::InitWidgetByCharacter(ABaseCharacter* Character)
{
	if (Character)
	{
		HealthValue->InitProgressBar(Character->GetHealthComponent());
		BlueValue->InitProgressBar(Character->GetBlueComponent());
		PhysicalPowerValue->InitProgressBar(Character->GetPhysicalPowerComponent());
	}
}

void URealTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HealthValue = NewObject<UMyProgressBar>();
	BlueValue = NewObject<UMyProgressBar>();
	PhysicalPowerValue = NewObject<UMyProgressBar>();
}
