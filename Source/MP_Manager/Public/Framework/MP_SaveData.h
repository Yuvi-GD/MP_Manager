// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/MP_PlayerProfile_STR.h"
#include "GameFramework/SaveGame.h"
#include "MP_SaveData.generated.h"

/**
 * 
 */
UCLASS()
class MP_MANAGER_API UMP_SaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FMP_PlayerProfile_STR PlayerProfile;

};
