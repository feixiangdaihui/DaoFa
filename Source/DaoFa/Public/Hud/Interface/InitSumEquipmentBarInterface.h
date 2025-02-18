// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InitSumEquipmentBarInterface.generated.h"
class USumEquipmentBarWidget;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInitSumEquipmentBarInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAOFA_API IInitSumEquipmentBarInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void InitSumEquipmentBar(USumEquipmentBarWidget* SumEquipmentBarWidget)=0;
};
