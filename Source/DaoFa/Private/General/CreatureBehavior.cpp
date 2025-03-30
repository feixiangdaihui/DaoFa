#include "General/CreatureBehavior.h"
#include "InputActionValue.h"
#include "Character/Animation/BaseAnimInstance.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Character/Component/PackComponent/PackObject.h"
#include "Character/Component/AttributeComponent/BlueComponent.h"
#include "Creature.h"
#include "Character/Component/GongFa/BaseMainGongFa.h"
#include "Character/Component/GongFa/GongFaComponent.h"
#include"Character/BaseCharacter.h"
#include "General/CreatureBehaviorManagement/MoveManagement.h"
#include "General/CreatureBehaviorManagement/SpellManagement.h"
// Sets default values for this component's properties
UCreatureBehavior::UCreatureBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MoveManagement = CreateDefaultSubobject<UMoveManagement>(TEXT("MoveManagement"));
	SpellManagement = CreateDefaultSubobject<USpellManagement>(TEXT("SpellManagement"));
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
		MoveManagement->Init(OwnerPhysicalPowerComponent, OwnerPhysicalPowerComponent);
		SpellManagement->Init(OwnerBlueComponent, OwnerBlueComponent);
		if (!OwnerAnimInstance )
			UE_LOG(LogTemp, Error, TEXT("%s OwnerAnimInstance is nullptr"), *this->GetName());
		if (!OwnerPhysicalPowerComponent )
			UE_LOG(LogTemp, Error, TEXT("%s OwnerPhysicalPowerComponent is nullptr"), *this->GetName());
		if (!OwnerBlueComponent)
			UE_LOG(LogTemp, Error, TEXT("%s OwnerBlueComponent is nullptr"), *this->GetName());

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s OwnerCreature is nullptr"), *this->GetName());
	}

}

void UCreatureBehavior::BaseMove(const FVector2D& MovementVector)
{
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


// Called every frame
void UCreatureBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(OwnerAnimInstance&& MoveManagement&&OwnerAnimInstance->GetSequenceState()!=AnimationType::Run)
		MoveManagement->StopRun();

	// ...
}






void UCreatureBehavior::Jump()
{
	if (MoveManagement->CheckForJump() && OwnerAnimInstance->CheckAnim(AnimationType::Jump))
	{
		OwnerCreature->Jump();
		MoveManagement->Jump();
		OwnerAnimInstance->UpdateAnim(AnimationType::Jump);
	}
}

void UCreatureBehavior::Walk(const FVector2D& MovementVector)
{
	if (!IsMoveForbid && OwnerAnimInstance->CheckAnim(AnimationType::Walk))
	{
		OwnerCreature->SetSpeedToWalk();
		BaseMove(MovementVector);
		OwnerAnimInstance->UpdateAnim(AnimationType::Walk);
	}
	else
		Idle();
}



void UCreatureBehavior::Run(const FVector2D& MovementVector)
{
	if (!IsMoveForbid && MoveManagement->CheckForRun() && OwnerAnimInstance->CheckAnim(AnimationType::Run))
	{
		OwnerCreature->SetSpeedToRun();
		MoveManagement->Run();
		OwnerAnimInstance->UpdateAnim(AnimationType::Run);
		BaseMove(MovementVector);
	}
	else
		Walk(MovementVector);
}

void UCreatureBehavior::Idle()
{
	if (OwnerAnimInstance->CheckAnim(AnimationType::Idle))
	{
		OwnerAnimInstance->UpdateAnim(AnimationType::Idle);
	}
}




void UCreatureBehavior::Dodge()
{
	if (MoveManagement->CheckForDodge() && OwnerAnimInstance->CheckAnim(AnimationType::Dodge))
	{
		MoveManagement->Dodge();
		OwnerAnimInstance->UpdateAnim(AnimationType::Dodge);
	}

}

void UCreatureBehavior::BeginSpell(APackObject* Equipment)
{
	if (SpellManagement->CheckForSpell(Equipment) && CurrentEquipment == nullptr)
	{
		SpellManagement->SpellBegin(Equipment);
		OwnerAnimInstance->UpdateAnim(AnimationType::SpellLoop);
		GetWorld()->GetTimerManager().SetTimer(SpellTimerHandle, [this, Equipment]() {
			SpellManagement->SpellLoop(Equipment, 0.1f);
			}, 0.1f, true);
		CurrentEquipment = Equipment;
	}
}

void UCreatureBehavior::EndSpell(APackObject* Equipment)
{
	GetWorld()->GetTimerManager().ClearTimer(SpellTimerHandle);
	SpellManagement->SpellEnd(Equipment);
	OwnerAnimInstance->UpdateAnim(AnimationType::SpellEnd);
	CurrentEquipment = nullptr;
}

void UCreatureBehavior::Spell(APackObject* Equipment, float SpellTime)
{
	BeginSpell(Equipment);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Equipment]() {
		EndSpell(Equipment);
		}, SpellTime, false);
}









void UCreatureBehavior::FirstAttack()
{
	if (OwnerAnimInstance->CheckAnim(AnimationType::FirstAttack))
	{
		UGongFaComponent* GongFaComponent = OwnerCreature->GetGongFaComponent();
		if (GongFaComponent)
		{
			UBaseMainGongFa* MainGongFa = GongFaComponent->GetMainGongFa();
			if (MainGongFa)
			{
				if (MainGongFa->CheckFirstAttack())
				{
					MainGongFa->FirstAttack();
					OwnerAnimInstance->UpdateAnim(AnimationType::FirstAttack);
				}
			}
		}
	}
}

void UCreatureBehavior::SecondAttack()
{
	if (OwnerAnimInstance->CheckAnim(AnimationType::SecondAttack))
	{
		UGongFaComponent* GongFaComponent = OwnerCreature->GetGongFaComponent();
		if (GongFaComponent)
		{
			UBaseMainGongFa* MainGongFa = GongFaComponent->GetMainGongFa();
			if (MainGongFa)
			{
				if (MainGongFa->CheckSecondAttack())
				{
					MainGongFa->SecondAttack();
					OwnerAnimInstance->UpdateAnim(AnimationType::SecondAttack);
				}
			}
		}
	}
}






