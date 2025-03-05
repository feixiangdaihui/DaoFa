// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/InputOperationComponent.h"
#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Hud/BaseHud.h"
#include "General/CreatureBehavior.h"
// Sets default values for this component's properties
UInputOperationComponent::UInputOperationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts


// Called every frame






void UInputOperationComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// ...
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (OwnerCharacter != nullptr)
	{

		OwnerHud = Cast<ABaseHud>(OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD());
		OwnerCreatureBehavior = OwnerCharacter->GetCreatureBehavior();
		if (!IsValid(OwnerCreatureBehavior))
		{
			UE_LOG(LogTemp, Error, TEXT("OwnerCreatureBehavior is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerCharacter is nullptr"));
	}
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Jump);
		// Moving
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, OwnerCreatureBehavior, &UCreatureBehavior::Walk);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, OwnerCreatureBehavior, &UCreatureBehavior::StopWalk);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, OwnerCreatureBehavior, &UCreatureBehavior::StopRun);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputOperationComponent::Look);
		//Dodge
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Dodge);

		//ChangeChosenEquipmentBar
		EnhancedInputComponent->BindAction(ChangeChosenEquipmentBarToSmallAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::ChangeChosenEquipmentBarToSmall);
		EnhancedInputComponent->BindAction(ChangeChosenEquipmentBarToBigAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::ChangeChosenEquipmentBarToBig);

		//Pack
		EnhancedInputComponent->BindAction(OpenPackAction, ETriggerEvent::Started, this, &UInputOperationComponent::OpenPack);
		OpenPackAction->bTriggerWhenPaused = true;

		//Spell
		EnhancedInputComponent->BindAction(SpellAction0, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 0, true);
		EnhancedInputComponent->BindAction(SpellAction0, ETriggerEvent::Completed, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 0, false);
		EnhancedInputComponent->BindAction(SpellAction1, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 1, true);
		EnhancedInputComponent->BindAction(SpellAction1, ETriggerEvent::Completed, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 1, false);
		EnhancedInputComponent->BindAction(SpellAction2, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 2, true);
		EnhancedInputComponent->BindAction(SpellAction2, ETriggerEvent::Completed, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 2, false);
		EnhancedInputComponent->BindAction(SpellAction3, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 3, true);
		EnhancedInputComponent->BindAction(SpellAction3, ETriggerEvent::Completed, OwnerCreatureBehavior, &UCreatureBehavior::Spell, 3, false);

	}
}

void UInputOperationComponent::SetInputMappingContext(ULocalPlayer* LocalPlayer)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 1);
	}
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


