// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MKOIGameplayAbility.h"
#include "MKOIAttackAbility.generated.h"

UCLASS()
class MKOI_API UMKOIAttackAbility : public UMKOIGameplayAbility
{
    GENERATED_BODY()

public:
    UMKOIAttackAbility();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Tags")
	FGameplayTag AttackStartTag;

    /*Only played if montage finished correctly*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Tags")
    FGameplayTag AttackEndTag;

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                 const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData) override;

    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
    void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    UAnimMontage* AttackMontage;
    UPROPERTY()
    FRotator PreviousRotation;
    UPROPERTY()
    ACharacter* Character;
};