// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MKOIComboDataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "MKOIComboListDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIComboListDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    // Array of combo data assets that define various combos
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combos")
    TArray<UMKOIComboDataAsset*> Combos;	

    UPROPERTY(EditAnywhere, Category = "Abilities")
    TSubclassOf<UGameplayAbility> LightAttackAbility;

    UPROPERTY(EditAnywhere, Category = "Abilities")
    TSubclassOf<UGameplayAbility> HeavyAttackAbility;

    TArray<TSubclassOf<UGameplayAbility>> GetAllAbilities() const;
};
