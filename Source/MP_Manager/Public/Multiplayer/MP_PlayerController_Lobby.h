// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Multiplayer/MP_GameState_Lobby.h"
#include "MP_PlayerController_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MP_MANAGER_API AMP_PlayerController_Lobby : public APlayerController
{
	GENERATED_BODY()

public:
    AMP_PlayerController_Lobby();

    // Declare the Widget Manager
    UPROPERTY(BlueprintReadWrite, Category = "GS Profile")
    TObjectPtr<AMP_GameState_Lobby> GameStateLobby;


protected:

    virtual void BeginPlay() override;
  
public:

    UFUNCTION(Client, Reliable, BlueprintCallable, Category = "MP Manager")
    void ClientInitializePlayer(int32 PlayerLobbyID);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager")
    void ServerInitializePlayer(int32 PlayerLobbyID);

    UFUNCTION(Client, Reliable, BlueprintCallable, Category = "MP Manager")
    void ClientDeinitializePlayer();

    UFUNCTION(BlueprintCallable, Category = "MP Manager")
    void ClientLeaveSession();
    
    UFUNCTION(Client, Reliable, BlueprintCallable, Category = "MP Manager")
    void ClientUpdateCharacter();

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager")
    void SendChatMessage( const FString& Message);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager")
    void SendTypingStatus(const bool bIsTyping);

    FTimerHandle TimerHandle;
};
