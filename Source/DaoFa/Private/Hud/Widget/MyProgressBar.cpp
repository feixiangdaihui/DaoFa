// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/MyProgressBar.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
void UMyProgressBar::InitProgressBar(TScriptInterface<IGetValueInterface> ValueInterface)
{
	Value = ValueInterface;
}

float UMyProgressBar::GetPercent() const
{
	if (Value)
	{
		return Value->GetPercentage();
	}
	return 0.0f;
}

