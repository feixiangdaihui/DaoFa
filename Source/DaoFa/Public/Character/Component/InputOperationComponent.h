// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputOperationComponent.generated.h"

class UInputAction;
class ABaseCharacter;
class UInputComponent;
struct FInputActionValue;
class UInputMappingContext;
class UBaseAnimInstance;


//负责告诉动画实例类现在的输入状态
//动画实例类根据输入状态来判断是否播放动画
//该类从而判断是否进行移动或者其他
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UInputOperationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputOperationComponent();
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	//设置输入映射上下文为当前组件所指定的上下文
	void SetInputMappingContext(ULocalPlayer* LocalPlayer);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	TObjectPtr<ABaseCharacter> OwnerCharacter;

	TObjectPtr<UBaseAnimInstance> OwnerAnimInstance;
	
	/* Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/* Walk Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WalkAction;

	/* Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	/* Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/* Dodge Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeAction;

	/* FirstAttack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FirstAttackAction;

	/* SecondAttack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondAttackAction;

	/** Spell Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<UInputAction*> SpellAction;

	/* ChangeSpellToSmall Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeSpellToSmallAction;

	/* ChangeSpellToBig Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeSpellToBigAction;

	/* OpenPack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenPackAction;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;


	void Jump();

	void StopJumping();

	void Walk(const FInputActionValue& Value);

	void BaseWalk(const FInputActionValue& Value);

	void StopWalk();

	void Run();

	void StopRun();
	
	void Look(const FInputActionValue& Value);

	void Dodge();

	void FirstAttack(const FInputActionValue& Value);

	void SecondAttack(const FInputActionValue& Value);

	void Spell(const FInputActionValue& Value);

	void ChangeSpellToSmall(const FInputActionValue& Value);

	void ChangeSpellToBig(const FInputActionValue& Value);

	void OpenPack(const FInputActionValue& Value);


	bool IsRunning = false;


		
};
