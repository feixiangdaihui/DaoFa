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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TSubclassOf<USumEquipmentBarWidget> SumEquipmentBarWidgetClass;
	TObjectPtr<USumEquipmentBarWidget> SumEquipmentBarWidget;
	UUserWidget* EquipmentBarWidget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TSubclassOf<UPackWidget> PackWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Pack")
	TObjectPtr<UPackWidget> PackWidget;

	ABasePlayerController* OwnerController;
	
public:
	ABaseHud();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	USumEquipmentBarWidget* GetSumEquipmentBarWidget() { return SumEquipmentBarWidget; }

	void OpenPack();

	void ClosePack();
};
