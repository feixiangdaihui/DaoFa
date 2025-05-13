// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Businessman/Businessman.h"
#include "General/Component/InteractComponent.h"
#include "Hud/Widget/ShoppingWidget.h"
#include "Hud/BaseHud.h"
#include "Components/SphereComponent.h"
#include "PlayerController/BasePlayerController.h"
#include"NPC/Businessman/Component/GoodsManage.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/PackComponent/PackComponent.h"
#include "Character/Component/Reputation/ReputationComponent.h"
#include "Character/Component/Reputation/FaceComponent.h"

void ABusinessman::BeginPlay()
{
	Super::BeginPlay();
	InteractComponent->OnInteract.BindUObject(this, &ABusinessman::OnInteract);
}

ABusinessman::ABusinessman()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
	GoodsManage = CreateDefaultSubobject<UGoodsManage>(TEXT("GoodsManage"));
}

void ABusinessman::OnInteract(AActor* InteractActor)
{
	if (InteractActor)
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(InteractActor);
		if (BaseCharacter)
		{

			InteractCharacter = BaseCharacter;
			OpenShoppingWidget();
		}
	}
}

void ABusinessman::OpenShoppingWidget()
{
	if (GoodsManage)
	{
		ABaseHud* BaseHud = Cast<ABaseHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (BaseHud)
		{
			UShoppingWidget* ShoppingWidget = Cast<UShoppingWidget>(BaseHud->GetWidgetByName("ShoppingWidget"));
			if(ShoppingWidget)
			{
				ShoppingWidget->Pop(this);
			}
		}
	}
}

void ABusinessman::SellGoods(APackObject* Goods)
{
	if (InteractCharacter.IsValid())
	{
		if (GoodsManage)
		{
			float Price = GoodsManage->GetPriceByGoods(Goods);
			if (Price > 0.0f)
			{
				InteractCharacter->GetPackComponent()->WearEquipment(Goods);
				InteractCharacter->GetReputationComponent()->GetFaceComponent()->SubtractValue(Price);
			}
		}
	}
}
