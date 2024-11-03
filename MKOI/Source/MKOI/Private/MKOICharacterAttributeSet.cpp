// Fill out your copyright notice in the Description page of Project Settings.


#include "MKOICharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

UMKOICharacterAttributeSet::UMKOICharacterAttributeSet()
{
    Health = 100.0f;
    MaxHealth = 100.0f;
    Stamina = 100.0f;
    MaxStamina = 100.0f;
}

void UMKOICharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0, MaxHealth.GetCurrentValue());
    }
    else if (Attribute == GetStaminaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0, MaxStamina.GetCurrentValue());
    }

    Super::PreAttributeChange(Attribute, NewValue);
}

void UMKOICharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    if (Attribute == GetHealthAttribute())
    {
        OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
    }
    else if (Attribute == GetStaminaAttribute())
    {
        OnStaminaChanged.Broadcast(Stamina.GetCurrentValue(), MaxStamina.GetCurrentValue());
    }

    Super::PostAttributeChange(Attribute, OldValue, NewValue);
}