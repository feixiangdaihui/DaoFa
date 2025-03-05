// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Component/PackComponent/POAttackAttributeComponent.h"
#include "PackObject.generated.h"
class UBlueCostComponent;
class UAttackAttributeComponent;
class UPOAttackAttributeComponent;
class UStateComponent;


//物品耗尽委托,需要一个参数，表示物品耗尽的物品
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPackObjectExhausted, APackObject*, PackObject);

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	FASHU,
	FABAO,
	FULU
};

//背包中要显示的信息的结构体
USTRUCT(BlueprintType)
struct FPackObjectInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	int Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	int SizeInPack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float AttackMutiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float CriticalHitChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float CriticalHitMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	GElement Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	EInterruptAblity InterruptAblity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float ShortPressDamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float LongPressDamageMultiplier;

};



UCLASS()
class DAOFA_API APackObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APackObject();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	UTexture2D* Icon;

	//物品的名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FText Name;


	//物品的描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	int Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	float LongPressTime = 1.0f;
	float LongPressTimeCounter = 0.0f;

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UBlueCostComponent> BlueCostComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UPOAttackAttributeComponent> POAttackAttributeComponent;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PackObject")
    EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UStateComponent> StateComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	int SizeInPack = 1;

	ACreature* OwnerCreature;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	bool IsLongPressPermit = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	bool IsShortPressPermit = true;

	virtual void TriggeredByShortPress() {}

	virtual void TriggeredByLongPress() {}


	bool CanBeWearOrTakeOff = true;
public:	
	FOnPackObjectExhausted OnPackObjectExhausted;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "IShowTrigger")
	virtual UTexture2D* GetIcon()const  { return Icon; }



	UFUNCTION(BlueprintCallable, Category = "IShowTrigger")
	virtual int GetQunatity() const { return Quantity; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual void AttachToCreature(class ACreature* Creature);

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	bool GetCanBeWearOrTakeOff() { return CanBeWearOrTakeOff; }

	//允许长按且允许短按的模式：
	//1.begin后什么都不做，直到end，判断是否长按，如果是长按，触发长按，否则触发短按
	//不允许长按的模式：
	//1.begin直接触发短按
	//2.end再次触发短按，所以该模式下的物品应该在再次触发短按时处理收尾逻辑
	//不允许短按的模式：
	//1.begin后什么都不做，直到end，判断是否长按，如果是长按，触发长按，否则什么都不做
	bool TriggeredBegin();

	bool TriggeredEnd();




	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual EEquipmentType GetEquipmentType() { return EquipmentType; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	int GetSizeInPack() { return SizeInPack; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	FPackObjectInfo GetPackObjectInfo();

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	UPOAttackAttributeComponent* GetPOAttackAttributeComponent() { return POAttackAttributeComponent; } 

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	UStateComponent* GetStateComponent() { return StateComponent; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	ACreature* GetOwnerCreature() { return OwnerCreature; }
	
	



};




