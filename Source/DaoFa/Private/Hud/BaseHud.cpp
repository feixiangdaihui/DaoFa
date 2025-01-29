// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include "Character/BaseCharacter.h"
#include "Blueprint/UserWidget.h"

void ABaseHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ABaseHud::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ABaseCharacter>(GetOwningPawn());




}

void ABaseHud::DrawHUD()
{
	Super::DrawHUD();

}
