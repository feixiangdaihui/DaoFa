// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/BaseAnimInstance.h"
#include "Creature.h"
#include "GameFramework/CharacterMovementComponent.h"


//记录哪些状态可以共存
//IdleWalkRun持续输入的状态无需单独记录
//具有先后顺序，不一定完全对称（意味着可以从A到B，但不一定可以从B到A）
//NONE表示中止当前蒙太奇动画
TMap<InputAnimation, TArray<InputAnimation>> UBaseAnimInstance::InputBlendAgree =
{
	{InputAnimation::FirstAttack,{InputAnimation::Idle}},
	{InputAnimation::SecondAttack,{InputAnimation::Idle}},
	{InputAnimation::SpellLoop,{InputAnimation::Idle,InputAnimation::Walk,InputAnimation::SpellEnd}},
	{InputAnimation::Dodge,{InputAnimation::Idle}},
	{InputAnimation::Jump,{InputAnimation::Run, InputAnimation::Idle ,InputAnimation::Walk} },
	{InputAnimation::SpellEnd ,{InputAnimation::Idle,InputAnimation::Walk}},

};
TSet<InputAnimation> UBaseAnimInstance::FlexibleState = { InputAnimation::Run, InputAnimation::Idle ,InputAnimation::Walk };




//Input==NONE时表示中止当前蒙太奇动画
void UBaseAnimInstance::UpdateInput(InputAnimation Input)
{
	if (OwnerCreature)
	{

		if (FlexibleState.Contains(Input))
		{
			CurrentSequenceState = Input;
		}
		else 
		{
			IsMontageForbiden = false;
			CurrentMontageState = Input;
			if (CurrentMontageState == InputAnimation::NONE)
				StopAllMontages(0.25f);
		}

	}

}

bool UBaseAnimInstance::CheckInput(InputAnimation Input)
{
	if (OwnerCreature)
	{
		if (CurrentMontageState != InputAnimation::NONE && !InputBlendAgree[CurrentMontageState].Contains(Input))
			return false;
		return true;
	}
	return false;
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCreature)
	{
		ZVelocity = OwnerCreature->GetCharacterMovement()->Velocity.Z;
		IsFalling = OwnerCreature->GetCharacterMovement()->IsFalling();
		if(!IsFalling&& CurrentMontageState == InputAnimation::Jump)
			CurrentMontageState = InputAnimation::NONE;
		
	}
}

void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCreature = Cast<ACreature>(GetOwningActor());
}



