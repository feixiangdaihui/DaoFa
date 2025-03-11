// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class DAOFA_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	int PauseCount = 0;
public:
	UFUNCTION(BlueprintCallable, Category = "BasePlayerController")
	void QueryForGamePause(bool WantPause);
};
