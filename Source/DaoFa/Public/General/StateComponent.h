#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Component/AttributeComponent/GetValueInterface.h"
#include "Character/Component/AttributeComponent/SetValueInterface.h"
#include "General/Interface/SaveLoadData.h"
#include "StateComponent.generated.h"

#define LARGE_STATE_NUM 5
#define SMALL_STATE_NUM 4
class UBlueComponent;



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

	FState() : LargeState(ELargeState::LIANQI), SmallState(ESmallState::Early) {}

	FState(ELargeState InLargeState, ESmallState InSmallState) : LargeState(InLargeState), SmallState(InSmallState) {}

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

//境界突破的事件，参数为当前境界
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateUpgrade, FState, CurrentState);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UStateComponent : public UActorComponent, public IGetValueInterface, public ISetValueInterface, public ISaveLoadData
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

	float StateExp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	UBlueComponent* BlueComponent;


	float LastUpgradeExp = 0.0f;

private:
	//境界差异导致的伤害倍率
	static float CreatureStateDamageMultiplier[LARGE_STATE_NUM][SMALL_STATE_NUM];
	//物品和角色的境界差异导致的伤害倍率
	static float ItemCreatureStateDamageMultiplier[LARGE_STATE_NUM];
	//境界经验表
	static float StateExpTable[LARGE_STATE_NUM][SMALL_STATE_NUM];

	//每个境界超出的经验值作用在增加灵力密度上的比例
	static float ExpToDensityRate;
	//境界升级成功率
	static float UpgradeSuccessRate[LARGE_STATE_NUM][SMALL_STATE_NUM];

	static TMap<ELargeState, FText> LargeStateTextMap;

	static TMap<ESmallState, FText> SmallStateTextMap;





public:

	UFUNCTION(BlueprintCallable, Category = "State")
	static FText GetLargeStateText(ELargeState InLargeState)
	{
		return LargeStateTextMap.FindChecked(InLargeState);
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	static FText GetSmallStateText(ESmallState InSmallState)
	{
		return SmallStateTextMap.FindChecked(InSmallState);
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	static FText GetStateText(FState InState)
	{
		return FText::Format(FText::FromString("{0}{1}"), GetLargeStateText(InState.LargeState), GetSmallStateText(InState.SmallState));
	}

	UPROPERTY(BlueprintAssignable, Category = "State")
	FOnStateUpgrade OnStateUpgrade;
	//计算境界差异导致的伤害倍率
	static float CalCreatureStateDamageMultiplier(FState SelfState, FState OtherState);

	//计算物品和角色的境界不匹配度导致的伤害倍率
	static float CalItemCreatureStateDamageMultiplier(FState SelfState, FState ItemState);




	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "State")
	float GetCurrentValue() const override { return StateExp; }

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetMaxValue() const override { return StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)]; }

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetPercentage() const override { return StateExp / StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)]; }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsFull() const override { return StateExp == StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)]; }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool IsEmpty() const override { return StateExp == 0; }



	UFUNCTION(BlueprintCallable, Category = "State")
	void SetCurrentValue(float NewValue) override;

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetMaxValue(float NewValue) override{}

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetPercentage(float NewValue) override {
		SetCurrentValue(StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)] * NewValue);
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetFull() override { SetCurrentValue(StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)]); }

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetEmpty() override { SetCurrentValue(0); }

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddValue(float Value) override { SetCurrentValue(StateExp + Value); }

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddPercentage(float Value) override { SetCurrentValue(StateExp + StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)] * Value); }

	UFUNCTION(BlueprintCallable, Category = "State")
	bool SubtractValue(float Value) override
	{
		SetCurrentValue(StateExp - Value);
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	bool SubtractPercentage(float Value) override
	{
		SetCurrentValue(StateExp - StateExpTable[static_cast<int>(CurrentState.LargeState)][static_cast<int>(CurrentState.SmallState)] * Value);
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "State")
	bool UpgradeState();

	UFUNCTION(BlueprintCallable, Category = "State")
	FState GetNextState();

	UFUNCTION(BlueprintCallable, Category = "State")
	FState GetState() { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetUpgradeSuccessRate();

	void InitStateComponent(UBlueComponent* InBlueComponent) { BlueComponent = InBlueComponent; }

	
	//存档
	virtual FJsonObject SaveDataMethod() const override;

	virtual void LoadDataMethod(const TSharedPtr<FJsonObject> JsonObject) override;

	virtual FString GetKey() const override { return TEXT("StateComponent"); }








};
