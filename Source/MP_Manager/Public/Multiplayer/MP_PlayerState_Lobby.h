// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Multiplayer/MP_GameState_Lobby.h"
#include "MP_PlayerState_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MP_MANAGER_API AMP_PlayerState_Lobby : public APlayerState
{
	GENERATED_BODY()
	
public:

	AMP_PlayerState_Lobby();

	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PS Profile")
	FString PlayerProfile;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PS Profile")
	int32 PlayerIndexOnLobby;

	UFUNCTION(Server, reliable, BlueprintCallable, Category = "Ps Profile")
	void PlayerSaveProfile(const FString& PlayerName, const bool UpdateUI);

	UFUNCTION(Server, reliable, BlueprintCallable, Category = "Ps Profile")
	void PlayerAddPsProfile(const FString& PlayerName);


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	TObjectPtr<AMP_GameState_Lobby> LobbyGameState;


};
