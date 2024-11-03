// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/MKOIDamageGameplayEffect.h"
#include "Effects/MKOIDamageExecution.h"
#include "Settings/MKOIGameplayTagsSettings.h"

UMKOIDamageGameplayEffect::UMKOIDamageGameplayEffect()
{
    DurationPolicy = EGameplayEffectDurationType::Instant; 
    FGameplayEffectExecutionDefinition DamageExecution;
    DamageExecution.CalculationClass = UMKOIDamageExecution::StaticClass();
    Executions.Add(DamageExecution);
    FGameplayEffectCue DamageCue(GetDefault<UMKOIGameplayTagsSettings>()->DamageAppliedTag, 0.f, 1.f);
    GameplayCues.Add(DamageCue);
}