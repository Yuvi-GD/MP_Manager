// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MP_PlayerController_Lobby.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Interfaces/MP_Interface_Character.h"
#include "Interfaces/MP_Interface_GameInstance.h"
#include "Base/MP_BlueprintFunctionLibrary.h"
#include "Multiplayer/MP_GameMode_Lobby.h"
#include "Multiplayer/MP_PlayerState_Lobby.h"
#include "Multiplayer/MP_GameState_Lobby.h"



AMP_PlayerController_Lobby::AMP_PlayerController_Lobby()
{
	// Set this player controller to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	GameStateLobby= nullptr;
}

void AMP_PlayerController_Lobby::BeginPlay()
{
	Super::BeginPlay();
	GameStateLobby = UMP_BlueprintFunctionLibrary::GetLobbyGameState(this);
	if (IsLocalController())
	{
		UMP_Lobby_UserWidget* LobbyWidget = UMP_BlueprintFunctionLibrary::GetLobbyWidget(this);
		if (GameStateLobby)
		{
			if (LobbyWidget)
			{
				LobbyWidget->UpdatePanel(GameStateLobby->PlayerProfiles);
			}
		}
	}
}

void AMP_PlayerController_Lobby::ServerInitializePlayer_Implementation(int32 PlayerLobbyID)
{
	AMP_PlayerState_Lobby* PlayerStateLobby = Cast<AMP_PlayerState_Lobby>(PlayerState);
	if (PlayerStateLobby)
	{
		PlayerStateLobby->PlayerIndexOnLobby = PlayerLobbyID;
	}
	AMP_GameMode_Lobby* GameModeLobby = Cast<AMP_GameMode_Lobby>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeLobby) 
	{
		GameModeLobby->ServerUpdatePlayerCharacter();
		UE_LOG(LogTemp, Warning, TEXT("ServerPlayerCharacter Will Update. PlayerLobbyID: %d"), PlayerLobbyID);
	}
}

void AMP_PlayerController_Lobby::ClientInitializePlayer_Implementation(int32 PlayerLobbyID)
{
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle, [this, PlayerLobbyID, World]()
	{
		if (!World) return;
		ServerInitializePlayer(PlayerLobbyID);
		AMP_PlayerState_Lobby* PlayerStateLobby = Cast<AMP_PlayerState_Lobby>(PlayerState);
		if (PlayerStateLobby) 
		{
			PlayerStateLobby->PlayerIndexOnLobby = PlayerLobbyID;
			UE_LOG(LogTemp, Warning, TEXT("PlayerState have Save PlayerLobby ID = %d"), PlayerLobbyID);

			UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GameInstance && GameInstance->Implements<UMP_Interface_GameInstance>())
			{
				FString ProfileName = IMP_Interface_GameInstance:: Execute_GetPlayerData(GameInstance);
				PlayerStateLobby->PlayerAddPsProfile(ProfileName);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GameInstance is NULL or does not implement interface!"));
			}

			UMP_Lobby_UserWidget* LobbyWidget = UMP_BlueprintFunctionLibrary::GetLobbyWidget(this);
			if (GameStateLobby) 
			{
				if (LobbyWidget) 
				{
					LobbyWidget->UpdateLevelSelection(GameStateLobby->LevelNumber);
				}
			}
		}
	}, 0.2f, false);
}

void AMP_PlayerController_Lobby::ClientDeinitializePlayer_Implementation()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		PlayerCharacter->Destroy();
	}
}

void AMP_PlayerController_Lobby::ClientUpdateCharacter_Implementation()
{
	ACharacter* PlayerCharacter =UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	// Call Character Class Function
	if (PlayerCharacter && PlayerCharacter->Implements<UMP_Interface_Character>())
	{
		IMP_Interface_Character::Execute_UpdateCharacter(PlayerCharacter, 3);
	}
}

void AMP_PlayerController_Lobby::ClientLeaveSession()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance && GameInstance->Implements<UMP_Interface_GameInstance>())
	{
		IMP_Interface_GameInstance::Execute_RemakeSession(GameInstance);
	}
}

void AMP_PlayerController_Lobby::SendChatMessage_Implementation(const FString& Message)
{
	if (GameStateLobby)
	{
		AMP_PlayerState_Lobby* PlayerStateLobby = Cast<AMP_PlayerState_Lobby>(PlayerState);
		if (PlayerStateLobby)
		{
			FString Sender = PlayerStateLobby->PlayerProfile;
			GameStateLobby->ServerSendChatMessage(Sender, Message);
		}
	}
}

void AMP_PlayerController_Lobby::SendTypingStatus_Implementation(const bool bIsTyping)
{
	if (GameStateLobby)
	{
		AMP_PlayerState_Lobby* PlayerStateLobby = Cast<AMP_PlayerState_Lobby>(PlayerState);
		if (PlayerStateLobby)
		{
			FString Sender = PlayerStateLobby->PlayerProfile;
			GameStateLobby->ServerSendTypingStatus(Sender, bIsTyping);
		}
	}
}