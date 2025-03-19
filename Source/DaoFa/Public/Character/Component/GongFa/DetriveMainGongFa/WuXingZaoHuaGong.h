// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/GongFa/BaseMainGongFa.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "WuXingZaoHuaGong.generated.h"

class UPackComponent;

/**
 * 
 */
UCLASS()
class DAOFA_API UWuXingZaoHuaGong : public UBaseMainGongFa
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FirstAttack")
	float SpellCoolSubPercent = 0.5f;

private:

	void BaseFirstAttack(EEquipmentType EquipmentType, UPackComponent* PackComponent);


public:
	UWuXingZaoHuaGong();

	virtual void FirstAttack() override;

	virtual void SecondAttack() override;

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
