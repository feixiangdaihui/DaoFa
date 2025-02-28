// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/RealTimeWidget.h"
#include "Hud/Widget/MyProgressBar.h"

void URealTimeWidget::InitRealTimeWidget(TScriptInterface<IGetValueInterface> NewHealthValue, TScriptInterface<IGetValueInterface> NewBlueValue, TScriptInterface<IGetValueInterface> NewPhysicalPowerValue)
{
	HealthValue->InitProgressBar(NewHealthValue);
	BlueValue->InitProgressBar(NewBlueValue);
	PhysicalPowerValue->InitProgressBar(NewPhysicalPowerValue);
}

void URealTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HealthValue = NewObject<UMyProgressBar>();
	BlueValue = NewObject<UMyProgressBar>();
	PhysicalPowerValue = NewObject<UMyProgressBar>();
}
