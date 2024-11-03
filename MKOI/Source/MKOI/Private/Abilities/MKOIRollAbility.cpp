#include "Abilities/MKOIRollAbility.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "Settings/MKOIGameplayTagsSettings.h"

UMKOIRollAbility::UMKOIRollAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    StaminaCost = 20.0f;

    ActivationOwnedTags.AddTag(GetDefault<UMKOIGameplayTagsSettings>()->BlockStaminaRegenTag);

    RollStartTag = GetDefault<UMKOIGameplayTagsSettings>()->RollStartTag;
    RollEndTag = GetDefault<UMKOIGameplayTagsSettings>()->RollEndTag;
}

void UMKOIRollAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
        ASC->ExecuteGameplayCue(RollStartTag);
    }

    FVector InputDirection = Character->GetLastMovementInputVector();
    PreviousRotation = Character->GetActorRotation();

    FVector CharacterForward = Character->GetActorForwardVector();
    FVector CharacterRight = Character->GetActorRightVector();

    FVector DesiredDirection = FVector::ZeroVector;

    UAnimMontage* SelectedMontage = GetRollMontageByDirection(InputDirection, CharacterForward, CharacterRight, DesiredDirection);

    if (!DesiredDirection.IsNearlyZero())
    {
        Character->bUseControllerRotationYaw = false;
        RotateCharacterTowardsAttackDirection(Character, DesiredDirection);
    }

    if (SelectedMontage && Character->GetMesh())
    {
        Character->PlayAnimMontage(SelectedMontage);

        FOnMontageEnded MontageEndedDelegate;
        MontageEndedDelegate.BindUObject(this, &UMKOIRollAbility::OnMontageEnded);
        CurrentMontage = SelectedMontage;
        Character->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, SelectedMontage);
    }
    else
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    }
   
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMKOIRollAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (Montage == CurrentMontage)
    {
        CurrentMontage = nullptr;

		UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
		if (ASC)
		{
			ASC->ExecuteGameplayCue(RollEndTag);
		}

        EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
    }
}

UAnimMontage* UMKOIRollAbility::GetRollMontageByDirection(const FVector& InputDirection, const FVector& CharacterForward,
                                                          const FVector& CharacterRight, FVector& Out_DesiredDirection)
{
    UAnimMontage* SelectedMontage = nullptr;

    if (FVector::DotProduct(InputDirection, CharacterForward) > 0.8f) // Forward
    {
        SelectedMontage = ForwardRollMontage;
    }
    else if (FVector::DotProduct(InputDirection, CharacterForward) < -0.8f) // Backward
    {
        SelectedMontage = BackwardRollMontage;
    }
    else if (FVector::DotProduct(InputDirection, CharacterRight) > 0.8f) // Right
    {
        SelectedMontage = RightRollMontage;
    }
    else if (FVector::DotProduct(InputDirection, CharacterRight) < -0.8f) // Left
    {
        SelectedMontage = LeftRollMontage;
    }
    else if (FVector::DotProduct(InputDirection, CharacterForward + CharacterRight) > 0.8f) // Forward Right
    {
        SelectedMontage = ForwardRightRollMontage;
        Out_DesiredDirection = CharacterForward + CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, CharacterForward - CharacterRight) > 0.8f) // Forward Left
    {
        SelectedMontage = ForwardLeftRollMontage;
        Out_DesiredDirection = CharacterForward - CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, -CharacterForward + CharacterRight) > 0.8f) // Backward Right
    {
        SelectedMontage = BackwardRightRollMontage;
        Out_DesiredDirection = -CharacterForward + CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, -CharacterForward - CharacterRight) > 0.8f) // Backward Left
    {
        SelectedMontage = BackwardLeftRollMontage;
        Out_DesiredDirection = -CharacterForward - CharacterRight;
    }

    return SelectedMontage;
}

void UMKOIRollAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
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