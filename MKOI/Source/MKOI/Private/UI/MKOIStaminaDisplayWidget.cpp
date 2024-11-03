// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MKOIStaminaDisplayWidget.h"
#include "Components/ProgressBar.h"
#include "MKOICharacter.h"
#include "MKOICharacterAttributeSet.h"

void UMKOIStaminaDisplayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BindToStaminaChange();

    UpdateInitialStamina();
}

void UMKOIStaminaDisplayWidget::NativeDestruct()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());

    if (PlayerCharacter)
    {
        PlayerCharacter->GetAttributeSet()->OnStaminaChanged.RemoveDynamic(this, &UMKOIStaminaDisplayWidget::UpdateStamina);
    }

    Super::NativeDestruct();
}

void UMKOIStaminaDisplayWidget::UpdateStamina(float CurrentStamina, float MaxStamina)
{
    if (StaminaProgressBar)
    {
        float StaminaPercentage = MaxStamina > 0.0f ? CurrentStamina / MaxStamina : 0.0f;
        StaminaProgressBar->SetPercent(StaminaPercentage);
    }
}

void UMKOIStaminaDisplayWidget::BindToStaminaChange()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());

    if (PlayerCharacter)
    {
        PlayerCharacter->GetAttributeSet()->OnStaminaChanged.AddDynamic(this, &UMKOIStaminaDisplayWidget::UpdateStamina);
    }
}

void UMKOIStaminaDisplayWidget::UpdateInitialStamina()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());
    if (PlayerCharacter && PlayerCharacter->GetAttributeSet())
    {
        float CurrentStamina = PlayerCharacter->GetAttributeSet()->GetStamina();
        float MaxStamina = PlayerCharacter->GetAttributeSet()->GetMaxStamina();
        UpdateStamina(CurrentStamina, MaxStamina);
    }
}