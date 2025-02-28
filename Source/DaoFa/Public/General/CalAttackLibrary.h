// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "CalAttackLibrary.generated.h"
USTRUCT(BlueprintType)
struct FAttackReturnValue
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float Damage;

	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	EInterruptType InterruptType;

	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	EInterruptDir InterruptDir;
};

class APackObject;
/**
 * 
 */
UCLASS()
class DAOFA_API UCalAttackLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable, Category = "Attack")
	static EInterruptType CalculateInterrupt(EInterruptAblity InterruptAblity,float ActualDamagePercent, EAvoidInterruptAblity AvoidAblity, float StartToBeInterruptedPercent);

	//计算公式：攻击力*角色与法宝不匹配度带来的伤害倍率*境界差异带来的伤害倍率/对方的防御力*元素克制倍率
	UFUNCTION(BlueprintCallable, Category = "Attack")
	static  float CalculateDamage(APackObject* SelfPackObejct, ACreature* OtherCreature, float DamageMultiplier);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	static EInterruptDir CalculateInterruptDir(AActor* SelfActor,AActor* OtherActor);

	static bool IsTest;

public:
	//DamageMultiplier是类似重击所带的倍率，也可以是虚弱状态所带的倍率，物品和角色原本自带的倍率已经算在内
	UFUNCTION(BlueprintCallable, Category = "Attack")
	static  FAttackReturnValue CalculateAttack( APackObject* SelfPackObejct, ACreature* OtherCreature, float DamageMultiplier);
	
};
