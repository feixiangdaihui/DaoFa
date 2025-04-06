// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Component/InputOperationComponent.h"
#include "Character/Animation/GetAnimation.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class AnimationType : uint8
{
	Idle,
	Walk,
	Run,
	Jump,
	Dodge,
	FirstAttack,
	SecondAttack,
	SpellLoop,
	SpellEnd,
	NONE
};



class ACreature;

UCLASS()
class DAOFA_API UBaseAnimInstance : public UAnimInstance 
{
	GENERATED_BODY()


	
	static TMap<AnimationType, TArray<AnimationType>> InputBlendAgree;

	//记录使用动画序列完成的动画状态
	static TSet<AnimationType> FlexibleState;
public:

	//更新动画状态
	//Input:要更新的动画状态
	//val:动画状态的值
	//返回值:是否更新成功
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateAnim(AnimationType Input) ;

	bool CheckAnim(AnimationType Input) ;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetIsMontageForbiden(bool value) { IsMontageForbiden = value; }

	AnimationType GetSequenceState() { return CurrentSequenceState; }

protected:
	//记录一次性完成的动画状态
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	AnimationType CurrentMontageState = AnimationType::NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsMontageForbiden = false;

	FOnMontageEnded MontageEndDelegate;


	//记录持续更新类的动画状态
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	AnimationType CurrentSequenceState= AnimationType::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<ACreature> OwnerCreature;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	bool IsFalling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	float ZVelocity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TMap<AnimationType, FMontageInfo> MontageMap;


};
