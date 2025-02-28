#include "General/StateComponent.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

//境界差异导致的伤害倍率
//[i][j]表示大境界为i，小境界为j
//[i][j]的值表示比对上一个境界造成的伤害倍率
float UStateComponent::CreatureStateDamageMultiplier[LARGE_STATE_NUM][SMALL_STATE_NUM] =
{
	{1.0f, 1.1f, 1.1f, 1.1f},
	{2.0f, 1.1f, 1.1f, 1.1f},
	{10.0f, 2.0f, 2.0f, 2.0f},
	{20.0f, 3.0f, 3.0f, 3.0f},
	{50.0f, 5.0f, 5.0f, 5.0f}
};


float UStateComponent::CalCreatureStateDamageMultiplier(FState SelfState, FState OtherState)
{
    //越高境界，隔一个大境界和小境界，伤害倍率都会增加
    ELargeState LargeLarger;
    ELargeState LargeSmaller;
    int SmallLarger;
    int SmallSmaller;
    bool SelfIsLarger = false;
	float DamageMultiplier = 1.0f;
	if (SelfState == OtherState)
	{
		return DamageMultiplier;
	}
	else if (SelfState.LargeState > OtherState.LargeState)
	{
		LargeLarger = SelfState.LargeState;
		LargeSmaller = OtherState.LargeState;
		SmallLarger = static_cast<int>(SelfState.SmallState);
		SmallSmaller = static_cast<int>(OtherState.SmallState);
		SelfIsLarger = true;
	}
	else
	{
		LargeLarger = OtherState.LargeState;
		LargeSmaller = SelfState.LargeState;
		SmallLarger = static_cast<int>(OtherState.SmallState);
		SmallSmaller = static_cast<int>(SelfState.SmallState);
		SelfIsLarger = false;
	}
    for(int Large=static_cast<int>(LargeSmaller); Large <=static_cast<int>(LargeLarger); Large++)
    {
        int SmallBegin = 0;
        int SmallEnd = SMALL_STATE_NUM-1;
		if (Large == static_cast<int>(LargeSmaller))
		{
			SmallBegin = static_cast<int>(SelfState.SmallState)+1;
		}
        if (Large == static_cast<int>(LargeLarger))
        {
			SmallEnd = static_cast<int>(OtherState.SmallState);
        }
		for (int Small = SmallBegin; Small <= SmallEnd; Small++)
		{
			DamageMultiplier *= CreatureStateDamageMultiplier[Large][Small];
		}
    }
	if (!SelfIsLarger)
	{
		DamageMultiplier = 1.0f / DamageMultiplier;
	}
	return DamageMultiplier;
}
//物品和角色的境界差异导致的伤害倍率
//[i]表示大境界为i
//[i]的值表示该境界的角色使用上一个境界物品造成的伤害倍率
float UStateComponent:: ItemCreatureStateDamageMultiplier[LARGE_STATE_NUM] = { 0.9f, 0.8f, 0.7f, 0.6f, 1.0f };


float UStateComponent::CalItemCreatureStateDamageMultiplier(FState SelfState, FState ItemState)
{
	float DamageMultiplier = 1.0f;
	//如果角色境界高于物品境界，那么角色使用该物品造成的伤害倍率为1.0f
	if (SelfState.LargeState != ItemState.LargeState)
	{
		for (int Large = static_cast<int>(ItemState.LargeState); Large < static_cast<int>(SelfState.LargeState); Large++)
		{
			DamageMultiplier *= ItemCreatureStateDamageMultiplier[Large];
		}
	}
	return DamageMultiplier;
}

// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
