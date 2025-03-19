#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMainGongFa.generated.h"

class USpellCoolComponent;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UBaseMainGongFa : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseMainGongFa();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GongFa")
	FText GongFaName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GongFa")
	FText GongFaDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GongFa")
	FText PassiveIntroduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GongFa")
	FText Active1Introduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FirstAttack")
	USpellCoolComponent* FSpellCoolComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SecondAttack")
	USpellCoolComponent* SSpellCoolComponent;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void FirstAttack();

	virtual bool CheckFirstAttack();

	virtual bool CheckSecondAttack();

	virtual void SecondAttack();

	UFUNCTION(BlueprintCallable)
	FText GetGongFaName() { return GongFaName; }

	UFUNCTION(BlueprintCallable)
	FText GetGongFaDescription() { return GongFaDescription; }
	

	UFUNCTION(BlueprintCallable)
	FText GetPassiveIntroduction() { return PassiveIntroduction; }

	UFUNCTION(BlueprintCallable)
	FText GetActive1Introduction() { return Active1Introduction; }



};
