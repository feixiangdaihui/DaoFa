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
class IInitWidgetByCharacter;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetMessage
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UUserWidget> Widget;

	FWidgetMessage()
	{
		WidgetClass = nullptr;
		Widget = nullptr;
	}
	FWidgetMessage(TSubclassOf<UUserWidget> InWidgetClass, UUserWidget* InWidget)
	{
		WidgetClass = InWidgetClass;
		Widget = InWidget;
	}
};

UCLASS()
class DAOFA_API ABaseHud : public AHUD
{
	GENERATED_BODY()
protected:


	TArray<TScriptInterface<IInitWidgetByCharacter>> InitWidgetByCharacterArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ABaseCharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TMap<FString, FWidgetMessage> WidgetMap;

	ABasePlayerController* OwnerController;
	
public:
	ABaseHud();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;


	void OpenClosePack();

};
