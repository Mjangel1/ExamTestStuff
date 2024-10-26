// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

APlayerPawn::APlayerPawn()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->bUsePawnControlRotation = true;
	
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Imc, 0);
		}
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(Wasd, ETriggerEvent::Triggered, this ,&APlayerPawn::PlayerMovement);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawn::CameraLook);

}

void APlayerPawn::PlayerMovement(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator YawPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);

		const FVector ForwardBackwards = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::Y);

		const FVector RightDirection = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::X);


		AddMovementInput(ForwardBackwards, MoveInput.X);
		AddMovementInput(RightDirection, MoveInput.Y);
	}

}

void APlayerPawn::CameraLook(const FInputActionValue& Value)
{

	const FVector2D LookInput = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookInput.X);

		AddControllerPitchInput(LookInput.Y);

	}

}
