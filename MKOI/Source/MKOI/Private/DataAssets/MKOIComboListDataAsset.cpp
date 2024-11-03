// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/MKOIComboListDataAsset.h"

TArray<TSubclassOf<UGameplayAbility>> UMKOIComboListDataAsset::GetAllAbilities() const
{
    TArray<TSubclassOf<UGameplayAbility>> OutAbilties;
    for (const UMKOIComboDataAsset* Combo : Combos)
    {
        for (TSubclassOf<UGameplayAbility>& Ability : Combo->GetAllAbilities())
            OutAbilties.AddUnique(Ability);
    }
    OutAbilties.AddUnique(LightAttackAbility);
    OutAbilties.AddUnique(HeavyAttackAbility);
    return OutAbilties;
}
