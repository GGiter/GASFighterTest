// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/MKOIAnimNotifyState_GrantTag.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "Settings/MKOIGameplayTagsSettings.h"

void UMKOIAnimNotifyState_GrantTag::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    UAbilitySystemComponent* AbilitySystemComponent = Owner->FindComponentByClass<UAbilitySystemComponent>();
    if (AbilitySystemComponent && TagToGrant.IsValid())
    {
        AbilitySystemComponent->AddLooseGameplayTag(TagToGrant);
    }
}

void UMKOIAnimNotifyState_GrantTag::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;

    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    UAbilitySystemComponent* AbilitySystemComponent = Owner->FindComponentByClass<UAbilitySystemComponent>();
    if (AbilitySystemComponent && TagToGrant.IsValid())
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(TagToGrant);
    }
}
