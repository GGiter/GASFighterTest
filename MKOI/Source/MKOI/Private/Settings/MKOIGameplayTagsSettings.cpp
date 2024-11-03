// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/MKOIGameplayTagsSettings.h"

UMKOIGameplayTagsSettings::UMKOIGameplayTagsSettings()
{
	ImmortalityTag = FGameplayTag::RequestGameplayTag(TEXT("Gameplay.Immortality"));
	InterruptionTag = FGameplayTag::RequestGameplayTag(TEXT("Ability.CanBeInterrupted"));
	BlockStaminaRegenTag = FGameplayTag::RequestGameplayTag(TEXT("CharacterState.StaminaBlocked"));
	DamageTag = FGameplayTag::RequestGameplayTag(TEXT("Data.Damage"));
	AttackStartTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.MKOIAttackAbility.Start"));
    AttackEndTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.MKOIAttackAbility.End"));
	RollStartTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.MKOIRollAbility.Start"));
    RollEndTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.MKOIRollAbility.End"));
	DamageAppliedTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.MKOIDamage.Applied"));
	DeathTag = FGameplayTag::RequestGameplayTag(TEXT("CharacterState.Death"));
}
