// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"



void UBaseSaveGame::SaveGameMethod(FString SlotName)
{
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonObject>> TempSaveData;
	TempSaveData.SetNum(ISaveLoadDataArray.Num());
	for (int i = 0; i < ISaveLoadDataArray.Num(); i++)
	{
		if (ISaveLoadDataArray[i].GetObject() != nullptr)
		{
			if(IsTest)
			{
				TempSaveData[i] = MakeShared<FJsonObject>(ISaveLoadDataArray[i]->SaveDataMethod());
				//输出jsonobject
				FString TestString;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&TestString);
				FJsonSerializer::Serialize(TempSaveData[i].ToSharedRef(), Writer);
				// 输出日志  
				UE_LOG(LogTemp, Display, TEXT("JSON内容：\n%s"), *TestString);
			}
			SaveData->SetObjectField(ISaveLoadDataArray[i]->GetKey(), TempSaveData[i]);
		}
	}
	if (SaveData.IsValid())
	{
		FString OutputString;
		TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(SaveData.ToSharedRef(), Writer);
		SaveDataString = OutputString;
		UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
	}
	
}

void UBaseSaveGame::LoadGameMethod(FString SlotName)
{
	TSharedPtr<FJsonObject> SaveData;
	USaveGame* LoadGameInstance = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	UBaseSaveGame* LoadBaseSaveGame = Cast<UBaseSaveGame>(LoadGameInstance);
	if (LoadBaseSaveGame)
	{
		SaveDataString = LoadBaseSaveGame->SaveDataString;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(SaveDataString);
		FJsonSerializer::Deserialize(Reader, SaveData);
		for (auto ISaveLoadData : ISaveLoadDataArray)
		{
			if (ISaveLoadData.GetObject() != nullptr)
				ISaveLoadData->LoadDataMethod(SaveData->GetObjectField(ISaveLoadData->GetKey()));
		}
	}
}
