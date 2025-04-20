// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "SaveGame/ArchiveSaveGame.h"
#include "Kismet/GameplayStatics.h"


void UMyGameInstance::SaveSlot()
{
	if (ArchiveSaveGame)
	{
		//保存存档数据
		ArchiveSaveGame->SaveArchiveMethod(GetWorld(), true);
	}
}

void UMyGameInstance::OnApplicationExit()
{
	SaveSlot();
}

void UMyGameInstance::OnPrePIEEnded(const bool bIsSimulating)
{
	SaveSlot();
}



void UMyGameInstance::Init()
{
	Super::Init();

	ArchiveSaveGame = Cast<UArchiveSaveGame>(UGameplayStatics::CreateSaveGameObject(UArchiveSaveGame::StaticClass()));
	FCoreDelegates::ApplicationWillDeactivateDelegate.AddUObject(this, &UMyGameInstance::OnApplicationExit);
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UMyGameInstance::OnPrePIEEnded);

}

void UMyGameInstance::EnterSlot(int SlotIndex)
{
	if (ArchiveSaveGame)
	{
		ArchiveSaveGame->ChangeCurrentSlotIndex(SlotIndex);
		OpenSlot(SlotIndex);
	}
}

void UMyGameInstance::ExitGameFromSlot()
{
	SaveSlot();
	CloseSlot();
}

void UMyGameInstance::ExitGameFromWhole()
{
	//退出游戏
	SaveSlot();
	FGenericPlatformMisc::RequestExit(false);

}

