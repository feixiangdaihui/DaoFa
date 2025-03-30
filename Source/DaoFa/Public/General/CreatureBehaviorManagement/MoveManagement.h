#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MoveManagement.generated.h"

class ISetValueInterface;
class IGetValueInterface;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UMoveManagement : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMoveManagement();

private:
	void LockRun() { RunLockTimer = RunLockTime; }
	void LockJump() { JumpLockTimer = JumpLockTime; }
	void LockDodge() { DodgeLockTimer = DodgeLockTime; }

	bool IsRunLock() { return RunLockTimer > 0; }
	bool IsJumpLock() { return JumpLockTimer > 0; }
	bool IsDodgeLock() { return DodgeLockTimer > 0; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//跑步消耗体力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float RunLossPhysicalPowerAmountBySecond = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "PhysicalPower")
	void RunLossPhysicalPower(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	bool IsRun = false;

	//跑步锁
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float RunLockTime = 1.0f;
	float RunLockTimer = 0.0;


	//一次性消耗体力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float JumpLoss = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float DodgeLoss = 10.0f;

	//跳跃锁
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float JumpLockTime = 1.0f;
	float JumpLockTimer = 0.0;

	//翻滚锁
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalPower")
	float DodgeLockTime = 1.0f;
	float DodgeLockTimer = 0.0;

	TScriptInterface<ISetValueInterface> SetPhysicalValue;
	TScriptInterface<IGetValueInterface> GetPhysicalValue;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckForRun();
	bool CheckForJump();
	bool CheckForDodge();

	void Run();
	void Jump();
	void Dodge();
	void StopRun();

	void Init(TScriptInterface<ISetValueInterface> InSetPhysicalValue, TScriptInterface<IGetValueInterface> InGetPhysicalValue)
	{
		SetPhysicalValue = InSetPhysicalValue;
		GetPhysicalValue = InGetPhysicalValue;
	}

	bool IsRuning() { return IsRun; }




};
