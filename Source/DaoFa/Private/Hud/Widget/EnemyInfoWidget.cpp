// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/Widget/EnemyInfoWidget.h"
#include "Hud/Widget/MyProgressBar.h"
#include "General/EnemyDetector.h"
#include "Enemy/BaseEnemy.h"
#include "Character/Component/AttributeComponent/HealthComponent.h"
#include "Character/BaseCharacter.h"

void UEnemyInfoWidget::UpdateEnemy()
{
	if (EnemyDetector)
	{
		TArray<AActor*> Enemies = EnemyDetector->DetectEnemies();
		if (Enemies.Num() > 0)
		{
			ABaseEnemy* Enemy ;
			for (auto Actor : Enemies)
			{
				Enemy = Cast<ABaseEnemy>(Actor);
				if (Enemy)
				{
					EnemyHealthValue->InitProgressBar(Enemy->GetHealthComponent());
					EnemyName = Enemy->GetObjectName();
					IsEnemyPresent = true;
				}
			}
		}
		else
			IsEnemyPresent = false;
	}
	else
		IsEnemyPresent = false;
}




void UEnemyInfoWidget::InitWidgetByCharacter(ABaseCharacter* Character)
{
	if (Character) 
	{
		EnemyDetector = Character->GetEnemyDetector();
	}
}

void UEnemyInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//计时器
	GetWorld()->GetTimerManager().SetTimer(UpdateEnemyTimer, this, &UEnemyInfoWidget::UpdateEnemy, UpdateEnemyInterval, true);

	GetWorld()->GetTimerManager().SetTimer(UpdateEnemyInfoTimer, this, &UEnemyInfoWidget::UpdateEnemyInfo, UpdateInfoInterval, true);
	
	EnemyHealthValue = NewObject<UMyProgressBar>();
	



}



