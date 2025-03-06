// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/PackComponent/FaBao.h"
#include "General/Interface/BeAttacked.h"
#include "JinZhongZhao.generated.h"
class ACreature;
class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class DAOFA_API AJinZhongZhao : public AFaBao, public IBeAttacked
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JinZhongZhao")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JinZhongZhao")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;


	UFUNCTION()
	void OnDeath();

	bool IsSpell = false;

public:


	virtual void TriggeredByShortPress() override;

	AJinZhongZhao();

	virtual void AttachToCreature(ACreature* Creature) override;


	virtual void BeAttacked(APackObject* PackObject, float DamageMultiplier) override;



};
