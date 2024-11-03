// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MKOIGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
    float StaminaCost;


    FVector GetCharacterDesiredDirection(const FVector& InputDirection, const FVector& CharacterForward, const FVector& CharacterRight);
    void RotateCharacterTowardsAttackDirection(ACharacter* Character, const FVector& Direction);
    bool HandleAbilityInterruption(FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo& ActivationInfo);
    bool ApplyStaminaCost(const FGameplayAbilityActorInfo* ActorInfo);
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
};
