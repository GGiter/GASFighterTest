// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/MKOIComboDataAsset.h"
#include "Abilities/GameplayAbility.h"

bool UMKOIComboDataAsset::MatchesStack(const TArray<TSubclassOf<UGameplayAbility>>& PerformedStack) const
{
    if (PerformedStack.Num() < AbilityStack.Num()) return false;

    // Compare the most recent PerformedStack elements with AbilityStack
    for (int32 i = 0; i < AbilityStack.Num(); ++i)
    {
        if (PerformedStack[PerformedStack.Num() - AbilityStack.Num() + i] != AbilityStack[i].ExpectedAbility)
        {
            return false;
        }
    }

    return true;
}

TArray<TSubclassOf<UGameplayAbility>> UMKOIComboDataAsset::GetAllAbilities() const
{
    TArray<TSubclassOf<UGameplayAbility>> OutAbilties;
    for (const FComboEntry& ComboEntry : AbilityStack)
    {
        OutAbilties.AddUnique(ComboEntry.ExpectedAbility);
    }
    OutAbilties.AddUnique(ResultingAbility);
    return OutAbilties;
}
