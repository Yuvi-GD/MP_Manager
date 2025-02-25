// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MP_PlayerController_Lobby.h"
#include "MP_GameMode_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MP_MANAGER_API AMP_GameMode_Lobby : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMP_GameMode_Lobby();

protected:
	virtual void PostLogin(APlayerController* NewPlayer)override;
	
	virtual void Logout(AController* Exiting) override;

public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "MP Manager|Game Mode")
	void ServerShutdownSession();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP Manager|Game Mode")
	void ServerKickPlayer(int32 PlayerIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP Manager|Game Mode")
	void ServerUpdatePlayerCharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category = "MP Manager")
	TArray<TObjectPtr<AMP_PlayerController_Lobby>> AllMenuControllers;


	FTimerHandle TimerHandle;
};
