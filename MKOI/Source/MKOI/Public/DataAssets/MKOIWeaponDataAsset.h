// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MKOIWeaponDataAsset.generated.h"


class UMKOIComboListDataAsset;

UCLASS()
class MKOI_API UMKOIWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    // Class of the weapon actor to spawn (or None if no weapon)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
    TSubclassOf<AActor> WeaponClass;

    // Class of the animation blueprint to use for this weapon
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
    TSubclassOf<UAnimInstance> AnimationBlueprint;

    // Data asset that defines combos associated with this weapon
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combos")
    UMKOIComboListDataAsset* ComboListDataAsset;	
};
