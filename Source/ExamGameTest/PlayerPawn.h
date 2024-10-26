// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class EXAMGAMETEST_API APlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category= "Camera")
	UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	class UInputMappingContext* Imc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* Wasd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* LookAction;


	UFUNCTION()
	void PlayerMovement(const FInputActionValue& Value);

	UFUNCTION()
	void CameraLook(const FInputActionValue& Value);

};
