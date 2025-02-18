// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

void ABasePlayerController::GatherToPauseGame()
{
	SetShowMouseCursor(true);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
	SetInputMode(FInputModeGameAndUI());
}

void ABasePlayerController::GatherToUnPauseGame()
{
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
