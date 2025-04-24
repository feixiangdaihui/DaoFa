// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShoppingWidget.generated.h"

class UBusinessmanPackComponent;
/**
 * 
 */
UCLASS()
class DAOFA_API UShoppingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Shopping")
	void PopShoppingWidget(UBusinessmanPackComponent* BusinessmanPackComponent);
	
};
