// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/MKOIDamageExecution.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "MKOICharacterAttributeSet.h"
#include "Settings/MKOIGameplayTagsSettings.h"

UMKOIDamageExecution::UMKOIDamageExecution()
{
    FGameplayEffectAttributeCaptureDefinition HealthCapture(
        UMKOICharacterAttributeSet::GetHealthAttribute(), 
        EGameplayEffectAttributeCaptureSource::Target, 
        true
    );

    RelevantAttributesToCapture.Add(HealthCapture);
}

void UMKOIDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    if (TargetASC && TargetASC->HasMatchingGameplayTag(GetDefault<UMKOIGameplayTagsSettings>()->ImmortalityTag))
    {
        return;
    }

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    
    float DamageAmount = Spec.GetSetByCallerMagnitude(GetDefault<UMKOIGameplayTagsSettings>()->DamageTag, true);
    
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
        UMKOICharacterAttributeSet::GetHealthAttribute(), EGameplayModOp::Additive, -DamageAmount));
}
