// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MP_Btn.generated.h"

class UTextBlock;
class UButtonSlot;

// Button Click Event Dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMPButtonClicked, int32, ButtonIndex);


/**
 * 
 */
UCLASS()
class MP_MANAGER_API UMP_Btn : public UButton
{
    GENERATED_BODY()
	
public:
    UMP_Btn(const FObjectInitializer& ObjectInitializer);

protected:
    // Called when the button is constructed
    //virtual void NativeConstruct();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP_Btn")
    int32 ButtonIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP_Btn")
    FText ButtonText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP_Btn|Text")
    FSlateFontInfo Font;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP_Btn|Text")
    FSlateColor TextColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MP_Btn|Text")
    FMargin TextPadding;

    UFUNCTION(BlueprintCallable, Category = "MP_Btn")
    void SetButtonText(const FText& NewText);

    UFUNCTION(BlueprintCallable, Category = "MP_Btn")
    void SetTextColor(const FSlateColor& NewColor);

    UFUNCTION(BlueprintCallable, Category = "MP_Btn")
    void SetTextPadding(const FMargin& NewTextPadding);

    UFUNCTION(BlueprintCallable, Category = "MP_Btn")
    void HandleButtonClick();


    // Event Dispatcher to bind to button clicks
    UPROPERTY(BlueprintAssignable, Category = "MP_Btn|Events")
    FOnMPButtonClicked OnMPButtonClicked;

    UPROPERTY()
    TObjectPtr<UTextBlock> TextBlock;

    void BuidButton();

};
