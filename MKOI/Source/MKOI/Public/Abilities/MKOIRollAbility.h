// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MKOIGameplayAbility.h"
#include "MKOIRollAbility.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIRollAbility : public UMKOIGameplayAbility
{
	GENERATED_BODY()
public:
    UMKOIRollAbility();

    // Directional montages
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* ForwardRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* BackwardRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* LeftRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* RightRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* ForwardLeftRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* ForwardRightRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* BackwardLeftRollMontage;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Montages")
    UAnimMontage* BackwardRightRollMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Tags")
	FGameplayTag RollStartTag;

    /*Only played if montage finished correctly*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Tags")
    FGameplayTag RollEndTag;
protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                 const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData) override;

    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

    UAnimMontage* GetRollMontageByDirection(const FVector& InputDirection, const FVector& CharacterForward, const FVector& CharacterRight, FVector& Out_DesiredDirection);

    FRotator PreviousRotation;
    UPROPERTY()
    ACharacter* Character;
};
