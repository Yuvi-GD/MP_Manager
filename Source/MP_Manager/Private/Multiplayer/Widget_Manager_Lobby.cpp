// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/Widget_Manager_Lobby.h"
#include "GameFramework/PlayerController.h"
#include "Base/MP_BlueprintFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"


AWidget_Manager_Lobby::AWidget_Manager_Lobby()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    LobbyWidget = nullptr;
    LobbyWidgetClass = nullptr;

	// Create the camera component and attach it to the root
	LobbyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LobbyCamera"));
	LobbyCamera->SetupAttachment(RootComponent);

	// Set the camera's location, rotation, and scale
	LobbyCamera->SetRelativeLocation(FVector(200.0f, 50.0f, 100.0f));
	LobbyCamera->SetRelativeRotation(FRotator(0.0f, 180.0f, -0.0f));
	LobbyCamera->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}

// Called when the game starts or when spawned
void AWidget_Manager_Lobby::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* LocalPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (LocalPlayerController && LobbyWidgetClass)
	{
		ShowLobbyUI();
		LocalPlayerController->SetViewTargetWithBlend(this, 0.5f); // Adjust blend time as needed
	}
}

void AWidget_Manager_Lobby::MulticastSetPlayer_Implementation(const FString& PlayerName, const int32 PlayerIndex)
{
	if (LobbyWidget)
	{

		LobbyWidget->UpdateOnePanel(PlayerName, PlayerIndex);
	}
}

void AWidget_Manager_Lobby::MulticastUpdatePlayerList_Implementation(const TArray<FString>& PlayerData)
{
	if (LobbyWidget)
	{

		LobbyWidget->UpdatePanel(PlayerData);
	}
}

void AWidget_Manager_Lobby::MulticastUpdateLevel_Implementation(const int32 LevelNum)
{
	if (LobbyWidget)
	{
		LobbyWidget->UpdateLevelSelection(LevelNum);
	}
}

void AWidget_Manager_Lobby::MultiCastSendChatMessage_Implementation(const FString& SenderName, const FString& Message)
{
	if (LobbyWidget)
	{
		AMP_PlayerState_Lobby* PlayerState = UMP_BlueprintFunctionLibrary::GetLobbyPlayerState(this);
		FString PlayerName = PlayerState->PlayerProfile;
		if (PlayerName != SenderName)
		{
			LobbyWidget->ReciveChatMessage(SenderName, Message);
			UE_LOG(LogTemp, Warning, TEXT("Message Broadcast to WidgetManager = %s"), *Message);
		}
	}
}

void AWidget_Manager_Lobby::MultiCastSendTypingStatus_Implementation(const FString& SenderName, const bool bIsTyping)
{
	if (LobbyWidget)
	{
		AMP_PlayerState_Lobby* PlayerState = UMP_BlueprintFunctionLibrary::GetLobbyPlayerState(this);
		FString PlayerName = PlayerState->PlayerProfile;
		if (PlayerName != SenderName)
		{
			LobbyWidget->ReciveTypingStatus(SenderName, bIsTyping);
		}
	}
}

void AWidget_Manager_Lobby::ShowLobbyUI()
{
	if (LobbyWidgetClass)
	{
		if (!LobbyWidget) // Ensure LobbyWidgetClass is valid
		{
			LobbyWidget = CreateWidget<UMP_Lobby_UserWidget>(GetWorld(), LobbyWidgetClass);
			if (LobbyWidget)
			{
				LobbyWidget->AddToViewport();
			}
		}
		else if (LobbyWidget)
		{
			if (LobbyWidget->IsInViewport())
			{
				LobbyWidget->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				LobbyWidget->AddToViewport();
			}
		}
	}
}

