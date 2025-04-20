// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BaseGameMode.h"
#include "SaveGame/ArchiveSaveGame.h"
#include "MyGameInstance.h"
#include"Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	//获取游戏实例
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		UArchiveSaveGame* ArchiveSaveGame = GameInstance->GetArchiveSaveGame();
		if (ArchiveSaveGame)
		{		
			//加载存档数据
			ArchiveSaveGame->LoadArchiveMethod(GetWorld());
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

void ABaseGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
