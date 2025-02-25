// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MP_GameState_Lobby.h"
#include <Net/UnrealNetwork.h>
#include "Kismet/GameplayStatics.h"
#include "Multiplayer/MP_PlayerState_Lobby.h"

void AMP_GameState_Lobby::BeginPlay()
{
    Super::BeginPlay();
    WidgetManager = Cast<AWidget_Manager_Lobby>(UGameplayStatics::GetActorOfClass(GetWorld(), AWidget_Manager_Lobby::StaticClass()));
    if (WidgetManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget Manager Exist in GameState"));

    }
}

void AMP_GameState_Lobby::ServerSavePlayerData_Implementation(const FString& PlayerName, const int32 Index)
{
    UE_LOG(LogTemp, Warning, TEXT("GameState Also Save to PlayerState %s at index %d"), *PlayerName, Index);
    if (PlayerProfiles.IsValidIndex(Index)) 
    {
        
        PlayerProfiles[Index] = PlayerName;

        WidgetManager->MulticastSetPlayer(PlayerName, Index);
    }
}

void AMP_GameState_Lobby::ServerAddPlayerData_Implementation(const FString& PlayerName)
{
    PlayerProfiles.Add(PlayerName);

    WidgetManager->MulticastSetPlayer(PlayerName, PlayerProfiles.Num()-1);

    UE_LOG(LogTemp, Warning, TEXT("PlayerProfile Add to GameState AS well ------- %s"), *PlayerName);
}

void AMP_GameState_Lobby::ServerUpdateLevel_Implementation(const int32 LevelNum)
{
    LevelNumber = LevelNum;
    WidgetManager->MulticastUpdateLevel(LevelNumber);
}

void AMP_GameState_Lobby::ServerUpdatePlayerData_Implementation()
{
    PlayerProfiles.Empty();
    for(APlayerState* PlayerState : PlayerArray) 
    {
        AMP_PlayerState_Lobby* LobbyPlayerState = Cast<AMP_PlayerState_Lobby>(PlayerState);
        if (LobbyPlayerState) 
        {
            PlayerProfiles.Add(LobbyPlayerState->PlayerProfile);
            LobbyPlayerState->PlayerIndexOnLobby = PlayerProfiles.Num() - 1;
            UE_LOG(LogTemp, Warning, TEXT("PlayerProfile ID to GameState AS well ------- %d"), LobbyPlayerState->PlayerIndexOnLobby);
        }
    }

    WidgetManager->MulticastUpdatePlayerList(PlayerProfiles);
}

void AMP_GameState_Lobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Add the properties to be replicated
    DOREPLIFETIME(AMP_GameState_Lobby, ChatMessages);
    DOREPLIFETIME(AMP_GameState_Lobby, PlayerProfiles);
    DOREPLIFETIME(AMP_GameState_Lobby, TotalPlayers);
    DOREPLIFETIME(AMP_GameState_Lobby, LevelNumber);
}

void AMP_GameState_Lobby::ServerSendChatMessage_Implementation(const FString& SenderName, const FString& Message)
{
    FMP_Chat_STR NewMessage;
    NewMessage.SenderName = SenderName;
    NewMessage.Message = Message;
    ChatMessages.Add(NewMessage);

    WidgetManager->MultiCastSendChatMessage(SenderName,Message);
}

void AMP_GameState_Lobby::ServerSendTypingStatus_Implementation(const FString& SenderName, const bool bIsTyping)
{
    WidgetManager->MultiCastSendTypingStatus(SenderName, bIsTyping);
}
