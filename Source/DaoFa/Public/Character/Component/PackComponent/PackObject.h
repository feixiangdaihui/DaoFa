// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "General/AttackAttributeComponent.h"
#include "General/DefenseComponent.h"
#include "PackObject.generated.h"

class UAttackAttributeComponent;
class UPOAttackAttributeComponent;
class UStateComponent;
class USpellCoolComponent;
class UPODefenseComponent;

//物品耗尽委托，需要一个参数，表示耗尽的物品
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPackObjectExhausted, APackObject*, PackObject);



UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	FASHU,
	FABAO,
	FULU
};

UENUM(BlueprintType)
enum class EEquipmentModeType : uint8
{
	Attack,
	Defense,
	Blend
};

UENUM(BlueprintType)
enum class EEquipmentSpellType : uint8
{
	Continuous,
	ShortAndLongPress,
	OnlyLongPress,
	OnlyShortPress
};

USTRUCT(BlueprintType)
struct FPackObjectSpellInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float ShortPressBlueCost = 0.0f;

	//属于在短按基础上的额外消耗
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float LongPressBlueCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueCost")
	float OngoingBlueCostBySecond = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float LongPressTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	EEquipmentSpellType EquipmentSpellType = EEquipmentSpellType::ShortAndLongPress;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PackObjectInfo")
	TObjectPtr<USpellCoolComponent> SpellCoolComponent;

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
	EEquipmentModeType EquipmentModeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FAttackAttributeInfo AttackAttributeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FDefenseAttributeInfo DefenseAttributeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PackObjectInfo")
	float CurrentHealth = 100.0f;


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
	FText ObjectName;

	//物品的描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	int Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	EEquipmentModeType EquipmentModeType;


	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UAttackAttributeComponent> AttackAttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UPODefenseComponent> PODefenseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<USpellCoolComponent> SpellCoolComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PackObject")
    EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UStateComponent> StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	int SizeInPack = 1;

	ACreature* OwnerCreature;

	bool CanBeWearOrTakeOff = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FPackObjectSpellInfo SpellInfo;


public:	

	EEquipmentModeType GetEquipmentModeType() { return EquipmentModeType; }

	UPROPERTY(BlueprintAssignable, Category = "PackObject")
	FOnPackObjectExhausted OnPackObjectExhausted;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "IShowTrigger")
	virtual UTexture2D* GetIcon()const  { return Icon; }


	UFUNCTION(BlueprintCallable, Category = "IShowTrigger")
	virtual int GetQunatity() const { return Quantity; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual void AttachToCreature(class ACreature* Creature);

	void AttachToCreatureByActor(AActor* Actor);


	UFUNCTION(BlueprintCallable, Category = "PackObject")
	bool GetCanBeWearOrTakeOff() { return CanBeWearOrTakeOff; }


	virtual void TriggeredByShortPress() {}

	virtual void TriggeredByLongPress() {}


	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual EEquipmentType GetEquipmentType() { return EquipmentType; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	int GetSizeInPack() { return SizeInPack; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	FPackObjectInfo GetPackObjectInfo() const;

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	FText GetObjectName() const { return ObjectName; }

	UAttackAttributeComponent* GetAttackAttributeComponent() { return AttackAttributeComponent; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	UStateComponent* GetStateComponent() { return StateComponent; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	ACreature* GetOwnerCreature() { return OwnerCreature; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	USpellCoolComponent* GetSpellCoolComponent() { return SpellCoolComponent; }
	
	UFUNCTION(BlueprintCallable, Category = "PackObject")
	FPackObjectSpellInfo GetSpellInfo() { return SpellInfo; }
	
	UFUNCTION(BlueprintCallable, Category = "PackObject")
	void SetCanBeWearOrTakeOff(bool value) { CanBeWearOrTakeOff = value; }


};




