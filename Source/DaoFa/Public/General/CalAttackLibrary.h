// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "General/ElementSetting.h"
#include"General/StateComponent.h"
#include "CalAttackLibrary.generated.h"


class APackObject;
class UDefenseComponent;
class UHealthComponent;
class UPODefenseComponent;
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

USTRUCT(BlueprintType)
struct FAttackerInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	FState State;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	FState OwnerState;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float BlueDensity;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float DamageMultiplier;	//DamageMultiplier是类似重击所带的倍率，也可以是虚弱状态所带的倍率，物品和角色原本自带的倍率已经算在内
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	GElement Element;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	EInterruptAblity InterruptAblity;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	AActor* Attacker;
};

USTRUCT(BlueprintType)
struct FDefenderInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Defend")
	FState State;
	UPROPERTY(BlueprintReadWrite, Category = "Defend")
	float Defense;
	UPROPERTY(BlueprintReadWrite, Category = "Defend")
	GElement Element;
	UPROPERTY(BlueprintReadWrite, Category = "Defend")	
	EAvoidInterruptAblity AvoidAblity;
	UPROPERTY(BlueprintReadWrite, Category = "Defend")
	AActor* Defender;
};



/**
 * 
 */
UCLASS()
class DAOFA_API UCalAttackLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable, Category = "Attack")
	static EInterruptType CalculateInterrupt(EInterruptAblity InterruptAblity, EAvoidInterruptAblity AvoidAblity);




	UFUNCTION(BlueprintCallable, Category = "Attack")
	static EInterruptDir CalculateInterruptDir(AActor* SelfActor,AActor* OtherActor);

	static bool IsTest;

public:
	//计算公式：攻击力*角色与法宝不匹配度带来的伤害倍率*境界差异带来的伤害倍率/对方的防御力*元素克制倍率*灵力密度
	static  float CalculateDamage(FAttackerInfo AttackerInfo, FDefenderInfo DefenderInfo);
	
	static float CalculateAttackNum(FAttackerInfo AttackerInfo);

	static float CalculateDefenseNum(FDefenderInfo DefenderInfo);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	static  FAttackReturnValue CalculateAttack(FAttackerInfo AttackerInfo, FDefenderInfo DefenderInfo);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	static FAttackerInfo CreateAttackerInfo(UAttackAttributeComponent* AttackAttributeComponent);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	static FDefenderInfo CreateDefenderInfo(UDefenseComponent* DefenseComponent);

};
