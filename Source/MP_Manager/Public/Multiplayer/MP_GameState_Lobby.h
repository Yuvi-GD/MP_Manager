// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Base/MP_Chat_STR.h"
#include "Multiplayer/Widget_Manager_Lobby.h"
#include "MP_GameState_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MP_MANAGER_API AMP_GameState_Lobby : public AGameState
{
	GENERATED_BODY()
public:

    // Declare the Widget Manager
    UPROPERTY(BlueprintReadWrite, Category = "GS Profile")
    TObjectPtr<AWidget_Manager_Lobby> WidgetManager;

    // Override BeginPlay
    virtual void BeginPlay() override;

 
    // String arrays
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "GS Profile")
    TArray<FMP_Chat_STR> ChatMessages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "GS Profile")
    TArray<FString> PlayerProfiles;

    // Integer properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "GS Profile")
    int32 TotalPlayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "GS Profile")
    int32 LevelNumber;

    // Function to set up replication
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category ="MP Manager|GameState")
	void ServerSavePlayerData(const FString& PlayerName,const int32 Index);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager|GameState")
	void ServerAddPlayerData(const FString& PlayerName);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager|GameState")
    void ServerUpdateLevel(const int32 LevelNum);

    // Function to update player profiles and indexes
    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager|GameState")
    void ServerUpdatePlayerData();

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager|GameState")
    void ServerSendChatMessage(const FString& SenderName, const FString& Message);
    
    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MP Manager|GameState")
    void ServerSendTypingStatus(const FString& SenderName, const bool bIsTyping);
};
