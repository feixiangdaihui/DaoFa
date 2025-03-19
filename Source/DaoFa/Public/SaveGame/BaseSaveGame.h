// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "General/Interface/SaveLoadData.h"
#include "BaseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DAOFA_API UBaseSaveGame : public USaveGame
{
	GENERATED_BODY()
private:

	UPROPERTY(SaveGame)
	FString SaveDataString;

	TArray<TScriptInterface<ISaveLoadData>> ISaveLoadDataArray;

	bool IsTest = false;

public:

	void SetIsTest(bool Value) { IsTest = Value; }

	void InitISaveLoadData(TArray<TScriptInterface<ISaveLoadData>> InISaveLoadDataArray) {
		ISaveLoadDataArray.Empty();
		ISaveLoadDataArray = InISaveLoadDataArray;

	}

	UFUNCTION(BlueprintCallable)
	void SaveGameMethod(FString SlotName);

	UFUNCTION(BlueprintCallable)
	void LoadGameMethod(FString SlotName);

};
