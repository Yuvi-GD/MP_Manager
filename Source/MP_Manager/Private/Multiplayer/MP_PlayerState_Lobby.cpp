// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MP_PlayerState_Lobby.h"
#include "Kismet/GameplayStatics.h"
#include <Net/UnrealNetwork.h>

AMP_PlayerState_Lobby::AMP_PlayerState_Lobby()
{
	PlayerProfile = "Bro";
	PlayerIndexOnLobby = -1;
	LobbyGameState = nullptr;
}

void AMP_PlayerState_Lobby::BeginPlay()
{
	Super::BeginPlay();

	if (!LobbyGameState)
	{
		LobbyGameState = Cast<AMP_GameState_Lobby>(UGameplayStatics::GetGameState(GetWorld()));
	}
}

void AMP_PlayerState_Lobby::PlayerSaveProfile_Implementation(const FString& PlayerName, const bool UpdateUI)
{
	PlayerProfile = PlayerName;

	if (UpdateUI)
	{
		if (LobbyGameState)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerProfile Save to PlayerState %s"), *PlayerProfile);
			LobbyGameState->ServerSavePlayerData(PlayerProfile, PlayerIndexOnLobby);
		}		
	}
}

void AMP_PlayerState_Lobby::PlayerAddPsProfile_Implementation(const FString& PlayerName)
{
	PlayerProfile = PlayerName;
	if (LobbyGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerProfile Add to PlayerState %s"), *PlayerProfile);
		LobbyGameState->ServerAddPlayerData(PlayerProfile);
	}
}

void AMP_PlayerState_Lobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Add the properties to be replicated
	DOREPLIFETIME(AMP_PlayerState_Lobby, PlayerProfile);
	DOREPLIFETIME(AMP_PlayerState_Lobby, PlayerIndexOnLobby);
}


