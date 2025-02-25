// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MP_Interface_Character.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMP_Interface_Character : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MP_MANAGER_API IMP_Interface_Character
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// BlueprintNativeEvent, BlueprintCallable type of interface trigger by Plugin PlayerController
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP_Character")
	void UpdateCharacter(int32 CharacterNum);
};
