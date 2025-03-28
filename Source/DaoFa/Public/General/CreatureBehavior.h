#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Interface/InputUpdateInterface.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpell, APackObject*, Equipment);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UCreatureBehavior : public UActorComponent, public IInputUpdateInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCreatureBehavior();

	friend class UInputOperationComponent;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnSpell OnSpell;

	void SetMoveForbid(bool NewValue);

	void Jump();

	void Walk(const FInputActionValue& Value);

	void BaseWalk(const FInputActionValue& Value);

	void StopWalk();

	void Run();

	void StopRun();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float DodgeUnbeatableTime = 0.5f;
	void Dodge();

	//1表示开始释放技能，0表示结束释放技能
	void Spell(APackObject* Equipment, bool Begin);

	void FirstAttack();

	void SecondAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:



	APackObject* CurrentEquipment = nullptr;

	bool IsRunning = false;

	bool IsMoveForbid = false;

	virtual void UpdateInput(InputAnimation Input) override;

	virtual bool CheckInput(InputAnimation Input) override;

	TArray<TScriptInterface<IInputUpdateInterface>> InputUpdateInterfaces;

	ACreature* OwnerCreature;

	UBaseAnimInstance* OwnerAnimInstance;


};
