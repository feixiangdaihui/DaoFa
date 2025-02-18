// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UpdateEquipmentInterface.generated.h"



class APackObject;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUpdateEquipmentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAOFA_API IUpdateEquipmentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void WearEquipment(APackObject* Equipment, int SpecificIndex=-1) = 0;

	virtual void TakeOffEquipment(APackObject* Equipment) = 0;
};
