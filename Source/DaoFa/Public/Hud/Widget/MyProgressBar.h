// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProgressBar.generated.h"
class IGetValueInterface;
/**
 * 
 */
UCLASS()
class DAOFA_API UMyProgressBar : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitProgressBar(TScriptInterface<IGetValueInterface> ValueInterface);

	UFUNCTION(BlueprintCallable)
	float GetPercent() const;

private:
	TScriptInterface<IGetValueInterface> Value;

};
