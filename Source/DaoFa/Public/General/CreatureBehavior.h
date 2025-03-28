#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CreatureBehavior.generated.h"




class UInputAction;
class ACreature;
class UInputComponent;
struct FInputActionValue;
class UInputMappingContext;
class UBaseAnimInstance;
class USumEquipmentBarWidget;
class ABaseHud;
class APackObject;
class UMoveManagement;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpell, APackObject*, Equipment);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UCreatureBehavior : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCreatureBehavior();

	friend class UInputOperationComponent;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnSpell OnSpell;


	void Jump();

	void Walk(const FVector2D& MovementVector);

	void Run(const FVector2D& MovementVector);

	void Idle();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float DodgeUnbeatableTime = 0.5f;
	void Dodge();

	//1表示开始释放技能，0表示结束释放技能
	void Spell(APackObject* Equipment, bool Begin);

	void FirstAttack();

	void SecondAttack();

	void SetMoveForbid(bool value) { IsMoveForbid = value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
	TObjectPtr<UMoveManagement> MoveManagement;

private:

	void BaseMove(const FVector2D& MovementVector);

	APackObject* CurrentEquipment = nullptr;

	bool IsMoveForbid = false;


	ACreature* OwnerCreature;

	UBaseAnimInstance* OwnerAnimInstance;


};
