// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "General/Interface/SaveLoadData.h"

#include "BaseGameMode.generated.h"

class USeedsComponent;
/**
 * 
 */
UCLASS()
class DAOFA_API ABaseGameMode : public AGameMode, public ISaveLoadData
{
	GENERATED_BODY()

private:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TArray<TScriptInterface<ISaveLoadData>> SaveLoadDataArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TObjectPtr<USeedsComponent> SeedsComponent;

public:

	ABaseGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual FJsonObject SaveDataMethod() const;

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) ;

	virtual FString GetKey()const {
		return TEXT("BaseGameMode");
	}

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	FRandomStream GetRandomStream() const;
	
};
