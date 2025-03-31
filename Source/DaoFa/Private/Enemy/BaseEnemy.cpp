// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Enemy/Component/EnemyController.h"
#include "Enemy/Component/EnemyPackComponent.h"
ABaseEnemy::ABaseEnemy()
{
	PackComponent = CreateDefaultSubobject<UEnemyPackComponent>(TEXT("EnemyPackComponent"));
	EnemyController = CreateDefaultSubobject<UEnemyController>(TEXT("EnemyController"));
	WalkSpeed = 50.f;
}

