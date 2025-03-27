// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "General/CalAttackLibrary.h"
#include "Attacker.generated.h"


//判断两个物体对于攻击的优先级
//可以用于武器碰撞时的优先级判断
UENUM()
enum class EAttackCompareType
{
	LESS,
	EQUAL,
	GREATER
};

//攻击者是否会阻挡其他攻击者的攻击

UENUM()
enum class EAttackerType
{
	NOBLOCK,
	BLOCK
};

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class  UAttacker : public UInterface
{
	GENERATED_BODY()
};

class IAttacker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	virtual FAttackerInfo GetAttackerInfo() = 0;
	virtual EAttackerType GetAttackerType() = 0;
};

UCLASS()
class DAOFA_API UCompareAttackLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	//计算相对优先级
	static float CalculateAttackPriority(FAttackerInfo Attacker1, FAttackerInfo Attacker2);
	static EAttackCompareType CompareAttack(FAttackerInfo Attacker1, FAttackerInfo Attacker2);
public:
	static EAttackCompareType CompareAttack(IAttacker* Attacker1, IAttacker* Attacker2);
};
