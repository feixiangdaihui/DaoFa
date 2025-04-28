#include "General/StateComponent.h"

#include "Character/Component/AttributeComponent/BlueComponent.h"



TMap<ELargeState, FText> UStateComponent::LargeStateTextMap =
{
	//多语言的宏
	{ ELargeState::LIANQI, NSLOCTEXT("LargeState", "LIANQI","炼气") },
	{ ELargeState::ZHUJI, NSLOCTEXT("LargeState", "ZHUJI", "筑基") },
	{ ELargeState::JINDAN, NSLOCTEXT("LargeState", "JINDAN", "金丹") },
	{ ELargeState::YUANYING, NSLOCTEXT("LargeState", "YUANYING", "元婴") },
	{ ELargeState::HUASHEN, NSLOCTEXT("LargeState", "HUASHEN", "化神") }
};
TMap<ESmallState, FText> UStateComponent::SmallStateTextMap =
{
	{ ESmallState::Early, NSLOCTEXT("SmallState", "Early", "初期") },
	{ ESmallState::Middle, NSLOCTEXT("SmallState", "Middle", "中期") },
	{ ESmallState::Late, NSLOCTEXT("SmallState", "Late", "后期") },
	{ ESmallState::Complete, NSLOCTEXT("SmallState", "Complete", "圆满") }
};




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

//境界经验表
//[i][j]表示大境界为i，小境界为j
//[i][j]的值表示突破到下一个境界所需的经验，即这个境界的经验值
float UStateComponent::StateExpTable[LARGE_STATE_NUM][SMALL_STATE_NUM] =
{
	{100.0f, 200.0f, 300.0f, 400.0f},
	{500.0f, 600.0f, 700.0f, 800.0f},
	{900.0f, 1000.0f, 1100.0f, 1200.0f},
	{1300.0f, 1400.0f, 1500.0f, 1600.0f},
	{1700.0f, 1800.0f, 1900.0f, 2000.0f}
};


//每个境界的经验值作用在增加灵力密度上的比例
float UStateComponent::ExpToDensityRate = 0.1f;

//境界升级成功率
//[i][j]表示大境界为i，小境界为j
//[i][j]的值表示突破到下一个境界的成功率
float UStateComponent::UpgradeSuccessRate[LARGE_STATE_NUM][SMALL_STATE_NUM] =
{
	{0.9f, 0.8f, 0.7f, 0.6f},
	{0.8f, 0.7f, 0.6f, 0.5f},
	{0.7f, 0.6f, 0.5f, 0.4f},
	{0.6f, 0.5f, 0.4f, 0.3f},
	{0.5f, 0.4f, 0.3f, 0.2f}
};


FState UStateComponent::GetNextState()
{
	if (CurrentState.SmallState != ESmallState::Complete)
	{
		return { CurrentState.LargeState, static_cast<ESmallState>(static_cast<int>(CurrentState.SmallState) + 1) };
	}
	else
	{
		return { static_cast<ELargeState>(static_cast<int>(CurrentState.LargeState) + 1), ESmallState::Early };
	}
}

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

void UStateComponent::SetCurrentValue(float NewValue)
{
	float OldStateExp = StateExp;
	StateExp = FMath::Max(0.0f, NewValue);
	if (OldStateExp < StateExp)
	{
		//增加灵力密度
		BlueComponent->AddBlueDensity((StateExp - OldStateExp) * ExpToDensityRate);
	}
}

bool UStateComponent::UpgradeState()
{
	float SuccessRate = GetUpgradeSuccessRate();
	if (SuccessRate == -1)
	{
		return false;
	}
	else
	{
		if (FMath::FRand() <= SuccessRate)
		{
			LastUpgradeExp = 0;
			CurrentState = GetNextState();
			OnStateUpgrade.Broadcast(CurrentState);
			StateExp = 0;
			return true;
		}
		else
		{
			LastUpgradeExp = StateExp;
			StateExp = 0;
			return false;
		}
	}
}
//-1表示无法突破
//其他返回值表示突破到下一个境界的概率
float UStateComponent::GetUpgradeSuccessRate()
{
	if (StateExp <= LastUpgradeExp)
	{
		return 0;
	}
	else
	{
		return (StateExp / StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)] - 1) + UpgradeSuccessRate[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)];
	}
		
}

FJsonObject UStateComponent::SaveDataMethod() const
{
	TSharedPtr<FJsonObject> SaveData = MakeShared<FJsonObject>();
	SaveData->SetNumberField(TEXT("StateExp"), StateExp);
	SaveData->SetNumberField(TEXT("LastUpgradeExp"), LastUpgradeExp);
	SaveData->SetNumberField(TEXT("CurrentStateLarge"), static_cast<int>(CurrentState.LargeState));
	SaveData->SetNumberField(TEXT("CurrentStateSmall"), static_cast<int>(CurrentState.SmallState));
	return *SaveData;
}

void UStateComponent::LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject)
{
	StateExp = JsonObject->GetNumberField(TEXT("StateExp"));
	LastUpgradeExp = JsonObject->GetNumberField(TEXT("LastUpgradeExp"));
	CurrentState.LargeState = static_cast<ELargeState>(JsonObject->GetIntegerField(TEXT("CurrentStateLarge")));
	CurrentState.SmallState = static_cast<ESmallState>(JsonObject->GetIntegerField(TEXT("CurrentStateSmall")));
}
