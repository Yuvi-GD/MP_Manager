// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "UI/MP_Lobby_UserWidget.h"
#include "Widget_Manager_Lobby.generated.h"

UCLASS()
class MP_MANAGER_API AWidget_Manager_Lobby : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWidget_Manager_Lobby();

	// Multicast RPCs
	UFUNCTION(NetMulticast, Reliable, Category = "MP Manager|WidgetManager")
	void MulticastSetPlayer(const FString& PlayerName, const int32 PlayerIndex);

	UFUNCTION(NetMulticast, Reliable, Category = "MP Manager|WidgetManager")
	void MulticastUpdatePlayerList(const TArray<FString>& PlayerData);

	UFUNCTION(NetMulticast, Reliable, Category = "MP Manager|WidgetManager")
	void MulticastUpdateLevel(const int32 LevelNum);

	UFUNCTION(NetMulticast, Reliable, Category = "MP Manager|WidgetManager")
	void MultiCastSendChatMessage(const FString& SenderName, const FString& Message);

	UFUNCTION(NetMulticast, Reliable, Category = "MP Manager|WidgetManager")
	void MultiCastSendTypingStatus(const FString& SenderName, const bool bIsTyping);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "MP Manager|WidgetManager")
	void ShowLobbyUI();

public:
	// Camera component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> LobbyCamera;

	UPROPERTY(EditAnywhere, Category = "MP Manager")
	TObjectPtr<UMP_Lobby_UserWidget> LobbyWidget;


	UPROPERTY(EditAnywhere, Category = "MP Manager")
	TSubclassOf<class UMP_Lobby_UserWidget> LobbyWidgetClass;

private:

};