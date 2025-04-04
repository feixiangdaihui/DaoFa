#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CreatureBehavior.generated.h"





class ACreature;
class UBaseAnimInstance;
class APackObject;
class UMoveManagement;
class USpellManagement;

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

	FTimerHandle SpellTimerHandle;

	void BeginSpell(APackObject* Equipment);

	void EndSpell(APackObject* Equipment);

	void Spell(APackObject* Equipment, float SpellTime);
	

	void FirstAttack();

	void SecondAttack();

	void SetMoveForbid(bool value) { IsMoveForbid = value; }

	APackObject* GetCurrentEquipment() { return CurrentEquipment; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
	TObjectPtr<UMoveManagement> MoveManagement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Creature")
	TObjectPtr<USpellManagement> SpellManagement;

private:

	void BaseMove(const FVector2D& MovementVector);

	APackObject* CurrentEquipment = nullptr;

	bool IsMoveForbid = false;


	ACreature* OwnerCreature;

	UBaseAnimInstance* OwnerAnimInstance;

	UFUNCTION()
	void OnPackObjectExhausted(APackObject* Equipment);




};
