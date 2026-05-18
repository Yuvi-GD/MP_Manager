// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MP_BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AWidget_Manager_Lobby* UMP_BlueprintFunctionLibrary::GetWidgetManager(const UObject* WorldContextObject)
{
    if (!WorldContextObject) {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) {
        return nullptr;
    }

    return Cast<AWidget_Manager_Lobby>(UGameplayStatics::GetActorOfClass(World, AWidget_Manager_Lobby::StaticClass()));
}

UMP_Lobby_UserWidget* UMP_BlueprintFunctionLibrary::GetLobbyWidget(const UObject* WorldContextObject)
{
    AWidget_Manager_Lobby* WidgetManager = GetWidgetManager(WorldContextObject);
    if (!WidgetManager) {
        return nullptr;
    }

    return WidgetManager->LobbyWidget;  // Assuming LobbyWidget is public
}

AMP_GameState_Lobby* UMP_BlueprintFunctionLibrary::GetLobbyGameState(const UObject* WorldContextObject)
{
    if (!WorldContextObject) {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) {
        return nullptr;
    }

    return Cast<AMP_GameState_Lobby>(World->GetGameState<AGameState>());
}

AMP_GameMode_Lobby* UMP_BlueprintFunctionLibrary::GetLobbyGameMode(const UObject* WorldContextObject)
{
    if (!WorldContextObject) {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) {
        return nullptr;
    }
    return  Cast<AMP_GameMode_Lobby>(UGameplayStatics::GetGameMode(World));
}

AMP_PlayerState_Lobby* UMP_BlueprintFunctionLibrary::GetLobbyPlayerState(const UObject* WorldContextObject)
{
    if (!WorldContextObject) {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) {
        return nullptr;
    }
    
    AMP_PlayerController_Lobby* PlayerCtrlr = GetLobbyPlayerController(WorldContextObject);

    return Cast<AMP_PlayerState_Lobby>(PlayerCtrlr->PlayerState);
}

AMP_PlayerController_Lobby* UMP_BlueprintFunctionLibrary::GetLobbyPlayerController(const UObject* WorldContextObject)
{
    if (!WorldContextObject) {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) {
        return nullptr;
    }
    
    AMP_PlayerController_Lobby *PlayerPC = Cast<AMP_PlayerController_Lobby>(UGameplayStatics::GetPlayerController(World, 0));
    return PlayerPC;
}

bool UMP_BlueprintFunctionLibrary::CheckUniqueNetId(const UObject* WorldContextObject, FUniqueNetIdRepl NetIdA, FUniqueNetIdRepl NetIdB)
{
    if (!WorldContextObject) {
        return false;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) {
        return false;
    }

    return NetIdA == NetIdB;
}

APlayerState* UMP_BlueprintFunctionLibrary::FindPlayerStateByUniqueNetId(UObject* WorldContextObject, const FUniqueNetIdRepl& TargetUniqueNetId)
{
    if (!WorldContextObject || !TargetUniqueNetId.IsValid())
    {
        return nullptr;
    }

    UWorld* World = WorldContextObject->GetWorld();
    if (!World)
    {
        return nullptr;
    }

    // Loop through all Player Controllers in the world
    for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        if (!PlayerController)
        {
            continue;
        }

        APlayerState* PlayerState = PlayerController->PlayerState;
        if (!PlayerState)
        {
            continue;
        }

        // Get the Unique Net ID from the Player State
        const FUniqueNetIdRepl CurrentUniqueNetId = PlayerState->GetUniqueId();
        if (CurrentUniqueNetId == TargetUniqueNetId)
        {
            return PlayerState;
        }
    }

    // Return nullptr if no matching Player State is found
    return nullptr;
}

