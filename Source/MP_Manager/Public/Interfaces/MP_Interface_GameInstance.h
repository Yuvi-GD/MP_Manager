// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MP_Interface_GameInstance.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMP_Interface_GameInstance : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MP_MANAGER_API IMP_Interface_GameInstance
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetPlayerProfile(FString& PlayerProfile) = 0;


	// BlueprintNativeEvent, BlueprintCallable type of interface trigger by Plugin PlayerController
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP_Session")
	void CreateSession();

	 //BlueprintNativeEvent, BlueprintCallable type of interface trigger by Plugin PlayerController
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP_Session")
	void UpdateSession();

	 //BlueprintNativeEvent, BlueprintCallable type of interface trigger by Plugin PlayerController
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP_Session")
	void LeaveSession();

	//BlueprintNativeEvent, BlueprintCallable type of interface trigger by Plugin PlayerController
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP_Session")
	void RemakeSession();

	//BlueprintNativeEvent, BlueprintCallable type of interface trigger by Plugin PlayerController
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MP_Session")
	FString GetPlayerData();
};
