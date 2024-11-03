// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MKOICharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
public: \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, Health, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, Stamina, float, MaxStamina);

UCLASS()
class MKOI_API UMKOICharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
    UMKOICharacterAttributeSet();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData Health;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData Stamina;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
    FGameplayAttributeData MaxStamina;

    ATTRIBUTE_ACCESSORS(UMKOICharacterAttributeSet, Health)
    ATTRIBUTE_ACCESSORS(UMKOICharacterAttributeSet, MaxHealth)
    ATTRIBUTE_ACCESSORS(UMKOICharacterAttributeSet, Stamina)
    ATTRIBUTE_ACCESSORS(UMKOICharacterAttributeSet, MaxStamina)

    FOnHealthChanged OnHealthChanged;
    FOnStaminaChanged OnStaminaChanged;

protected:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
