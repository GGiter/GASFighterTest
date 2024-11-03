// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MKOIStaminaDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIStaminaDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* StaminaProgressBar;

    void BindToStaminaChange();
    void UpdateInitialStamina();

    UFUNCTION()
    void UpdateStamina(float CurrentStamina, float MaxStamina);
};
