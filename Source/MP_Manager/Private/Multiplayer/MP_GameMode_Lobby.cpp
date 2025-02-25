// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MP_GameMode_Lobby.h"
#include "Multiplayer/MP_GameState_Lobby.h"
#include "Multiplayer/MP_PlayerState_Lobby.h"
#include "Kismet/GameplayStatics.h" 
#include "Engine/GameInstance.h"
#include "TimerManager.h"
#include "CoreMinimal.h"
#include "Interfaces/MP_Interface_GameInstance.h"


AMP_GameMode_Lobby::AMP_GameMode_Lobby()
{
	//AllMenuControllers = nullptr;
	
	// Set the custom PlayerController class
	PlayerControllerClass = AMP_PlayerController_Lobby::StaticClass();

	// Set the custom PlayerState class
	PlayerStateClass = AMP_PlayerState_Lobby::StaticClass();

	// Set the custom GameState class
	GameStateClass = AMP_GameState_Lobby::StaticClass();
}


void AMP_GameMode_Lobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AMP_PlayerController_Lobby* LobbyPlayerController = Cast<AMP_PlayerController_Lobby>(NewPlayer);
	if (LobbyPlayerController)
	{
		UWorld* World = GetWorld();
		World->GetTimerManager().SetTimer(TimerHandle, [this, LobbyPlayerController, World]()
			{
				AllMenuControllers.Add(LobbyPlayerController);
				LobbyPlayerController->ClientInitializePlayer(AllMenuControllers.Num()-1);
				//Debug
				UE_LOG(LogTemp, Warning, TEXT("%d Player has joined in Lobby"), AllMenuControllers.Num() - 1);
			}, 0.05f, false);
	}
}

void AMP_GameMode_Lobby::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	AMP_PlayerController_Lobby* ExitingPlayer = Cast<AMP_PlayerController_Lobby>(Exiting);
	if (ExitingPlayer)
	{
		ExitingPlayer->ClientDeinitializePlayer();
		AllMenuControllers.Remove(ExitingPlayer);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, ExitingPlayer]()
		{
			AMP_GameState_Lobby* GameStateLobby = Cast<AMP_GameState_Lobby>(GameState);
			GameStateLobby->ServerUpdatePlayerData();
		}, 0.05f, false);
	}
}

void AMP_GameMode_Lobby::ServerShutdownSession_Implementation()
{
	UGameInstance* MPGameInstance = Cast<UGameInstance>(GetGameInstance());

	for (AMP_PlayerController_Lobby* Player : AllMenuControllers)
	{
		if (Player != UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			Player->ClientLeaveSession();
		}
	}
	if (MPGameInstance && MPGameInstance->Implements<UMP_Interface_GameInstance>())
	{
		IMP_Interface_GameInstance::Execute_RemakeSession(MPGameInstance);
	}
}

void AMP_GameMode_Lobby::ServerKickPlayer_Implementation(int32 PlayerIndex)
{
	if (AllMenuControllers.IsValidIndex(PlayerIndex))
	{
		AMP_PlayerController_Lobby* PlayerToKick = AllMenuControllers[PlayerIndex];
		if (PlayerToKick)
		{
			PlayerToKick->ClientLeaveSession();
		}
	}
}

void AMP_GameMode_Lobby::ServerUpdatePlayerCharacter_Implementation()
{
	for (AMP_PlayerController_Lobby* Player : AllMenuControllers)
	{
		if (Player)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayerCharacter Is Update"));
			}
			// Notify client to update character
			Player->ClientUpdateCharacter();
		}
	}

}