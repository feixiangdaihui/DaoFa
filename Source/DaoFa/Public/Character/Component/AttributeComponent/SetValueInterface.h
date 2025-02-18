// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SetValueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USetValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAOFA_API ISetValueInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetCurrentValue(float NewValue) = 0;
	virtual void SetMaxValue(float NewValue) = 0;
	virtual void SetPercentage(float NewValue) = 0;
	virtual void SetFull() = 0;
	virtual void SetEmpty() = 0;
	virtual void AddValue(float Value) = 0;
	virtual void AddPercentage(float Value) = 0;
	virtual bool SubtractValue(float Value) = 0;
	virtual bool SubtractPercentage(float Value) = 0;

};
