// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/InputOperationComponent.h"
#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Character/Animation/BaseAnimInstance.h"
#include "Character/Component/AttributeComponent/AttributeComponent.h"
#include "Character/Component/AttributeComponent/PhysicalPowerComponent.h"
#include "Character/Component/PackComponent/SumEquipmentBarWidget.h"
#include "Hud/BaseHud.h"
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
		UAttributeComponent* OwnerAttributeComponent = OwnerCharacter->AttributeComponent;
		UPhysicalPowerComponent* OwnerPhysicalPowerComponent = OwnerAttributeComponent->PhysicalPowerComponent;
		OwnerHud = Cast<ABaseHud>(OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD());

		if (OwnerAnimInstance != nullptr)
			InputUpdateInterfaces.Add(OwnerAnimInstance);
		if (OwnerPhysicalPowerComponent != nullptr)
			InputUpdateInterfaces.Add(OwnerPhysicalPowerComponent);
	
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

void UInputOperationComponent::UpdateInput(InputAnimation Input)
{
	for (auto InputUpdateInterface : InputUpdateInterfaces)
	{
		InputUpdateInterface->UpdateInput(Input);
	}
}

bool UInputOperationComponent::CheckInput(InputAnimation Input)
{
	for (auto InputUpdateInterface : InputUpdateInterfaces)
	{
		if (!InputUpdateInterface->CheckInput(Input))
			return false;
	}
	return true;
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

		//ChangeChosenEquipmentBar
		EnhancedInputComponent->BindAction(ChangeChosenEquipmentBarToSmallAction, ETriggerEvent::Started, this, &UInputOperationComponent::ChangeChosenEquipmentBarToSmall);
		EnhancedInputComponent->BindAction(ChangeChosenEquipmentBarToBigAction, ETriggerEvent::Started, this, &UInputOperationComponent::ChangeChosenEquipmentBarToBig);

		//Pack
		EnhancedInputComponent->BindAction(OpenPackAction, ETriggerEvent::Started, this, &UInputOperationComponent::OpenPack);
		OpenPackAction->bTriggerWhenPaused = true;

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
	if (CheckInput(InputAnimation::Jump))
	{
		OwnerCharacter->Jump();
		UpdateInput(InputAnimation::Jump);
	}
}

void UInputOperationComponent::StopJumping()
{
	if (OwnerCharacter != nullptr )
	{
		OwnerCharacter->StopJumping();
		UpdateInput(InputAnimation::NONE);
	}
}

void UInputOperationComponent::Walk(const FInputActionValue& Value)
{

	if (OwnerCharacter != nullptr )
	{
		if(IsRunning&& CheckInput(InputAnimation::Run))
		{
			OwnerCharacter->SetSpeedToRun();
			UpdateInput(InputAnimation::Run);
			BaseWalk(Value);
		}
		else if (CheckInput(InputAnimation::Walk))
		{
			OwnerCharacter->SetSpeedToWalk();
			UpdateInput(InputAnimation::Walk);
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
	if (CheckInput(InputAnimation::Dodge))
	{
		UpdateInput(InputAnimation::Dodge);
	}

}

void UInputOperationComponent::FirstAttack(const FInputActionValue& Value)
{
	
}

void UInputOperationComponent::SecondAttack(const FInputActionValue& Value)
{
	
}

void UInputOperationComponent::Spell(const FInputActionValue& Value)
{
}

void UInputOperationComponent::ChangeChosenEquipmentBarToSmall(const FInputActionValue& Value)
{
	if (OwnerSumEquipmentBarWidget)
	{
		OwnerSumEquipmentBarWidget->ChangeChosenEquipmentBarToSmall();
	}
}

void UInputOperationComponent::ChangeChosenEquipmentBarToBig(const FInputActionValue& Value)
{
	if (OwnerSumEquipmentBarWidget)
	{
		OwnerSumEquipmentBarWidget->ChangeChosenEquipmentBarToBig();
	}
}


void UInputOperationComponent::OpenPack()
{
	if (IsPackOpen)
	{

		OwnerHud->ClosePack();
		IsPackOpen = false;
	}
	else
	{
		OwnerHud->OpenPack();
		IsPackOpen = true;
	}
}

void UInputOperationComponent::InitSumEquipmentBar(USumEquipmentBarWidget* SumEquipmentBarWidget)
{
	OwnerSumEquipmentBarWidget = SumEquipmentBarWidget;
}



