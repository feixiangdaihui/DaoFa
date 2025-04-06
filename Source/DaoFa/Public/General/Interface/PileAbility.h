// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PileAbility.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class  UPileAbility : public UInterface
{
	GENERATED_BODY()
};

class DAOFA_API IPileAbility
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Pile(TScriptInterface<IPileAbility> PileTarget) = 0;

	virtual int GetNumbers() = 0;

};
