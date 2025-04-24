#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractComponent.generated.h"


DECLARE_DELEGATE(FOnInteractTriggered);

class USphereComponent;
class UInteractManage;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAOFA_API UInteractComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	FText InteractText;


	//胶囊碰撞体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	TObjectPtr<USphereComponent> InteractSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
	TObjectPtr<UInteractManage> InteractManage;
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	// Called every frame

	USphereComponent* GetInteractSphereComponent() const { return InteractSphereComponent; }

	FOnInteractTriggered OnInteractTriggered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bIsInteractable = true;


		
};


