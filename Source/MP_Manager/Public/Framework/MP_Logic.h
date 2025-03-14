// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/MP_PlayerProfile_STR.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MP_Logic.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileUpdate, const FString&, UpdatedProfile);

/**
 * 
 */
UCLASS()
class MP_MANAGER_API UMP_Logic : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

    // Boolean to indicate if it's a LAN match
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|MP_Logic")
    bool IsLanMatch;

    // String to store the Lobby ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|MP_Logic")
    FString LobbyID;

    // Integer to store the number of public connections
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|MP_Logic")
    int32 NumberOfPublicConnections;

    // Player Profiles Strcture Comes with MP_Manager Plugins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|MP_Logic")
    FMP_PlayerProfile_STR PlayerProfile;

    // Function to save the player profile (Impure)
    UFUNCTION(BlueprintCallable, Category = "MP Manager|MP_Logic")
    void SaveProfile(FMP_PlayerProfile_STR MP_Profile);

    // Function to load the player profile (Pure)
    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "MP Manager|MP_Logic")
    FMP_PlayerProfile_STR LoadProfile();

    // Event dispatcher for profile update
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "MP Manager|MP_Logic")
    FOnProfileUpdate OnProfileUpdate;
};
