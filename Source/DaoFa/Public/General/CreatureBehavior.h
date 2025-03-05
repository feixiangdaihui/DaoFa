#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Interface/InputUpdateInterface.h"
#include "Hud/Interface/InitSumEquipmentBarInterface.h"
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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAOFA_API UCreatureBehavior : public UActorComponent, public IInputUpdateInterface, public IInitSumEquipmentBarInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCreatureBehavior();

	friend class UInputOperationComponent;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void InitSumEquipmentBar(USumEquipmentBarWidget* SumEquipmentBarWidget) override;


	

	void SetMoveForbid(bool NewValue);
private:
	bool IsMoveForbid = false;

	virtual void UpdateInput(InputAnimation Input) override;

	virtual bool CheckInput(InputAnimation Input) override;

	TArray<TScriptInterface<IInputUpdateInterface>> InputUpdateInterfaces;

	ACreature* OwnerCreature;

	UBaseAnimInstance* OwnerAnimInstance;

	USumEquipmentBarWidget* OwnerSumEquipmentBarWidget;



	void Jump();


	void Walk(const FInputActionValue& Value);

	void BaseWalk(const FInputActionValue& Value);

	void StopWalk();

	void Run();

	void StopRun();
	void ChangeChosenEquipmentBarToSmall();

	void ChangeChosenEquipmentBarToBig();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float DodgeUnbeatableTime = 0.5f;
	void Dodge();


	//1表示开始释放技能，0表示结束释放技能
	void Spell(int Num, bool Begin);

	UFUNCTION()
	void OnBlueEmpty();

	APackObject* CurrentPackObject = nullptr;


	bool IsRunning = false;





};
