// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/InputOperationComponent.h"
#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Hud/BaseHud.h"
#include "General/CreatureBehavior.h"
#include "Character/Component/PackComponent/EquipmentBarComponent.h"
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
		OwnerEquipmentBarComponent = OwnerCharacter->GetEquipmentBarComponent();
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
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &UInputOperationComponent::Walk);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Completed, this, &UInputOperationComponent::Idle);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &UInputOperationComponent::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &UInputOperationComponent::StopRun);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputOperationComponent::Look);
		//Dodge
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::Dodge);

		//ChangeChosenEquipmentBar
		EnhancedInputComponent->BindAction(ChangeChosenEquipmentBarToSmallAction, ETriggerEvent::Started,this, &UInputOperationComponent::ChangeChosenEquipmentBarToSmall);
		EnhancedInputComponent->BindAction(ChangeChosenEquipmentBarToBigAction, ETriggerEvent::Started,this, &UInputOperationComponent::ChangeChosenEquipmentBarToBig);

		//Pack
		EnhancedInputComponent->BindAction(OpenPackAction, ETriggerEvent::Started, this, &UInputOperationComponent::OpenPack);
		OpenPackAction->bTriggerWhenPaused = true;

		//Spell
		EnhancedInputComponent->BindAction(SpellAction0, ETriggerEvent::Started,this, &UInputOperationComponent::Spell, 0, true);
		EnhancedInputComponent->BindAction(SpellAction0, ETriggerEvent::Completed,this, &UInputOperationComponent::Spell, 0, false);
		EnhancedInputComponent->BindAction(SpellAction1, ETriggerEvent::Started,this, &UInputOperationComponent::Spell, 1, true);
		EnhancedInputComponent->BindAction(SpellAction1, ETriggerEvent::Completed,this, &UInputOperationComponent::Spell, 1, false);
		EnhancedInputComponent->BindAction(SpellAction2, ETriggerEvent::Started,this, &UInputOperationComponent::Spell, 2, true);
		EnhancedInputComponent->BindAction(SpellAction2, ETriggerEvent::Completed,this, &UInputOperationComponent::Spell, 2, false);
		EnhancedInputComponent->BindAction(SpellAction3, ETriggerEvent::Started,this, &UInputOperationComponent::Spell, 3, true);
		EnhancedInputComponent->BindAction(SpellAction3, ETriggerEvent::Completed,this, &UInputOperationComponent::Spell, 3, false);

		//Attack
		EnhancedInputComponent->BindAction(FirstAttackAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::FirstAttack);
		EnhancedInputComponent->BindAction(SecondAttackAction, ETriggerEvent::Started, OwnerCreatureBehavior, &UCreatureBehavior::SecondAttack);

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

void UInputOperationComponent::Walk(const FInputActionValue& Value)
{
	if (OwnerCreatureBehavior)
	{
		if (IsRun)
			OwnerCreatureBehavior->Run(Value.Get<FVector2D>());
		else
			OwnerCreatureBehavior->Walk(Value.Get<FVector2D>());
	}
}

void UInputOperationComponent::Idle()
{
	if (OwnerCreatureBehavior)
	{
		OwnerCreatureBehavior->Idle();
	}
}

void UInputOperationComponent::Run()
{
	IsRun = true;
}



void UInputOperationComponent::StopRun()
{
	IsRun = false;
}

void UInputOperationComponent::OpenPack()
{
	OwnerHud->OpenClosePack();
}

void UInputOperationComponent::ChangeChosenEquipmentBarToSmall()
{
	if (OwnerEquipmentBarComponent)
	{
		OwnerEquipmentBarComponent->ChangeChosenEquipmentBarToSmall();
	}
}

void UInputOperationComponent::ChangeChosenEquipmentBarToBig()
{
	if (OwnerEquipmentBarComponent)
	{
		OwnerEquipmentBarComponent->ChangeChosenEquipmentBarToBig();
	}
}

void UInputOperationComponent::Spell(int32 Index, bool Begin)
{
	if (OwnerEquipmentBarComponent)
	{
		if(OwnerCreatureBehavior)
		{
			if (APackObject* Temp=OwnerEquipmentBarComponent->GetEquipment(Index))
				OwnerCreatureBehavior->Spell(Temp, Begin);
		}
	}
}


