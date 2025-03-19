// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/GongFa/DetriveMainGongFa/WuXingZaoHuaGong.h"
#include"Character/Component/PackComponent/SpellCoolComponent.h"
#include "Character/Component/PackComponent/PackComponent.h"
#include"Creature.h"



UWuXingZaoHuaGong::UWuXingZaoHuaGong()
{
	//利用宏来保证ue的本地化控制板可以识别
	GongFaName = NSLOCTEXT("WuXingZaoHuaGong", "GongFaName", "五行造化功");
	GongFaDescription = NSLOCTEXT("WuXingZaoHuaGong", "GongFaDescription", "五行轮转，阴阳交泰；炼虚合道，造化天成。");
	PassiveIntroduction = NSLOCTEXT("WuXingZaoHuaGong", " PassiveIntroduction", "被动：按照元素相生顺序使用法宝、法术、符箓有一定概率进入元素拟态");
	Active1Introduction = NSLOCTEXT("WuXingZaoHuaGong", "Active1Introduction", "1、施法以减少所有五行法术的冷却。2、按五行相生顺序使用法术后解锁，跃向空中进行元素轰炸。");

	FSpellCoolComponent->SetCoolTime(5.0f);
	SSpellCoolComponent->SetCoolTime(10.0f);


}

void UWuXingZaoHuaGong::BaseFirstAttack(EEquipmentType EquipmentType, UPackComponent* PackComponent)
{
	TArray<APackObject*> PackArray = PackComponent->GetArrayByType(EquipmentType);
	for (auto PackObject : PackArray)
	{
		if (PackObject)
		{
			PackObject->GetSpellCoolComponent()->SubtractPercentage(SpellCoolSubPercent);
		}
	}
}

void UWuXingZaoHuaGong::FirstAttack()
{
	Super::FirstAttack();
	ACreature* OwnerCreature = Cast<ACreature>(GetOwner());
	if (OwnerCreature)
	{
		UPackComponent* PackComponent = OwnerCreature->GetPackComponent();
		if (PackComponent)
		{
			BaseFirstAttack(EEquipmentType::FASHU, PackComponent);
			BaseFirstAttack(EEquipmentType::FABAO, PackComponent);
			BaseFirstAttack(EEquipmentType::FULU, PackComponent);
		}
	}




}

void UWuXingZaoHuaGong::SecondAttack()
{
	Super::SecondAttack();
}
