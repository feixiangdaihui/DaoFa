// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/ReputationWidget.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/Reputation/ReputationComponent.h"
#include "Character/Component/Reputation/FaceComponent.h"

void UReputationWidget::InitWidgetByCharacter(ABaseCharacter* Character)
{
	if (Character)
	{
		ReputationComponent = Character->GetReputationComponent();
		if (ReputationComponent)
		{
			FaceComponent = ReputationComponent->GetFaceComponent();
		}
	}
}
