// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"
#include "MKOIComboDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FComboEntry
{
    GENERATED_BODY()

    // The specific gameplay ability expected in the combo stack
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
    TSubclassOf<UGameplayAbility> ExpectedAbility;
};

UCLASS()
class MKOI_API UMKOIComboDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    // Sequence of abilities that must be performed before the combo is triggered
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
    TArray<FComboEntry> AbilityStack;

    // The ability to activate when the combo conditions are met
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
    TSubclassOf<UGameplayAbility> ResultingAbility;

    bool MatchesStack(const TArray<TSubclassOf<UGameplayAbility>>& PerformedStack) const;

    TArray<TSubclassOf<UGameplayAbility>> GetAllAbilities() const;
};
