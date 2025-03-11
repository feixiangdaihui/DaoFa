// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
void ABasePlayerController::QueryForGamePause(bool WantPause)
{
	if (WantPause)
	{
		PauseCount++;
	}
	else
	{
		PauseCount--;
	}
	if (PauseCount > 0)
	{
		SetShowMouseCursor(true);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		SetShowMouseCursor(false);
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		SetInputMode(FInputModeGameOnly());
		PauseCount = 0;
	}
}
