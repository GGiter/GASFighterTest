// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "MKOIGameplayTagsSettings.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIGameplayTagsSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UMKOIGameplayTagsSettings();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FGameplayTag ImmortalityTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FGameplayTag InterruptionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FGameplayTag BlockStaminaRegenTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FGameplayTag DamageTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FGameplayTag AttackStartTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
    FGameplayTag AttackEndTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FGameplayTag RollStartTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
    FGameplayTag RollEndTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
    FGameplayTag DamageAppliedTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
    FGameplayTag DeathTag;
};
