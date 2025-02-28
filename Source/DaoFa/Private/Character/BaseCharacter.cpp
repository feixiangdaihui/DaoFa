// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/Component/InputOperationComponent.h"
#include "Character/Component/AttributeComponent/AttributeComponent.h"
#include "Character/Component/PackComponent/PackComponent.h"
#include "General/EnemyDetector.h"
#include "Enemy/BaseEnemy.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	InputOperationComponent = CreateDefaultSubobject<UInputOperationComponent>(TEXT("InputOperationComponent"));

	EnemyDetector = CreateDefaultSubobject<UEnemyDetector>(TEXT("EnemyDetector"));
	EnemyDetector->DetectionRadius = 3000.0f;
	EnemyDetector->HorizontalAngle = 90.0f;
	EnemyDetector->VerticalAngle = 180.0f;
	EnemyDetector->EnemyClasses.Empty();
	EnemyDetector->EnemyClasses.Add(ABaseEnemy::StaticClass());


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetSpeedToWalk();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		InputOperationComponent->SetInputMappingContext(PlayerController->GetLocalPlayer());
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputOperationComponent->SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::SetSpeedToWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ABaseCharacter::SetSpeedToRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ABaseCharacter::InitSumEquipmentBar(USumEquipmentBarWidget* SumEquipmentBarWidget)
{
	InputOperationComponent->InitSumEquipmentBar(SumEquipmentBarWidget);
	PackComponent->InitSumEquipmentBar(SumEquipmentBarWidget);
}


