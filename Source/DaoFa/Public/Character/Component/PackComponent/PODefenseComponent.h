#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PODefenseComponent.generated.h"
class UDefenseComponent;
class UHealthComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UPODefenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPODefenseComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PODefense")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PODefense")
	TObjectPtr<UDefenseComponent> DefenseComponent;


public:
	UFUNCTION(BlueprintCallable, Category = "PODefense")
	UHealthComponent* GetHealthComponent() { return HealthComponent; }

	UFUNCTION(BlueprintCallable, Category = "PODefense")
	UDefenseComponent* GetDefenseComponent() { return DefenseComponent; }





};
