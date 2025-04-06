// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PackComponent/FuLu.h"

// Sets default values
AFuLu::AFuLu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseInfo.EquipmentType = EEquipmentType::FULU;
}

// Called when the game starts or when spawned
void AFuLu::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuLu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFuLu::Pile(TScriptInterface<IPileAbility> PileTarget)
{
	//如果是同一个物品，直接返回
	if (this == PileTarget.GetObject())
	{
		return;
	}
	//如果是同类物品，叠加
	if (this->GetClass() == PileTarget.GetObject()->GetClass())
	{
		Numbers += PileTarget->GetNumbers();
		//销毁
		AFuLu* Target = Cast<AFuLu>(PileTarget.GetObject());
		if (Target)
		{
			Target->Destroy();
		}

	}
	else
	{
		//如果不是同类物品，直接返回
		return;
	}
}

