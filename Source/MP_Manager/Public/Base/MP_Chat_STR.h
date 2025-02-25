// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MP_Chat_STR.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct MP_MANAGER_API FMP_Chat_STR
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat")
	FString SenderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chat")
	FString Message;

	FMP_Chat_STR();
	~FMP_Chat_STR();
};
