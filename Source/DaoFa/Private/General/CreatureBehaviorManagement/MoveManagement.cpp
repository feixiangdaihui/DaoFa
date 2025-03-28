#include "General/CreatureBehaviorManagement/MoveManagement.h"
#include"Character/Component/AttributeComponent/SetValueInterface.h"
// Sets default values for this component's properties
UMoveManagement::UMoveManagement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UMoveManagement::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UMoveManagement::RunLossPhysicalPower(float DeltaTime)
{
	if (IsRun)
	{
		SetPhysicalValue->SubtractValue(RunLossPhysicalPowerAmountBySecond * DeltaTime);
	}
}

// Called every frame
void UMoveManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RunLockTimer > 0)
		RunLockTimer -= DeltaTime;
	if (JumpLockTimer > 0)
		JumpLockTimer -= DeltaTime;
	if (DodgeLockTimer > 0)
		DodgeLockTimer -= DeltaTime;
	RunLossPhysicalPower(DeltaTime);



	// ...
}

bool UMoveManagement::CheckForRun()
{
	if (IsRunLock())
		return false;
	return true;
}

bool UMoveManagement::CheckForJump()
{
	if (IsJumpLock())
		return false;
	if (GetPhysicalValue->GetCurrentValue() >= JumpLoss)
		return true;
	return false;
}

bool UMoveManagement::CheckForDodge()
{
	if (IsDodgeLock())
		return false;
	if (GetPhysicalValue->GetCurrentValue() >= DodgeLoss)
		return true;
	return false;
}

void UMoveManagement::Run()
{
	if (GetPhysicalValue->IsEmpty())
	{
		LockRun();
		IsRun = false;
		return;
	}
	IsRun = true;
}



void UMoveManagement::Jump()
{
	SetPhysicalValue->SubtractValue(JumpLoss);
	LockJump();
}

void UMoveManagement::Dodge()
{
	SetPhysicalValue->SubtractValue(DodgeLoss);
	LockDodge();
}

void UMoveManagement::StopRun()
{
	IsRun = false;
}



