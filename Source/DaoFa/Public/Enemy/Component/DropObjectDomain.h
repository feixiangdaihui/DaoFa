// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropObjectDomain.generated.h"
class USphereComponent;
class APackObject;
UCLASS()
class DAOFA_API ADropObjectDomain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropObjectDomain();





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//圆形碰撞体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	float Radius = 100.0f;

	//掉落物品
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	TArray<APackObject*> DropObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	TArray<TSubclassOf<APackObject>> DropObjectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	float DropExp = 10.0f;

public:	

	void SetDropObjects(TArray<APackObject*> InDropObjects) { DropObjects = InDropObjects; }

	void AddDropObject(APackObject* InDropObject) { DropObjects.Add(InDropObject); }

	void ClearDropObjects() { DropObjects.Empty(); }
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
