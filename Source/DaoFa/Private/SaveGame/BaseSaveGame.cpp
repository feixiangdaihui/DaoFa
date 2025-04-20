// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"



UBaseSaveGame* UBaseSaveGame::GetBaseSaveGame(FString SlotName)
{
	USaveGame* SaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	UBaseSaveGame* BaseSaveGame = Cast<UBaseSaveGame>(SaveGame);
	return BaseSaveGame;
}

void UBaseSaveGame::SaveISaveLoadDataArray(FString SlotName, TArray<TScriptInterface<ISaveLoadData>> ISaveLoadDataArray)
{
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonObject>> TempSaveData;
	TempSaveData.SetNum(ISaveLoadDataArray.Num());
	for (int i = 0; i < ISaveLoadDataArray.Num(); i++)
	{
		if (ISaveLoadDataArray[i].GetObject() != nullptr)
		{
			TempSaveData[i] = MakeShared<FJsonObject>(ISaveLoadDataArray[i]->SaveDataMethod());

			SaveData->SetObjectField(ISaveLoadDataArray[i]->GetKey(), TempSaveData[i]);
		}
	}
	if (SaveData.IsValid())
	{
		if (IsTest)
		{
			//输出jsonobject
			FString TestString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&TestString);
			FJsonSerializer::Serialize(SaveData.ToSharedRef(), Writer);
			UE_LOG(LogTemp, Display, TEXT("JSON内容：\n%s"), *TestString);
		}
		FString OutputString;
		TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(SaveData.ToSharedRef(), Writer);
		SaveDataString = OutputString;
		UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
	}
}

void UBaseSaveGame::LoadISaveLoadDataArray(UBaseSaveGame* LoadBaseSaveGame, TArray<TScriptInterface<ISaveLoadData>> ISaveLoadDataArray)
{
	if (LoadBaseSaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadBaseSaveGame is null"));
		return;
	}
	if (LoadBaseSaveGame->SaveDataString.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveDataString is empty"));
		return;
	}
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	if (LoadBaseSaveGame)
	{
		SaveDataString = LoadBaseSaveGame->SaveDataString;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(LoadBaseSaveGame->SaveDataString);
		FJsonSerializer::Deserialize(Reader, SaveData);
		for (auto ISaveLoadData : ISaveLoadDataArray)
		{
			if (ISaveLoadData.GetObject() != nullptr)
				ISaveLoadData->LoadDataMethod(SaveData->GetObjectField(ISaveLoadData->GetKey()));
		}
	}
}
