// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTurnGameModeBase.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

ACodeTurnGameModeBase::ACodeTurnGameModeBase()
{
	PlayerClass = APlayerPawn::StaticClass();

	CurrentPlayer = nullptr;
	Player1 = nullptr;
	Player2 = nullptr;
}

void ACodeTurnGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	
	SpawnPlayers();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	CurrentPlayer = PlayerArray[0];
	if (PlayerController != nullptr)
	{
		CurrentPlayer->PossessedBy(PlayerController);
	}

}

void ACodeTurnGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACodeTurnGameModeBase::Enqueue_Implementation(APawn* Actor)
{

	PlayerArray.Emplace(Actor);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Player Enqueued"));

}

APawn* ACodeTurnGameModeBase::Dequeue_Implementation()
{
	
	APawn* DequeueActor = nullptr;

	if (!PlayerArray.IsEmpty())
	{
		DequeueActor = PlayerArray[0];
		PlayerArray.RemoveAt(0);

	}

	return DequeueActor;
}

void ACodeTurnGameModeBase::SpawnPlayers()
{

	FVector Player1Location = FVector(0, 0, 0);
	FVector Player2Location = FVector(0, 0, 100);
	FRotator Rotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	Player1 = GetWorld()->SpawnActor<APlayerPawn>(PlayerClass, Player1Location, Rotation, SpawnParameters);
	Player2 = GetWorld()->SpawnActor<APlayerPawn>(PlayerClass, Player2Location, Rotation, SpawnParameters);

	Enqueue_Implementation(Player1);
	
	Enqueue_Implementation(Player2);
	

}

void ACodeTurnGameModeBase::DoWork()
{
	PlayerController->Possess(CurrentPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Change to new player"));
}

void ACodeTurnGameModeBase::SwitchPlayers_Implementation()
{
	

	if (PlayerArray.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Empty"));

		return;
	}

	// calls dequeue first and get the pawn return, then call enqueue
	APawn* PlayerDequeued = Dequeue_Implementation();

	if (IsValid(CurrentPlayer))
	{
		CurrentPlayer->UnPossessed();
	}

	//Enqueue the Player that was removed from the que back into it
	Enqueue_Implementation(PlayerDequeued);
	


	if (!PlayerArray.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Assigned"));

		CurrentPlayer = PlayerArray[0];
		FString Name = CurrentPlayer->GetName();
			
		

		if (IsValid(CurrentPlayer) && IsValid(PlayerController))
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ACodeTurnGameModeBase::DoWork);

		}
	}
	

}

