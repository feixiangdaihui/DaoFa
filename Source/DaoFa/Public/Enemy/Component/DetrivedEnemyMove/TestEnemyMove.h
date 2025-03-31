// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Component/EnemyMove.h"
#include "TestEnemyMove.generated.h"

/**
 * 
 */
UCLASS()
class DAOFA_API UTestEnemyMove : public UEnemyMove
{
	GENERATED_BODY()


protected:

	float WalkBackDistance = 100.0f;

	float WalkVerticalDistance = 1000.0f;

	virtual FVector2D CalMoveVec() override;
	
};
