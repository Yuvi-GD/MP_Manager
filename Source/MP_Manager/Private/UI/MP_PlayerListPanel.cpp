// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MP_PlayerlistPanel.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/ButtonSlot.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Delegates/IDelegateInstance.h"

UMP_PlayerListPanel::UMP_PlayerListPanel()
{
	TArray<FString>PlayerData = { "User 1","user 2" };
	PanelColor = { FLinearColor(1.0f, 0.10f, 0.0f, 1.0f), FLinearColor::Green, FLinearColor(0.0f, 0.250f, 1.0f, 1.0f), FLinearColor::Yellow, FLinearColor(0.20f, 0.20f, 0.20f, 1.0f) };
	PanelLimit = -1;
	TextColor = FLinearColor::White;
	bIsColor = true;
}

void UMP_PlayerListPanel::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	RefreshPanel(PanelLimit);
}

void UMP_PlayerListPanel::UpdatePanel(const TArray<FString>& PlayerNames, const int32& PlayerLimit)
{
	if (PlayerLimit<PlayerNames.Num())
	{
		RefreshPanel(PanelLimit);
	}
	else 
	{
		int32 localint = -1;
		for (const FString& PlayerName : PlayerNames)
		{
			localint++;
			SetPlayerEntry(PlayerName, localint);
		}

		for (int32 i = PlayerNames.Num(); i < PanelLimit; i++)
		{
			bIsColor = false;
			SetPlayerEntry("Waiting for player ....", i);
		}
	}
	
}

void UMP_PlayerListPanel::SetPlayerEntry(const FString& PlayerName, const int32& Index)
{
	if (PanelLimit < Index)
	{
		RefreshPanel(PanelLimit);
	}

	UMP_Btn* NewButton = Cast<UMP_Btn>(this->GetChildAt(Index));
	if (NewButton) 
	{
		NewButton->SetButtonText(FText::FromString(PlayerName));
		int32 ColorIndex = FMath::Clamp(Index, 0, PanelColor.Num() - 1);
		if (bIsColor)
		{
			NewButton->SetBackgroundColor(PanelColor[ColorIndex]);
		}
		else
		{
			NewButton->SetBackgroundColor(PanelColor.Last());
			bIsColor = true;
		}
	}
}

void UMP_PlayerListPanel::RefreshPanel(int32 Count)
{
	// Ensure Count is more than Zero
	if (Count<0)
	{
		Count = 0;
	}
	if (Count != this->GetChildrenCount())
	{
		if (Count < this->GetChildrenCount())
		{
			int32 i = this->GetChildrenCount() - 1;
			for (i; i >= Count; i--)
			{
				this->RemoveChildAt(i);
			}
		}
		else
		{
			// Add Items
			int32 i = this->GetChildrenCount();
			for (i; i < Count; i++)
			{
				CreatePlayerEntry_Internal("Waiting for player ....", i);
			}
		}
	}
}


void UMP_PlayerListPanel::CreatePlayerEntry_Internal(const FString& PlayerName, const int32& Index)
{

	// Create a new button for the player entry
	UMP_Btn* NewButton = NewObject<UMP_Btn>(this);
	if (NewButton)
	{
		//Button Property set
		// GetStyle() was introduced in UE 5.2 to replace direct WidgetStyle access
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 2)
		FButtonStyle ButtonStyle = GetStyle();
#else
		FButtonStyle ButtonStyle;
		if (UMP_Btn* DefaultBtn = Cast<UMP_Btn>(UMP_Btn::StaticClass()->GetDefaultObject()))
		{
			ButtonStyle = DefaultBtn->WidgetStyle;
		}
		else
		{
			ButtonStyle = FButtonStyle();
		}
#endif
		FSlateBrush Brush;
		Brush.DrawAs = ESlateBrushDrawType::Box;
		ButtonStyle.SetNormal(Brush);
		ButtonStyle.SetHovered(Brush);
		ButtonStyle.SetPressed(Brush);
		NewButton->SetStyle(ButtonStyle);
		NewButton->SetBackgroundColor(PanelColor.Last());
		NewButton->SetButtonText(FText::FromString(PlayerName));
		NewButton->SetTextColor(TextColor);
		NewButton->SetTextPadding(5.0f);
		NewButton->ButtonIndex=Index;

		// Add the button to the vertical box
		UVerticalBoxSlot* NewSlot = this->AddChildToVerticalBox(NewButton);
		if (NewSlot)
		{
			NewSlot->SetPadding(FMargin(4.0f));
		}
	}
}

