#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentBarComponent.generated.h"
#define EQUIPMENTBAR_NUM 3
#define EQUIPMENTBAR_SIZE 4

//委托，无参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentBarChange);

class APackObject;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UEquipmentBarComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentBarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Fashu, Fubao, Fulu
	APackObject* EquipmentBar[EQUIPMENTBAR_NUM][EQUIPMENTBAR_SIZE];

	int CurrentChosenIndex = 0;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	virtual void WearEquipment(APackObject* Equipment, int SpecificIndex = -1);

	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	virtual void TakeOffEquipment(APackObject* Equipment);

	UPROPERTY(BlueprintAssignable, Category = "SumEquipmentBar")
	FOnEquipmentBarChange OnEquipmentBarChange;


	void ChangeChosenEquipmentBarToSmall();

	void ChangeChosenEquipmentBarToBig();


	APackObject* GetEquipment(int Index) { return EquipmentBar[CurrentChosenIndex][Index]; }

	int GetCurrentChosenIndex() { return CurrentChosenIndex; }

	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	TArray<APackObject*> GetEquipmentBar(int TypeIndex)
	{ 
		if (TypeIndex < 0 || TypeIndex >= EQUIPMENTBAR_NUM)
		{
			return TArray<APackObject*>();
		}
		return TArray<APackObject*>(EquipmentBar[TypeIndex], EQUIPMENTBAR_SIZE); 
	}

};
