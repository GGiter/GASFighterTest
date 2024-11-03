#include "Abilities/MKOIAttackAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "MKOICharacterAttributeSet.h"
#include "Settings/MKOIGameplayTagsSettings.h"

UMKOIAttackAbility::UMKOIAttackAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    StaminaCost = 10.0f;

    ActivationOwnedTags.AddTag(GetDefault<UMKOIGameplayTagsSettings>()->BlockStaminaRegenTag);

    AttackStartTag = GetDefault<UMKOIGameplayTagsSettings>()->AttackStartTag;
    AttackEndTag = GetDefault<UMKOIGameplayTagsSettings>()->AttackEndTag;
}

void UMKOIAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

    if (HandleAbilityInterruption(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
    if (!Character) return;

    if (!ApplyStaminaCost(ActorInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    if (ASC)
    {
        ASC->ExecuteGameplayCue(AttackStartTag);
    }

    FVector InputDirection = Character->GetLastMovementInputVector();
    PreviousRotation = Character->GetActorRotation();

    FVector CharacterForward = Character->GetActorForwardVector();
    FVector CharacterRight = Character->GetActorRightVector();

    Character->bUseControllerRotationYaw = false;
    RotateCharacterTowardsAttackDirection(Character, GetCharacterDesiredDirection(InputDirection, CharacterForward, CharacterRight));

    if (AttackMontage && Character->GetMesh())
    {
        Character->PlayAnimMontage(AttackMontage);

        FOnMontageEnded MontageEndedDelegate;
        MontageEndedDelegate.BindUObject(this, &UMKOIAttackAbility::OnMontageEnded);
        CurrentMontage = AttackMontage;
        Character->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
    }
    else
    {
        Character->bUseControllerRotationYaw = true;
        EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
    }

    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMKOIAttackAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (Montage == CurrentMontage)
    {
        CurrentMontage = nullptr;

        UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
        if (ASC)
        {
            ASC->ExecuteGameplayCue(AttackEndTag);
        }

        EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
    }
}

void UMKOIAttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                    const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                    bool bReplicateEndAbility,
                                    bool bWasCancelled)
{
      Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

    if (CurrentMontage && Character && Character->GetMesh())
    {
        Character->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, CurrentMontage);
        CurrentMontage = nullptr;
    }

    if (Character)
    {
        Character->SetActorRotation(PreviousRotation);
        Character->bUseControllerRotationYaw = true;
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}