// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "General/ElementSetting.h"
#include "AttackAttributeComponent.generated.h"


//委托：对于可衰减的对象，在完全衰减后，调用该委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttenuationComplete, AActor*,AttenuationObject);
UENUM()
enum class EInterruptType
{
	FULL,
	PARTIAL,
	NONE
};

UENUM()
enum class EInterruptDir
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	FRONT,
	BACK,
	ERROR
};

UENUM()
enum class EInterruptAblity
{
	HEAVY,
	LIGHT,
	NONE
};

UENUM()
enum class EAvoidInterruptAblity
{
	ABSOLUTE,
	RELATIVE,
	NONE
};



USTRUCT(BlueprintType)
struct FAttackAttributeInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	GElement Element;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	EInterruptAblity InterruptAblity;
	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float CriticalHitChance = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float CriticalHitMultiplier = 2.0f;
};


class IBeAttacked;
class ACreature;
struct FAttackerInfo;




//本类用于存储攻击属性，包括基础伤害，伤害倍率，暴击率，暴击倍率，元素属性，中断属性，并囊括与之相关的方法，如攻击，攻击属性的比较等
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UAttackAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class UCalAttackLibrary;
public:	
	// Sets default values for this component's properties
	UAttackAttributeComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float BaseDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	GElement Element = GElement::Matel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	EInterruptAblity InterruptAblity = EInterruptAblity::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float DamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool IsAttenuation = false;


public:

	UPROPERTY(BlueprintAssignable, Category = "Attack")
	FOnAttenuationComplete OnAttenuationComplete;



	//Duration in seconds
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetDamageMultiplier(float Multiplier, bool bIsPermanent = false, float Duration = 0.0f);

	////if key is not found, it will add a new key-value pair
	////if key is found, return false
	//UFUNCTION(BlueprintCallable, Category = "Attack")
	//bool SetDamageMultiplierByKey(float Multiplier,FString Key);

	//bool WithDrawDamageMultiplierByKey(FString Key);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void MultiplyDamageMultiplier(float Multiplier, bool bIsPermanent = false, float Duration = 0.0f);

	void Attack(IBeAttacked* BeAttacked);


	UFUNCTION(BlueprintCallable, Category = "Attack")
	FAttackAttributeInfo GetAttackAttributeInfo();



};
