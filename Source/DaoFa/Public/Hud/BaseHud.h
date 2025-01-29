// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHud.generated.h"
class ABaseCharacter;
class UUserWidget;
/**
 * 
 */
UCLASS()
class DAOFA_API ABaseHud : public AHUD
{
	GENERATED_BODY()
protected:



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ABaseCharacter* OwnerCharacter;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;


};
