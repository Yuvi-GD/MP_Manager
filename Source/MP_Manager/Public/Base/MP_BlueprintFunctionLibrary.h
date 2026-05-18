// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Multiplayer/Widget_Manager_Lobby.h"
#include "UI/MP_Lobby_UserWidget.h"
#include "Multiplayer/MP_GameState_Lobby.h"
#include "Multiplayer/MP_PlayerState_Lobby.h"
#include "Multiplayer/MP_PlayerController_Lobby.h"
#include "Multiplayer/MP_GameMode_Lobby.h"
#include "MP_BlueprintFunctionLibrary.generated.h"


// Forward declaration of AMP_PlayerController_Lobby
class AMP_PlayerController_Lobby;
/**
 * 
 */
UCLASS()
class MP_MANAGER_API UMP_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static AWidget_Manager_Lobby* GetWidgetManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static UMP_Lobby_UserWidget* GetLobbyWidget(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static AMP_GameState_Lobby* GetLobbyGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static AMP_GameMode_Lobby* GetLobbyGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static AMP_PlayerState_Lobby* GetLobbyPlayerState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static AMP_PlayerController_Lobby* GetLobbyPlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static bool CheckUniqueNetId(const UObject* WorldContextObject , FUniqueNetIdRepl NetIdA, FUniqueNetIdRepl NetIdB);

	UFUNCTION(BlueprintPure, Category = "MP_Manager|FLibrary", meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static APlayerState* FindPlayerStateByUniqueNetId(UObject* WorldContextObject, const FUniqueNetIdRepl& TargetUniqueNetId);
};