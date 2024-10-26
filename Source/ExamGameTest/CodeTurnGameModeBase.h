// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "QueueInterface.h"
#include "GameFramework/GameModeBase.h"
#include "CodeTurnGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EXAMGAMETEST_API ACodeTurnGameModeBase : public AGameModeBase ,public IQueueInterface
{
	GENERATED_BODY()

public:
	ACodeTurnGameModeBase();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;


	//From QueueInterface
	virtual void Enqueue_Implementation(APawn* Actor) override;

	virtual APawn* Dequeue_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QueueArray")
	TArray<APawn*> PlayerArray;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "PlayerClass")
	TSubclassOf<APlayerPawn> PlayerClass;

	UPROPERTY()
	APawn* CurrentPlayer;


	UPROPERTY()
	APlayerPawn* Player1;

	UPROPERTY()
	APlayerPawn* Player2;

	UPROPERTY()
	APlayerController* PlayerController;

	UFUNCTION()
	void SpawnPlayers();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Switch Players")
	void SwitchPlayers();
};
