// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UArchiveSaveGame;

/**
 * 
 */
UCLASS()
class DAOFA_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArchiveSaveGame>  ArchiveSaveGame;

	void SaveSlot();

	void OnApplicationExit();

	void OnPrePIEEnded(const bool bIsSimulating);


protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "GamePlay")
	void OpenSlot(int SlotIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "GamePlay")
	void CloseSlot();

public:
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	UArchiveSaveGame* GetArchiveSaveGame() const { return ArchiveSaveGame; }

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void EnterSlot(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void ExitGameFromSlot();

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void ExitGameFromWhole();



};
