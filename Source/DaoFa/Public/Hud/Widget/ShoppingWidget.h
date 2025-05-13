// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShoppingWidget.generated.h"

class ABusinessman;
/**
 * 
 */
UCLASS()
class DAOFA_API UShoppingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shopping")
	ABusinessman* Businessman;

public:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Shopping")
	void BPPop(ABusinessman* InBusinessman);


	UFUNCTION(BlueprintCallable, Category = "Shopping")
	void Pop(ABusinessman* InBusinessman);

	UFUNCTION(BlueprintCallable, Category = "Shopping")
	void EndPop();



};
