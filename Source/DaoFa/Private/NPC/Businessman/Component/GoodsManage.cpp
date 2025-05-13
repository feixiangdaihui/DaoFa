// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Businessman/Component/GoodsManage.h"
#include"GameMode/BaseGameMode.h"

// Sets default values for this component's properties
UGoodsManage::UGoodsManage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGoodsManage::BeginPlay()
{
	Super::BeginPlay();
	InitializeGoodsRandom();

}


void UGoodsManage::InitializeGoodsRandom()
{
	ABaseGameMode* BaseGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (BaseGameMode)
	{
		// Initialize the random stream with the seed from the game mode
		FRandomStream RandomStream = BaseGameMode->GetRandomStream();
		TSet<int> AlreadySelectedGoodsIndex;
		for (int i = 0; i < GoodsNum; ++i)
		{
			int32 RandomIndex = RandomStream.RandRange(0, MayGoodsAndPriceArray.Num() - 1);
			if (AlreadySelectedGoodsIndex.Contains(RandomIndex))
			{
				--i; // Retry if the class is already selected
				continue;
			}
			AlreadySelectedGoodsIndex.Add(RandomIndex);
			const FGoodsPriceInfo& GoodsInfo = MayGoodsAndPriceArray[RandomIndex];
			int32 RandomPriceFactor = RandomStream.RandRange(1.0f, FMath::Max(GoodsInfo.PriceFloatFactor,1.0f));
			GoodsPriceArray.Add(FGoodsAndPrice(GoodsInfo.GoodsClass, GoodsInfo.ActualPrice));
		}
	}

}


void UGoodsManage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UGoodsManage::SellGoods(APackObject* Goods)
{
	for (int i = 0; i < GoodsPriceArray.Num(); ++i)
	{
		if (GoodsPriceArray[i].Goods == Goods)
		{
			float Price = GoodsPriceArray[i].Price;
			GoodsPriceArray.RemoveAt(i);
			return Price;
		}
	}
	return -1.0f; // Return -1 if the goods is not found
}




