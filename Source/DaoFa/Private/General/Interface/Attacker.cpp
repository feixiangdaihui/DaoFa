#include "General/Interface/Attacker.h"
#include "General/ElementSetting.h"
#include "General/StateComponent.h"
// Add default functionality here for any IMyInterface functions that are not pure virtual.





float UCompareAttackLibrary::CalculateAttackPriority(FAttackerInfo Attacker1, FAttackerInfo Attacker2)
{
	float Base1 = UCalAttackLibrary::CalculateAttackNum(Attacker1);
	float Base2 = UCalAttackLibrary::CalculateAttackNum(Attacker2);
	float Result = Base1 / Base2 * UElementSetting::GetElementRestrainMultiplier(Attacker1.Element, Attacker2.Element) * UStateComponent::CalCreatureStateDamageMultiplier(Attacker1.State, Attacker2.State);
	return Result;
}

EAttackCompareType UCompareAttackLibrary::CompareAttack(FAttackerInfo Attacker1, FAttackerInfo Attacker2)
{
	float Priority = CalculateAttackPriority(Attacker1, Attacker2);
	if (Priority > 1)
	{
		return EAttackCompareType::GREATER;
	}
	else if (Priority < 1)
	{
		return EAttackCompareType::LESS;
	}
	else
	{
		return EAttackCompareType::EQUAL;
	}

}

EAttackCompareType UCompareAttackLibrary::CompareAttack(IAttacker* Attacker1, IAttacker* Attacker2)
{
    
	if (Attacker1->GetAttackerType() == EAttackerType::BLOCK && Attacker2->GetAttackerType() == EAttackerType::BLOCK)
	{
		return CompareAttack(Attacker1->GetAttackerInfo(), Attacker2->GetAttackerInfo());
	}
	else if (Attacker1->GetAttackerType() == EAttackerType::BLOCK)
	{
		return EAttackCompareType::GREATER;
	}
	else if (Attacker2->GetAttackerType() == EAttackerType::BLOCK)
	{
		return EAttackCompareType::LESS;
	}
	else
	{
		return EAttackCompareType::EQUAL;
	}
}
