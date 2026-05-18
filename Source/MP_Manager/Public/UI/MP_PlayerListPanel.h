// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MP_Btn.h"
#include "Components/VerticalBox.h"
#include "MP_PlayerListPanel.generated.h"

class UTextBlock;
class MP_Button;

/**
 * Panel for displaying the player list in the lobby.
 */
UCLASS(Blueprintable, meta = (DisplayName = "MP_PlayerlistPanel"))
class MP_MANAGER_API UMP_PlayerListPanel : public UVerticalBox
{
	GENERATED_BODY()

public:
	// Function that will be bound to the button click
	UMP_PlayerListPanel();


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	// Updates the player list and adjusts the panel based on the limit and player names.
	UFUNCTION(BlueprintCallable, Category = "MP Manager|Mp Panel")
	void UpdatePanel(const TArray<FString>& PlayerNames, const int32& PlayerLimit);

	// Creates a new player entry (button with name) and adds it to the panel.
	UFUNCTION(BlueprintCallable, Category = "MP Manager|Mp Panel")
	void SetPlayerEntry(const FString& PlayerName, const int32& Index);

	// Refreshes the player list by adjusting the panel according to the current player count.
	UFUNCTION(BlueprintCallable, Category = "MP Manager|Mp Panel")
	void RefreshPanel(int32 Count);

	// Helper function to create player entry (button) dynamically.
	//UFUNCTION()
	void CreatePlayerEntry_Internal(const FString& PlayerName, const int32& Index);

protected:

	// Color settings for player entries.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|Mp Panel|Appearance")
	TArray<FLinearColor> PanelColor;

	// Text color for player names.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|Mp Panel|Appearance")
	FLinearColor TextColor;

	// Limit of players for the lobby.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|Mp Panel|Settings")
	int32 PanelLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP Manager|Mp Panel|Settings")
	int32 ButtonID;
	UPROPERTY(BlueprintReadOnly,Category = "MP Manager|Mp Panel|Settings")
	bool bIsColor;


};