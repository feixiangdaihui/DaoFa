// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Component/DetrivedEnemyMove/TestEnemyMove.h"
#include "Enemy/Component/EnemyTrace.h"

FVector2D UTestEnemyMove::CalMoveVec()
{
    if (EnemyTrace)
    {
        float Distance = EnemyTrace->GetDistanceToTarget();
		if (Distance < WalkBackDistance)
		{
			return EnemyTrace->GetDirAgainstTarget(false);
		}
		else if (Distance < WalkVerticalDistance)
		{
			return EnemyTrace->GetDirVerticalToTarget();
		}
		else
		{
			return EnemyTrace->GetDirAgainstTarget();
		}
    }
	return FVector2D::ZeroVector;
}
