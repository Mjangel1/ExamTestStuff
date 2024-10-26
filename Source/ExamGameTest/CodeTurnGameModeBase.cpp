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

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	SpawnPlayers();
	
	
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

	/*TArray<AActor*> PlayersFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, PlayersFound);
	Player1 = Cast<APlayerPawn>(PlayersFound[0]);
	Player2 = Cast<APlayerPawn>(PlayersFound[1]);*/
	Enqueue_Implementation(Player1);
	
	Enqueue_Implementation(Player2);
	

}

void ACodeTurnGameModeBase::SwitchPlayers_Implementation()
{

	//reference to return Pawn that the function returns

	if (PlayerArray.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Empty"));
	}

	if (CurrentPlayer == PlayerArray[0])
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("equal"));
		CurrentPlayer->UnPossessed();
		Enqueue_Implementation(Dequeue_Implementation());


		if (!PlayerArray.IsEmpty())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Assigned"));
			
			CurrentPlayer = PlayerArray[0];

			if (CurrentPlayer && PlayerController)
			{
				
				PlayerController->Possess(CurrentPlayer);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Change to new player"));
			}
		}

		

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("not equal"));
		CurrentPlayer->UnPossessed();
		Enqueue_Implementation(Dequeue_Implementation());


		if (!PlayerArray.IsEmpty())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Assigned"));

			CurrentPlayer = PlayerArray[0];

			if (CurrentPlayer && PlayerController)
			{

				PlayerController->Possess(CurrentPlayer);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Change to player1"));
			}
		}
		
	}
}

