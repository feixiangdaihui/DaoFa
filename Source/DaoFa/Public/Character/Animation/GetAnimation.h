// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GetAnimation.generated.h"


USTRUCT(BlueprintType)
struct FMontageInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	float StartPosition = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	bool IsLooping = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	float LoopStartPosition = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	bool ShouldStopOtherMontage = false;

};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGetAnimation : public UInterface
{
	GENERATED_BODY()
};

class  DAOFA_API IGetAnimation
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FMontageInfo GetMontageInfo() = 0;
};
