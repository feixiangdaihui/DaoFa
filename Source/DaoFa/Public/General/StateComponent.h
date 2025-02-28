#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

#define LARGE_STATE_NUM 5
#define SMALL_STATE_NUM 4
UENUM(BlueprintType)
enum class ELargeState : uint8
{
	LIANQI,
	ZHUJI,
	JINDAN,
	YUANYING,
	HUASHEN,

};
UENUM(BlueprintType)
enum class ESmallState : uint8
{
	Early,
	Middle,
	Late,
	Complete,
};

USTRUCT(BlueprintType)
struct FState
{
	GENERATED_BODY()
public:	
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ELargeState LargeState;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ESmallState SmallState;

	//重载操作符
	bool operator==(const FState& Other) const
	{
		return LargeState == Other.LargeState && SmallState == Other.SmallState;
	}
	bool operator!=(const FState& Other) const
	{
		return LargeState != Other.LargeState || SmallState != Other.SmallState;
	}
	bool operator<(const FState& Other) const
	{
		return LargeState < Other.LargeState || (LargeState == Other.LargeState && SmallState < Other.SmallState);
	}
	bool operator>(const FState& Other) const
	{
		return LargeState > Other.LargeState || (LargeState == Other.LargeState && SmallState > Other.SmallState);
	}
	bool operator<=(const FState& Other) const
	{
		return LargeState < Other.LargeState || (LargeState == Other.LargeState && SmallState <= Other.SmallState);
	}
	bool operator>=(const FState& Other) const
	{
		return LargeState > Other.LargeState || (LargeState == Other.LargeState && SmallState >= Other.SmallState);
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "State")
	FState CurrentState = { ELargeState::LIANQI, ESmallState::Early };

private:
	//境界差异导致的伤害倍率
	static float CreatureStateDamageMultiplier[LARGE_STATE_NUM][SMALL_STATE_NUM];
	//物品和角色的境界差异导致的伤害倍率
	static float ItemCreatureStateDamageMultiplier[LARGE_STATE_NUM];

public:
	//计算境界差异导致的伤害倍率
	static float CalCreatureStateDamageMultiplier(FState SelfState, FState OtherState);

	//计算物品和角色的境界不匹配度导致的伤害倍率
	static float CalItemCreatureStateDamageMultiplier(FState SelfState, FState ItemState);


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FState GetState() { return CurrentState; }


};
