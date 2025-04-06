// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "FaBao.generated.h"

UCLASS()
class DAOFA_API AFaBao : public APackObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFaBao();



protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FaBao")
	TObjectPtr<UDurabilityComponent> DurabilityComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TriggeredByLongPress() override;

	virtual void TriggeredByShortPress() override;

    UFUNCTION(BlueprintCallable, Category = "PackObject")
    void OnDurabilityExhausted(UDurabilityComponent* InDurabilityComponent)
    {
		OnPackObjectExhausted.Broadcast(this);
		Destroy();
    }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AttachToCreature(ACreature* Creature) override;
	

};
