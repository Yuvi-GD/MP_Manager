// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MP_Logic.h"
#include "Framework/MP_SaveData.h"
#include "Kismet/GameplayStatics.h"

void UMP_Logic::SaveProfile(FMP_PlayerProfile_STR MP_Profile)
{
    UMP_SaveData* SaveData = Cast<UMP_SaveData>(UGameplayStatics::CreateSaveGameObject(UMP_SaveData::StaticClass()));
    if (SaveData)
    {
        SaveData->PlayerProfile = MP_Profile;
        PlayerProfile = MP_Profile;
        UGameplayStatics::SaveGameToSlot(SaveData, "SaveProfile", 0);
        OnProfileUpdate.Broadcast(MP_Profile.PlayerName); // Fire event
    }
}

FMP_PlayerProfile_STR UMP_Logic::LoadProfile()
{
    if (UGameplayStatics::DoesSaveGameExist("SaveProfile", 0))
    {
        UMP_SaveData* SaveData = Cast<UMP_SaveData>(UGameplayStatics::LoadGameFromSlot("SaveProfile", 0));
        if (SaveData)
        {
            PlayerProfile = SaveData->PlayerProfile;
            return PlayerProfile;
        }
    }
    return PlayerProfile;
}
