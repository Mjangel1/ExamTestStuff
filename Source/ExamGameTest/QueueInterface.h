// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QueueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQueueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EXAMGAMETEST_API IQueueInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Queue")
	void Enqueue(APawn* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Queue")
	APawn* Dequeue();
};
