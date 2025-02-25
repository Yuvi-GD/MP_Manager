// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MP_PlayerProfile_STR.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct MP_MANAGER_API FMP_PlayerProfile_STR
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Profile")
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Profile")
	int32 PlayerID;

	FMP_PlayerProfile_STR();
	~FMP_PlayerProfile_STR();
};
