// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MP_Lobby_UserWidget.generated.h"


/**
 * 
 */
UCLASS()
class MP_MANAGER_API UMP_Lobby_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void MP_Lobby_UserWidget();

	// Function to update the UI
	UFUNCTION(BlueprintNativeEvent, Category = "MP Manager|UI")
	void UpdateOnePanel(const FString& PlayerName, int32 PlayerIndex);

	// Helper function to initialize the vertical box
	UFUNCTION(BlueprintNativeEvent, Category = "MP Manager|UI")
	void UpdatePanel(const TArray<FString>& PlayerData);

	UFUNCTION(BlueprintNativeEvent, Category = "MP Manager|UI")
	void UpdateLevelSelection(int32 LevelNumber);

	UFUNCTION(BlueprintNativeEvent, Category = "MP Manager|UI")
	void ReciveChatMessage(const FString& SenderName, const FString& Message);
	
	UFUNCTION(BlueprintNativeEvent, Category = "MP Manager|UI")
	void ReciveTypingStatus(const FString& SenderName, const bool bIsTyping);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|UI")
	int32 PlayerLimit;

};
