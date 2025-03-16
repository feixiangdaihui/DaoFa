// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHud.generated.h"
class ABaseCharacter;
class UUserWidget;
class USumEquipmentBarWidget;
class UPackWidget;
class ABasePlayerController;
class URealTimeWidget;
class UEnemyInfoWidget;
/**
 * 
 */
UCLASS()
class DAOFA_API ABaseHud : public AHUD
{
	GENERATED_BODY()
protected:



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ABaseCharacter* OwnerCharacter;

	//装备栏
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TSubclassOf<USumEquipmentBarWidget> SumEquipmentBarWidgetClass;
	TObjectPtr<USumEquipmentBarWidget> SumEquipmentBarWidget;
	UUserWidget* EquipmentBarWidget;

	//背包
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TSubclassOf<UPackWidget> PackWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category = "Pack")
	TObjectPtr<UPackWidget> PackWidget;


	//角色实时信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RealTime")
	TSubclassOf<URealTimeWidget> RealTimeWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "RealTime")
	TObjectPtr<URealTimeWidget> RealTimeWidget;


	//敌人信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<UEnemyInfoWidget> EnemyInfoWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UEnemyInfoWidget> EnemyInfoWidget;



	ABasePlayerController* OwnerController;
	
public:
	ABaseHud();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;


	void OpenClosePack();

};
