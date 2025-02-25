// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MP_Lobby_UserWidget.h"



void UMP_Lobby_UserWidget::MP_Lobby_UserWidget()
{
    PlayerLimit = 2;
    TArray<FString>PlayerData = {"User 1","user 2"};
}

void UMP_Lobby_UserWidget::ReciveTypingStatus_Implementation(const FString& SenderName, const bool bIsTyping)
{
    UE_LOG(LogTemp, Error, TEXT("UpdateOnePanel C++ Has not  Written Please Override in you UI"));
    // Note: Blueprints will override this, if needed.
}

void UMP_Lobby_UserWidget::ReciveChatMessage_Implementation(const FString& SenderName, const FString& Message)
{
    UE_LOG(LogTemp, Error, TEXT("UpdateOnePanel C++ Has not  Written Please Override in you UI"));
    // Note: Blueprints will override this, if needed.
}
void UMP_Lobby_UserWidget::UpdateOnePanel_Implementation(const FString& PlayerName, int32 PlayerIndex)
{
    UE_LOG(LogTemp, Error, TEXT("UpdateOnePanel C++ Has not  Written Please Override in you UI"));
    // Note: Blueprints will override this, if needed.
}

void UMP_Lobby_UserWidget::UpdatePanel_Implementation(const TArray<FString>& PlayerData)
{
    UE_LOG(LogTemp, Error, TEXT("UpdatePanel C++ Has not  Written Please Override in you UI"));
    // Note: Blueprints will override this, if needed.
 
}

void UMP_Lobby_UserWidget::UpdateLevelSelection_Implementation(int32 LevelNumber)
{
    UE_LOG(LogTemp, Error, TEXT("UpdateLevelSelection C++ Has not  Written Please Override in you UI"));
    // Note: Blueprints will override this, if needed.
}

