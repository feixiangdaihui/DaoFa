// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "General/Interface/SaveLoadData.h"
#include "GoodsManage.generated.h"


class UReputationComponent;
USTRUCT(BlueprintType)
struct FGoodsPriceInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")
	TSubclassOf<APackObject> GoodsClass; // 物品类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")
	float ActualPrice; // 实际价格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")
	float PriceFloatFactor; // 价格浮动系数
public:
	FGoodsPriceInfo()
		: GoodsClass(nullptr), ActualPrice(0.0f), PriceFloatFactor(2.0)
	{
	}
};
USTRUCT(BlueprintType)
struct FGoodsAndPrice
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")
	TObjectPtr<APackObject> Goods; // 物品类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")
	float Price; // 实际价格
public:
	FGoodsAndPrice(TSubclassOf<APackObject> InGoodsClass, float InPrice)
		:  Price(InPrice)
	{
		if (InGoodsClass)
		{
			Goods = InGoodsClass->GetDefaultObject<APackObject>();
		}
		else
		{
			Goods = nullptr;
		}
	}
	FGoodsAndPrice()
		: Goods(nullptr), Price(0.0f)
	{
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UGoodsManage : public UActorComponent, public ISaveLoadData
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoodsManage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")
	int GoodsNum = 1; // 物品数量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goods")

	TArray<FGoodsPriceInfo> MayGoodsAndPriceArray; // 物品和价格浮动系数数组，从中随机生成物品和价格

	TArray<FGoodsAndPrice> GoodsPriceArray; // 物品和价格

	TArray<int32> AlreadySoldGoodsIndex; // 已经出售的物品索引




private:

	void InitializeGoodsRandom();//随机生成物品数组

	void SellGoods(int index); //出售物品


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Goods")
	TArray<FGoodsAndPrice> GetGoodsAndPriceArray()
	{
		return GoodsPriceArray;
	}
	UFUNCTION(BlueprintCallable, Category = "Goods")
	float GetPriceByGoods(APackObject* Goods)
	{
		for (const FGoodsAndPrice& GoodsInfo : GoodsPriceArray)
		{
			if (GoodsInfo.Goods == Goods)
			{
				return GoodsInfo.Price;
			}
		}
		return -1.0; // Return 0 if the goods is not found
	}

	UFUNCTION(BlueprintCallable, Category = "Goods")
	TArray<APackObject*> GetGoodsArrayByType(EEquipmentType EquipmentType)
	{
		TArray<APackObject*> GoodsArray;
		for (const FGoodsAndPrice& GoodsInfo : GoodsPriceArray)
		{
			if (GoodsInfo.Goods && GoodsInfo.Goods->GetBaseInfo().EquipmentType == EquipmentType)
			{
				GoodsArray.Add(GoodsInfo.Goods);
			}
		}
		return GoodsArray;
	}

	UFUNCTION(BlueprintCallable, Category = "Goods")
	float SellGoods(APackObject* Goods);


	virtual FJsonObject SaveDataMethod() const override
	{
		TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
		TArray<TSharedPtr<FJsonValue>> TempSoldGoodsArray;
		for (int32 Index : AlreadySoldGoodsIndex)
		{
			TSharedPtr<FJsonObject> TempSoldGoods = MakeShared<FJsonObject>();
			TempSoldGoods->SetNumberField(TEXT("Index"), Index);
			TempSoldGoodsArray.Add(MakeShared<FJsonValueObject>(TempSoldGoods));
		}
		SaveData->SetArrayField(TEXT("AlreadySoldGoodsIndex"), TempSoldGoodsArray);
		return *SaveData;

	}

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) override
	{
		if (JsonObject.IsValid())
		{
			const TArray<TSharedPtr<FJsonValue>>* TempSoldGoodsArray;
			if (JsonObject->TryGetArrayField(TEXT("AlreadySoldGoodsIndex"), TempSoldGoodsArray))
			{
				for (const TSharedPtr<FJsonValue>& TempSoldGoods : *TempSoldGoodsArray)
				{
					int32 Index = TempSoldGoods->AsObject()->GetNumberField(TEXT("Index"));
					AlreadySoldGoodsIndex.Add(Index);
				}
			}
		}
	}

	virtual FString GetKey() const override
	{
		return TEXT("GoodsManage");
	} //返回保存的键值




	

};
