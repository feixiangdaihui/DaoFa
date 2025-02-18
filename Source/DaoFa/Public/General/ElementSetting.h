// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ElementSetting.generated.h"
#define ELEMENTRESTRAINPOSITIVE 1.2
#define ELEMENTRESTRAINNEGATIVE 0.8


UENUM(BlueprintType)
enum class GElement : uint8
{
	Matel,
	Wood,
	Water,
	Fire,
	Earth,
};
UENUM(BlueprintType)
enum class GElementRestrain : uint8
{
	Negative,
	Neutral,
	Positive,
};
/**
 * 
 */
UCLASS()
class DAOFA_API UElementSetting : public UObject
{
	GENERATED_BODY()
public:
	static GElementRestrain GetElementRestrain(GElement self, GElement other);
};
