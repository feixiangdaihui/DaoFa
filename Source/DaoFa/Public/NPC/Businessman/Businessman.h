// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "Businessman.generated.h"


class UInteractComponent;
class UGoodsManage;
class UReputationComponent;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class DAOFA_API ABusinessman : public ACreature
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	ABusinessman();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Businessman")
	TObjectPtr<UInteractComponent> InteractComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Businessman")
	TObjectPtr<UGoodsManage> GoodsManage;

	void OnInteract(AActor* InteractActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Businessman")
	TWeakObjectPtr<ABaseCharacter> InteractCharacter;

	void OpenShoppingWidget();

public:
	virtual FString GetKey() const override
	{
		return TEXT("Businessman");
	}

	UFUNCTION(BlueprintCallable, Category = "Businessman")
	void SellGoods(APackObject* Goods);




};
