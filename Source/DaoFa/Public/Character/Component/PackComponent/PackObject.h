// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Animation/GetAnimation.h"
#include "General/ElementSetting.h"
#include "PackObject.generated.h"

class UAttackAttributeComponent;
class UPOAttackAttributeComponent;
class UStateComponent;
class USpellCoolComponent;
class UDurabilityComponent;

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

};
USTRUCT(BlueprintType)
struct FPackObjectBaseInfo
{

	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FText ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	GElement Element;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObjectInfo")
	FText PowerDescription;
};




UCLASS()
class DAOFA_API APackObject : public AActor , public IGetAnimation
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APackObject();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FPackObjectBaseInfo BaseInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	TObjectPtr<UStateComponent> StateComponent;
	ACreature* OwnerCreature;

	bool CanBeWearOrTakeOff = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FPackObjectSpellInfo SpellInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PackObject")
	FMontageInfo MontageInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PackObjectInfo")
	TObjectPtr<USpellCoolComponent> SpellCoolComponent;




public:	

	USpellCoolComponent* GetSpellCoolComponent() { return SpellCoolComponent; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual FMontageInfo GetMontageInfo() { return MontageInfo; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	FPackObjectBaseInfo GetBaseInfo() { return BaseInfo; }

	UPROPERTY(BlueprintAssignable, Category = "PackObject")
	FOnPackObjectExhausted OnPackObjectExhausted;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual void AttachToCreature(class ACreature* Creature);

	void AttachToCreatureByActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	bool GetCanBeWearOrTakeOff() { return CanBeWearOrTakeOff; }


	virtual void TriggeredByShortPress() {}

	virtual void TriggeredByLongPress() {}


	UFUNCTION(BlueprintCallable, Category = "PackObject")
	virtual EEquipmentType GetEquipmentType() { return BaseInfo.EquipmentType; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	UStateComponent* GetStateComponent() { return StateComponent; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	ACreature* GetOwnerCreature() { return OwnerCreature; }
	
	UFUNCTION(BlueprintCallable, Category = "PackObject")
	FPackObjectSpellInfo GetSpellInfo() { return SpellInfo; }

	UFUNCTION(BlueprintCallable, Category = "PackObject")
	void SetCanBeWearOrTakeOff(bool value) { CanBeWearOrTakeOff = value; }


};




