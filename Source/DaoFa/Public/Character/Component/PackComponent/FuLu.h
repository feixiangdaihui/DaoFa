// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "General/Interface/PileAbility.h"
#include "FuLu.generated.h"

UCLASS()
class DAOFA_API AFuLu : public APackObject, public IPileAbility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuLu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int Numbers = 1;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual int GetNumbers() override { return Numbers; }

	virtual void Pile(TScriptInterface<IPileAbility> PileTarget) override;

};
