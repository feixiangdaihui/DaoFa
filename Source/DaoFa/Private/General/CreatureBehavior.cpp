#include "General/CreatureBehavior.h"
#include "InputActionValue.h"
#include "Character/Animation/BaseAnimInstance.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Creature.h"
// Sets default values for this component's properties
UCreatureBehavior::UCreatureBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCreatureBehavior::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCreature = Cast<ACreature>(GetOwner());
	if (OwnerCreature != nullptr)
	{
		OwnerAnimInstance = Cast<UBaseAnimInstance>(OwnerCreature->GetMesh()->GetAnimInstance());
		UPhysicalPowerComponent* OwnerPhysicalPowerComponent = OwnerCreature->GetPhysicalPowerComponent();
		UBlueComponent* OwnerBlueComponent = OwnerCreature->GetBlueComponent();
		if (OwnerBlueComponent)
			OwnerBlueComponent->OnBlueEmpty.AddDynamic(this, &UCreatureBehavior::OnBlueEmpty);
		else
			UE_LOG(LogTemp, Error, TEXT("OwnerBlueComponent is nullptr"));

		if (OwnerAnimInstance != nullptr)
			InputUpdateInterfaces.Add(OwnerAnimInstance);
		else
			UE_LOG(LogTemp, Error, TEXT("OwnerAnimInstance is nullptr"));
		if (OwnerPhysicalPowerComponent != nullptr)
			InputUpdateInterfaces.Add(OwnerPhysicalPowerComponent);
		else
			UE_LOG(LogTemp, Error, TEXT("OwnerPhysicalPowerComponent is nullptr"));

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerCreature is nullptr"));
	}

}


// Called every frame
void UCreatureBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCreatureBehavior::SetMoveForbid(bool NewValue)
{
	if (NewValue)
		UpdateInput(InputAnimation::Idle);
	IsMoveForbid = NewValue;
}

void UCreatureBehavior::UpdateInput(InputAnimation Input)
{
	for (auto InputUpdateInterface : InputUpdateInterfaces)
	{
		InputUpdateInterface->UpdateInput(Input);
	}
}

bool UCreatureBehavior::CheckInput(InputAnimation Input)
{
	for (auto InputUpdateInterface : InputUpdateInterfaces)
	{
		if (!InputUpdateInterface->CheckInput(Input))
			return false;
	}
	return true;
}




void UCreatureBehavior::Jump()
{
	if (CheckInput(InputAnimation::Jump))
	{
		OwnerCreature->Jump();
		UpdateInput(InputAnimation::Jump);
	}
}


void UCreatureBehavior::Walk(const FInputActionValue& Value)
{

	if (OwnerCreature != nullptr&&!IsMoveForbid)
	{
		if (IsRunning && CheckInput(InputAnimation::Run))
		{
			OwnerCreature->SetSpeedToRun();
			UpdateInput(InputAnimation::Run);
			BaseWalk(Value);
		}
		else if (CheckInput(InputAnimation::Walk))
		{
			OwnerCreature->SetSpeedToWalk();
			UpdateInput(InputAnimation::Walk);
			BaseWalk(Value);

		}

	}

}

void UCreatureBehavior::BaseWalk(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// find out which way is forward
	const FRotator Rotation = OwnerCreature->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement 
	OwnerCreature->AddMovementInput(ForwardDirection, MovementVector.Y);
	OwnerCreature->AddMovementInput(RightDirection, MovementVector.X);
}

void UCreatureBehavior::StopWalk()
{
	UpdateInput(InputAnimation::Idle);
}

void UCreatureBehavior::Run()
{
	IsRunning = true;
}

void UCreatureBehavior::StopRun()
{
	IsRunning = false;
}

void UCreatureBehavior::ChangeChosenEquipmentBarToSmall()
{
	if (OwnerSumEquipmentBarWidget)
	{
		OwnerSumEquipmentBarWidget->ChangeChosenEquipmentBarToSmall();
	}
}

void UCreatureBehavior::ChangeChosenEquipmentBarToBig()
{
	if (OwnerSumEquipmentBarWidget)
	{
		OwnerSumEquipmentBarWidget->ChangeChosenEquipmentBarToBig();
	}
}


void UCreatureBehavior::Dodge()
{
	if (CheckInput(InputAnimation::Dodge))
	{
		UpdateInput(InputAnimation::Dodge);
		OwnerCreature->SetUnbeatable(true);
		//设置定时器
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {OwnerCreature->SetUnbeatable(false); }, DodgeUnbeatableTime, false);
	}

}



void UCreatureBehavior::Spell(int Num, bool Begin)
{
	if (Begin)
	{
		if (CheckInput(InputAnimation::SpellLoop))
		{
			CurrentPackObject = OwnerSumEquipmentBarWidget->GetEquipment(Num);
			if (CurrentPackObject)
			{
				if (CurrentPackObject->TriggeredBegin())
				{
					UpdateInput(InputAnimation::SpellLoop);
				}
			}
		}
	}
	else
	{
		if (CheckInput(InputAnimation::SpellEnd))
		{
			if (CurrentPackObject)
			{
				if (CurrentPackObject->TriggeredEnd())
				{
					UpdateInput(InputAnimation::SpellEnd);
				}
				else
				{
					UpdateInput(InputAnimation::NONE);
				}
			}
		}
	}
}

void UCreatureBehavior::OnBlueEmpty()
{
	if (CurrentPackObject)
	{
		CurrentPackObject->TriggeredEnd();
		UpdateInput(InputAnimation::SpellEnd);
		CurrentPackObject = nullptr;
	}

}



void UCreatureBehavior::InitSumEquipmentBar(USumEquipmentBarWidget* SumEquipmentBarWidget)
{
	OwnerSumEquipmentBarWidget = SumEquipmentBarWidget;
}




