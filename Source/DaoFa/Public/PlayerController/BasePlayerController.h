// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"
class UInteractManage;
/**
 * 
 */
UCLASS()
class DAOFA_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	int PauseCount = 0;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
	TObjectPtr<UInteractManage> InteractManage;

public:
	ABasePlayerController();
	UFUNCTION(BlueprintCallable, Category = "BasePlayerController")
	void QueryForGamePause(bool WantPause);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	UInteractManage* GetInteractManage() const { return InteractManage; }

};
