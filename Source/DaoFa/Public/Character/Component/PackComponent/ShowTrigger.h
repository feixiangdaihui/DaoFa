// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShowTrigger.generated.h"

class UTexture2D;
class ABaseCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UShowTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAOFA_API IShowTrigger
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "ShowTrigger")
	virtual UTexture2D* GetIcon()const = 0;

	virtual void TriggeredByShortPress() = 0;
	virtual void TriggeredByLongPress() = 0;

	UFUNCTION(BlueprintCallable, Category = "ShowTrigger")
	virtual int GetQunatity() const = 0;


};
