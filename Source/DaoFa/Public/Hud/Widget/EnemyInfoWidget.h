// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hud/Interface/InitWidgetByCharacter.h"
#include "EnemyInfoWidget.generated.h"
class IGetValueInterface;
class UMyProgressBar;
class UEnemyDetector;
class ACreature;
/**
 * 
 */
UCLASS()
class DAOFA_API UEnemyInfoWidget : public UUserWidget, public IInitWidgetByCharacter
{
	GENERATED_BODY()
	
private:
	void UpdateEnemy();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UMyProgressBar> EnemyHealthValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	FText EnemyName;

	UEnemyDetector* EnemyDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	float UpdateEnemyInterval = 1.0f;



	FTimerHandle UpdateEnemyTimer;
	FTimerHandle UpdateEnemyInfoTimer;

	ACreature* OwnerCreature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	bool IsEnemyPresent = false;

	//蓝图实现
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEnemyInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float UpdateInfoInterval = 0.1f;


public:

	virtual void InitWidgetByCharacter(ABaseCharacter* Character) override;
	virtual void NativeConstruct() override;
	

};
