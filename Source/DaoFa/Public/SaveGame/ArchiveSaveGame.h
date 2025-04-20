// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGame/BaseSaveGame.h"
#include "ArchiveSaveGame.generated.h"

/**
 * 
 */

#define MAX_SLOT_NUMS 5
 //slot index 0-4

USTRUCT(BlueprintType)
struct FArchiveData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, SaveGame)
	int SlotIndex = -1;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	bool IsEmpty = true;
};
UCLASS()
class DAOFA_API UArchiveSaveGame : public UBaseSaveGame
{
	GENERATED_BODY()
private:
	const FString SaveSlotName = "ArchiveSaveSlot";

	int CurrentSlotIndex = -1;//-1 means no slot selected

	FString GetSlotNameByIndex(int Index) const
	{
		return SaveSlotName + FString::Printf(TEXT("%d"), Index);
	}

	bool IsValidCurrentSlotIndex() const
	{
		return CurrentSlotIndex >= 0 && CurrentSlotIndex < MAX_SLOT_NUMS;
	}

	TArray<TScriptInterface<ISaveLoadData>> GetArchiveWantedToSaveArray(UWorld* World)const;

protected:


	UPROPERTY(SaveGame)
	FArchiveData ArchiveData;

public:

	UFUNCTION(BlueprintCallable)
	TArray<FArchiveData> GetArchiveDataArray() const;


	void SaveArchiveMethod(UWorld* World,bool IsExit = false);


	void LoadArchiveMethod(UWorld* World);


	UFUNCTION(BlueprintCallable)
	int GetCurrentSlotIndex() const { return CurrentSlotIndex; }


	//-1 means no slot selected
	void ChangeCurrentSlotIndex(int NewIndex)
	{
		if (NewIndex >= -1 && NewIndex < MAX_SLOT_NUMS)
		{
			CurrentSlotIndex = NewIndex;
		}
	}
};
