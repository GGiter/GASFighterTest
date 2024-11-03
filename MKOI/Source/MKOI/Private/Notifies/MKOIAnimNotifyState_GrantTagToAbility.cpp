// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/MKOIAnimNotifyState_GrantTagToAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Settings/MKOIGameplayTagsSettings.h"

void UMKOIAnimNotifyState_GrantTagToAbility::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
    if (!Character) return;

    IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character);
    if (!AbilitySystemInterface) return;

    UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
    if (!ASC) return;

    for (FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
    {
        UGameplayAbility* AbilityInstance = AbilitySpec.GetPrimaryInstance();
        
        if (AbilityInstance && AbilityInstance->IsActive() && AbilityInstance->GetCurrentMontage() == Animation)
        {
            AbilityInstance->AbilityTags.AddTag(TagToGrant);
            AbilitySpec.Ability->AbilityTags.AddTag(TagToGrant);
            break;
        }
    }
}

void UMKOIAnimNotifyState_GrantTagToAbility::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
    if (!Character) return;

    IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Character);
    if (!AbilitySystemInterface) return;

    UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
    if (!ASC) return;

    for (FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
    {
        UGameplayAbility* AbilityInstance = AbilitySpec.GetPrimaryInstance();
        
        if (AbilityInstance && AbilityInstance->IsActive() && AbilityInstance->GetCurrentMontage() == Animation)
        {
            AbilityInstance->AbilityTags.RemoveTag(TagToGrant);
            AbilitySpec.Ability->AbilityTags.RemoveTag(TagToGrant);
            break;
        }
    }
}
