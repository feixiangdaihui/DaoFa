// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputUpdateInterface.generated.h"
UENUM(BlueprintType)
enum class InputAnimation : uint8
{
	Walk,
	Run,
	Idle,
	Jump,
	Fall,
	FirstAttack,
	SecondAttack,
	SpellLoop,
	SpellEnd,
	Dodge,
	EndRun,
	NONE,
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputUpdateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAOFA_API IInputUpdateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void UpdateInput(InputAnimation Input) = 0;

	virtual bool CheckInput(InputAnimation Input) = 0;

};
