#include "Abilities/MKOIGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "MKOICharacterAttributeSet.h"
#include "Settings/MKOIGameplayTagsSettings.h"

FVector UMKOIGameplayAbility::GetCharacterDesiredDirection(
    const FVector& InputDirection,
    const FVector& CharacterForward,
    const FVector& CharacterRight)
{
    FVector DesiredDirection = FVector::ZeroVector;


    if (FVector::DotProduct(InputDirection, CharacterForward) < -0.8f) // Backward
    {
        DesiredDirection = -CharacterForward;
    }
    else if (FVector::DotProduct(InputDirection, CharacterRight) > 0.8f) // Right
    {
        DesiredDirection = CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, CharacterRight) < -0.8f) // Left
    {
        DesiredDirection = -CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, CharacterForward + CharacterRight) > 0.8f) // Forward Right
    {
        DesiredDirection = CharacterForward + CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, CharacterForward - CharacterRight) > 0.8f) // Forward Left
    {
        DesiredDirection = CharacterForward - CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, -CharacterForward + CharacterRight) > 0.8f) // Backward Right
    {
        DesiredDirection = -CharacterForward + CharacterRight;
    }
    else if (FVector::DotProduct(InputDirection, -CharacterForward - CharacterRight) > 0.8f) // Backward Left
    {
        DesiredDirection = -CharacterForward - CharacterRight;
    }
    return DesiredDirection;
}

void UMKOIGameplayAbility::RotateCharacterTowardsAttackDirection(ACharacter* InCharacter, const FVector& Direction)
{
    if (Direction.IsNearlyZero()) return;

    InCharacter->SetActorRotation(Direction.Rotation());
}

bool UMKOIGameplayAbility::HandleAbilityInterruption(FGameplayAbilitySpecHandle Handle, 
                                               const FGameplayAbilityActorInfo* ActorInfo, 
                                               const FGameplayAbilityActivationInfo& ActivationInfo)
{
    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    if (ASC)
    {
        for (FGameplayAbilitySpec& ActiveAbilitySpec : ASC->GetActivatableAbilities())
        {
            UGameplayAbility* ActiveAbility = ActiveAbilitySpec.GetPrimaryInstance();
            if (ActiveAbility && ActiveAbility->GetCurrentMontage() != nullptr)
            {
                if (ActiveAbilitySpec.Ability->AbilityTags.HasTag(GetDefault<UMKOIGameplayTagsSettings>()->InterruptionTag))
                {
                    ActiveAbility->CancelAbility(ActiveAbilitySpec.Handle, ActorInfo, ActivationInfo, true);
                    break;
                }
                else
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool UMKOIGameplayAbility::ApplyStaminaCost(const FGameplayAbilityActorInfo* ActorInfo)
{
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (ASC)
	{
		float CurrentStamina = ASC->GetNumericAttribute(UMKOICharacterAttributeSet::GetStaminaAttribute());

		if (CurrentStamina > StaminaCost)
		{
			ASC->ApplyModToAttribute(UMKOICharacterAttributeSet::GetStaminaAttribute(), EGameplayModOp::Additive, -StaminaCost);
			return true;
		}
	}
	return false;
}

bool UMKOIGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const {
     UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
    if (ASC->HasMatchingGameplayTag(GetDefault<UMKOIGameplayTagsSettings>()->DeathTag)) {
        return false;
    }
    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}