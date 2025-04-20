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
protected:

	UPROPERTY(SaveGame)
	FString SaveDataString;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	bool IsTest = false;


	void SetIsTest(bool Value) { IsTest = Value; }

	UBaseSaveGame* GetBaseSaveGame(FString SlotName);


	void SaveISaveLoadDataArray(FString SlotName, TArray<TScriptInterface<ISaveLoadData>> ISaveLoadDataArray);

	void LoadISaveLoadDataArray(UBaseSaveGame* LoadBaseSaveGame, TArray<TScriptInterface<ISaveLoadData>> ISaveLoadDataArray);




};
