// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "SaveGame/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Character/BaseCharacter.h"


void UMyGameInstance::Init()
{
	Super::Init();

	//1s后加载游戏
	FTimerHandle TimerHandle1;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &UMyGameInstance::LoadGame, 1.0f, false);

	//定时保存游戏
	FTimerHandle TimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &UMyGameInstance::AutoSaveGame, 10.0f, true);

}

void UMyGameInstance::LoadGame()
{
	UBaseSaveGame* SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	//获取当前控制的角色
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (IsValid(BaseCharacter))
	{
		SaveGameInstance->InitISaveLoadData({ BaseCharacter });
		SaveGameInstance->LoadGameMethod(TEXT("Test"));
	}
}

void UMyGameInstance::AutoSaveGame()
{
	UBaseSaveGame* SaveGameInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	//获取当前控制的角色
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(IsValid(BaseCharacter))
	{
		SaveGameInstance->InitISaveLoadData({ BaseCharacter });
		SaveGameInstance->SaveGameMethod(TEXT("Test"));
	}
}
