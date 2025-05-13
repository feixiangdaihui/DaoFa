
#include "SaveGame/ArchiveSaveGame.h"
#include"Creature.h"
#include "Kismet/GameplayStatics.h"





TArray<FArchiveData> UArchiveSaveGame::GetArchiveDataArray() const
{
	TArray<FArchiveData> ArchiveDataArray;
	for (int i = 0; i < MAX_SLOT_NUMS; i++)
	{
		FString SlotName = GetSlotNameByIndex(i);
		USaveGame* LoadGameInstance = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
		UArchiveSaveGame* LoadArchiveSaveGame = Cast<UArchiveSaveGame>(LoadGameInstance);
		if (LoadArchiveSaveGame)
		{
			ArchiveDataArray.Add(LoadArchiveSaveGame->ArchiveData);
		}
		else
		{
			FArchiveData EmptyData;
			EmptyData.SlotIndex = i;
			EmptyData.IsEmpty = true;
			ArchiveDataArray.Add(EmptyData);
		}
	}
	return ArchiveDataArray;

}

void UArchiveSaveGame::SaveArchiveMethod(UWorld* World,bool IsExit)
{
	if (IsValidCurrentSlotIndex() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot index for saving data"));
		return;
	}


	//保存存档数据
	ArchiveData.SlotIndex = CurrentSlotIndex;
	ArchiveData.IsEmpty = false;

	//保存当前存档
	FString SlotName = GetSlotNameByIndex(CurrentSlotIndex);
	SaveISaveLoadDataArray(SlotName, SaveLoadDataArray);


	if (IsExit)
	{
		CurrentSlotIndex = -1;
		SaveLoadDataArray.Empty();
	}
}

void UArchiveSaveGame::LoadArchiveMethod(UWorld* World, TArray<TScriptInterface<ISaveLoadData>> InSaveLoadDataArray)
{
	if (IsValidCurrentSlotIndex() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot index for loading save data"));
		return;
	}
	SaveLoadDataArray = InSaveLoadDataArray;
	FString SlotName = GetSlotNameByIndex(CurrentSlotIndex);
	UBaseSaveGame* BaseSaveGame = GetBaseSaveGame(SlotName);
	if (BaseSaveGame == nullptr)
	{
		return;
	}
	UArchiveSaveGame* LoadArchiveSaveGame = Cast<UArchiveSaveGame>(BaseSaveGame);

	if (LoadArchiveSaveGame)
	{
		LoadISaveLoadDataArray(LoadArchiveSaveGame, SaveLoadDataArray);
		ArchiveData = LoadArchiveSaveGame->ArchiveData;
	}
}







