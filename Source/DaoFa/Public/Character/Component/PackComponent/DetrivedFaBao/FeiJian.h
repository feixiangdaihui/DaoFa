// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/FaBao.h"
#include "FeiJian.generated.h"

/**
 * 
 */
UCLASS()
class DAOFA_API AFeiJian : public AFaBao
{
	GENERATED_BODY()
public:

	bool IsInHand = true;


	virtual void TriggeredByShortPress() override;
};
