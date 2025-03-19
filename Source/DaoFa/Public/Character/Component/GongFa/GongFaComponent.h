#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GongFaComponent.generated.h"


class UBaseMainGongFa;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UGongFaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGongFaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	TObjectPtr<UBaseMainGongFa> MainGongFa;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "GongFa")
	void SetMainGongFa(TSubclassOf<UBaseMainGongFa> MainGongFaClass);

	UFUNCTION(BlueprintCallable, Category = "GongFa")
	UBaseMainGongFa* GetMainGongFa() { return MainGongFa; }



};
