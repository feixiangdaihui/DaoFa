// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveLoadData.generated.h"





// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveLoadData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAOFA_API ISaveLoadData
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FJsonObject SaveDataMethod() const = 0;
	
	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) = 0;

	virtual FString GetKey()const = 0;
};
