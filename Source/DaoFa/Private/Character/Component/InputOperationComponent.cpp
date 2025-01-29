// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/InputOperationComponent.h"
#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Character/Animation/BaseAnimInstance.h"
#include "Character/Component/AttributeComponent/AttributeComponent.h"


// Sets default values for this component's properties
UInputOperationComponent::UInputOperationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputOperationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (OwnerCharacter != nullptr)
	{
		OwnerAnimInstance = Cast<UBaseAnimInstance>(OwnerCharacter->GetMesh()->GetAnimInstance());
		OwnerAttributeComponent = OwnerCharacter->AttributeComponent;
		if (OwnerAttributeComponent == nullptr)
			UE_LOG(LogTemp, Error, TEXT("OwnerAttributeComponent is nullptr"));
		if (OwnerAnimInstance == nullptr)
			UE_LOG(LogTemp, Error, TEXT("OwnerAnimInstance is nullptr"));
	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerCharacter is nullptr"));
	}
}


// Called every frame
void UInputOperationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInputOperationComponent::UpdateInput(InputAnimation Input, int val)
{
	if (OwnerAnimInstance!=nullptr&&OwnerAnimInstance->UpdateInput(Input, val))
	{
		if (OwnerAttributeComponent != nullptr)
			return OwnerAttributeComponent->UpdateInput(Input, val);
	}
	return false;
}



void UInputOperationComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UInputOperationComponent::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UInputOperationComponent::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &UInputOperationComponent::Walk);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, this, &UInputOperationComponent::StopWalk);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &UInputOperationComponent::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &UInputOperationComponent::StopRun);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputOperationComponent::Look);
		//Dodge
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &UInputOperationComponent::Dodge);
	}
}

void UInputOperationComponent::SetInputMappingContext(ULocalPlayer* LocalPlayer)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 1);
	}
}



void UInputOperationComponent::Jump()
{
	if (UpdateInput(InputAnimation::Jump))
	{
		OwnerCharacter->Jump();
	}
}

void UInputOperationComponent::StopJumping()
{
	if (OwnerCharacter != nullptr )
	{
		OwnerCharacter->StopJumping();
	}
}

void UInputOperationComponent::Walk(const FInputActionValue& Value)
{

	if (OwnerCharacter != nullptr && OwnerAnimInstance != nullptr&&OwnerAttributeComponent!=nullptr)
	{
		if(IsRunning&& UpdateInput(InputAnimation::Run))
		{
			OwnerCharacter->SetSpeedToRun();
			BaseWalk(Value);
		}
		else if (UpdateInput(InputAnimation::Walk))
		{
			OwnerCharacter->SetSpeedToWalk();
			BaseWalk(Value);
		}

	}

}

void UInputOperationComponent::BaseWalk(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// find out which way is forward
	const FRotator Rotation = OwnerCharacter->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement 
	OwnerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	OwnerCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void UInputOperationComponent::StopWalk()
{
	UpdateInput(InputAnimation::Idle);
}

void UInputOperationComponent::Run()
{
	IsRunning = true;
}

void UInputOperationComponent::StopRun()
{
	IsRunning=false;
	if (OwnerAttributeComponent != nullptr)
		OwnerAttributeComponent->UpdateInput(InputAnimation::EndRun);
}

void UInputOperationComponent::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (OwnerCharacter != nullptr)
	{
		// add yaw and pitch input to controller
		OwnerCharacter->AddControllerYawInput(LookAxisVector.X);
		OwnerCharacter->AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void UInputOperationComponent::Dodge()
{
	if (UpdateInput(InputAnimation::Dodge))
	{
		if(OwnerAnimInstance!=nullptr)
			OwnerAnimInstance->SetIsMontageForbiden(false);
	}

}

void UInputOperationComponent::FirstAttack(const FInputActionValue& Value)
{
	if (OwnerAnimInstance != nullptr && OwnerAnimInstance->UpdateInput(InputAnimation::FirstAttack))
	{
	}
}

void UInputOperationComponent::SecondAttack(const FInputActionValue& Value)
{
	if (OwnerAnimInstance != nullptr && OwnerAnimInstance->UpdateInput(InputAnimation::SecondAttack))
	{
	}
}

void UInputOperationComponent::Spell(const FInputActionValue& Value)
{
}

void UInputOperationComponent::ChangeSpellToSmall(const FInputActionValue& Value)
{
}

void UInputOperationComponent::ChangeSpellToBig(const FInputActionValue& Value)
{
}

void UInputOperationComponent::OpenPack(const FInputActionValue& Value)
{
}



