// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/BaseAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


//记录蒙太奇无法与其他哪些动画序列同时进行
TMap<InputAnimation, TArray<InputAnimation>> UBaseAnimInstance::InputBlendAgree =
{
	{InputAnimation::FirstAttack,{InputAnimation::Idle}},
	{InputAnimation::SecondAttack,{InputAnimation::Idle}},
	{InputAnimation::Spell,{InputAnimation::Idle,InputAnimation::Spell,InputAnimation::Walk}},
	{InputAnimation::Dodge,{InputAnimation::Idle}}
};
TSet<InputAnimation> UBaseAnimInstance::FlexibleState = { InputAnimation::Run, InputAnimation::Idle ,InputAnimation::Walk ,InputAnimation::Jump };



bool UBaseAnimInstance::UpdateInput(InputAnimation Input, int val)
{
	
	if (OwnerCharacter)
	{
		if (CurrentMontageState!=InputAnimation::NONE&&!InputBlendAgree[CurrentMontageState].Contains(Input))
			return false;
		else
		{
			if (FlexibleState.Contains(Input))
			{
				CurrentSequenceState = Input;
				return true;
			}
			else
			{
				CurrentMontageState = Input;
				MontageStateValue = val;
				IsMontageForbiden = false;
				return true;
			}
		}
	}
	return false;
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		ZVelocity = OwnerCharacter->GetCharacterMovement()->Velocity.Z;
		IsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
		
	}
}

void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ABaseCharacter>(GetOwningActor());
}
