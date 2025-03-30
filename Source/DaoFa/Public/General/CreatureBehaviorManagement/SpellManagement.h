#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellManagement.generated.h"

class ISetValueInterface;
class IGetValueInterface;
class APackObject;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API USpellManagement : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpellManagement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	TScriptInterface<ISetValueInterface> SetBlueValue;
	TScriptInterface<IGetValueInterface> GetBlueValue;

	TMap<APackObject*, float> SpellBeginTimeMap;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	bool CheckForSpell(APackObject* Equipment);

	void SpellBegin(APackObject* Equipment);

	void SpellLoop(APackObject* Equipment, float DeltaTime);

	void SpellEnd(APackObject* Equipment);


	void Init(TScriptInterface<ISetValueInterface> InSetBlueValue, TScriptInterface<IGetValueInterface> InGetBlueValue)
	{
		SetBlueValue = InSetBlueValue;
		GetBlueValue = InGetBlueValue;
	}


};
