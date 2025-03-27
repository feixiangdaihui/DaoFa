// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Enemy/Component/EnemyController.h"
ABaseEnemy::ABaseEnemy()
{

	EnemyController = CreateDefaultSubobject<UEnemyController>(TEXT("EnemyController"));
}

