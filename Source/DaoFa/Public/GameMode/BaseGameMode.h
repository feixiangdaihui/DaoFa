// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DAOFA_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;




	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
