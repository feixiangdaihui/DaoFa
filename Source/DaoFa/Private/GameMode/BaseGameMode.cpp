// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BaseGameMode.h"
#include "SaveGame/ArchiveSaveGame.h"
#include "MyGameInstance.h"
#include"Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include"GameMode/Component/SeedsComponent.h"


ABaseGameMode::ABaseGameMode(const FObjectInitializer& ObjectInitializer)
{
	SeedsComponent = CreateDefaultSubobject<USeedsComponent>(TEXT("SeedsComponent"));
}
void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	//获取游戏实例

	//遍历世界里的所有继承于ACreature角色,加入到SaveLoadDataArray中
	TArray<AActor*> BaseCharacterArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreature::StaticClass(), BaseCharacterArray);
	for (AActor* Actor : BaseCharacterArray)
	{
		ACreature* BaseCharacter = Cast<ACreature>(Actor);
		SaveLoadDataArray.Add(BaseCharacter);
	}
	
	SaveLoadDataArray.Add(SeedsComponent);


	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UArchiveSaveGame* ArchiveSaveGame = GameInstance->GetArchiveSaveGame();
		if (ArchiveSaveGame)
		{		
			//加载存档数据
			ArchiveSaveGame->LoadArchiveMethod(GetWorld(), { this });
		}
	}

	//获取控制器
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//不显示鼠标
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
	}
	PlayerController->SetInputMode(FInputModeGameOnly());



}

FJsonObject ABaseGameMode::SaveDataMethod() const
{
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonObject>> TempArray;
	TempArray.SetNum(SaveLoadDataArray.Num());
	for (int i = 0; i < SaveLoadDataArray.Num(); i++)
	{
		if (SaveLoadDataArray[i].GetObject() != nullptr)
		{
			TempArray[i] = MakeShared<FJsonObject>(SaveLoadDataArray[i]->SaveDataMethod());
			SaveData->SetObjectField(SaveLoadDataArray[i]->GetKey(), TempArray[i]);
		}
	}
	return *SaveData;
}

void ABaseGameMode::LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject)
{
	for (auto ISaveLoadData : SaveLoadDataArray)
	{
		if (ISaveLoadData.GetObject() != nullptr)
			ISaveLoadData->LoadDataMethod(JsonObject->GetObjectField(ISaveLoadData->GetKey()));
	}
}

FRandomStream ABaseGameMode::GetRandomStream() const
{
	return SeedsComponent->GetRandomStream();
}


