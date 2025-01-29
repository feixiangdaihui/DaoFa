// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/Interface/InputUpdateInterface.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */


class ABaseCharacter;

UCLASS()
class DAOFA_API UBaseAnimInstance : public UAnimInstance ,public IInputUpdateInterface
{
	GENERATED_BODY()

	static TMap<InputAnimation, TArray<InputAnimation>> InputBlendAgree;

	//记录使用动画序列完成的动画状态
	static TSet<InputAnimation> FlexibleState;
public:

	//更新动画状态
	//Input:要更新的动画状态
	//val:动画状态的值
	//返回值:是否更新成功
	UFUNCTION(BlueprintCallable, Category = "Animation")
	virtual bool UpdateInput(InputAnimation Input, int val = -1) override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

	void SetIsMontageForbiden(bool value) { IsMontageForbiden = value; }
	

protected:
	//记录蒙太奇完成的动画状态
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	InputAnimation CurrentMontageState=InputAnimation::NONE;
	int MontageStateValue = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsMontageForbiden = false;
	//记录动画序列完成的动画状态
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	InputAnimation CurrentSequenceState= InputAnimation::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<ABaseCharacter> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	bool IsFalling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	float ZVelocity = 0;


};
