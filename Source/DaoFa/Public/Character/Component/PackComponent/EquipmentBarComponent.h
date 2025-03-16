#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentBarComponent.generated.h"
#define EQUIPMENTBAR_NUM 3
#define EQUIPMENTBAR_SIZE 4

class APackObject;
class USumEquipmentBarWidget;
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

	USumEquipmentBarWidget* SumEquipmentBarWidget;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	virtual void WearEquipment(APackObject* Equipment, int SpecificIndex = -1);

	UFUNCTION(BlueprintCallable, Category = "SumEquipmentBar")
	virtual void TakeOffEquipment(APackObject* Equipment);



	void ChangeChosenEquipmentBarToSmall();

	void ChangeChosenEquipmentBarToBig();

	void InitSumEquipmentBarWidget(USumEquipmentBarWidget* InSumEquipmentBarWidget);

	APackObject* GetEquipment(int Index) { return EquipmentBar[CurrentChosenIndex][Index]; }

};
