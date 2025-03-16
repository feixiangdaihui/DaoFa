// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PackComponent.generated.h"

class AFuLu;
class AFaBao;
class AFaShu;
class UPackWidget;
class ABasePlayerController;
class UEquipmentBarComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UPackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	int SumSize = 100;

	int CurrentSize = 0;

	UPROPERTY()
	ABasePlayerController* OwnerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TArray<TObjectPtr<APackObject>> FuLuArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TArray<TObjectPtr<APackObject>> FaBaoArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pack")
	TArray<TObjectPtr<APackObject>> FaShuArray;


	UEquipmentBarComponent* EquipmentBarComponent;


	UFUNCTION()
	void OnPackObjectExhausted(APackObject* PackObject);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Pack")
	virtual void WearEquipment( APackObject* Equipment, int SpecificIndex = -1) ;

	UFUNCTION(BlueprintCallable, Category = "Pack")
	virtual void TakeOffEquipment(APackObject* Equipment);








	UFUNCTION(BlueprintCallable, Category = "Pack")
	TArray<APackObject*> GetArrayByType(EEquipmentType TypeIndex);



	
};
