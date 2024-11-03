// Fill out your copyright notice in the Description page of Project Settings.


#include "MKOICharacter.h"
#include "AbilitySystemGlobals.h"
#include "UI/MKOIStaminaDisplayWidget.h"
#include "DataAssets/MKOIComboDataAsset.h"
#include "DataAssets/MKOIComboListDataAsset.h"
#include "DataAssets/MKOIWeaponDataAsset.h"
#include "MKOIWeapon.h"
#include "Settings/MKOIGameplayTagsSettings.h"

AMKOICharacter::AMKOICharacter()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AttributeSet = CreateDefaultSubobject<UMKOICharacterAttributeSet>(TEXT("AttributeSet"));  
}

UAbilitySystemComponent* AMKOICharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UMKOICharacterAttributeSet* AMKOICharacter::GetAttributeSet() const
{
    return AttributeSet;
}

bool AMKOICharacter::HasGameplayTag(const FGameplayTag& Tag) const
{
    return AbilitySystemComponent->HasMatchingGameplayTag(Tag);
}

bool AMKOICharacter::IsDead()
{
    return AbilitySystemComponent->HasMatchingGameplayTag(GetDefault<UMKOIGameplayTagsSettings>()->DeathTag);
}

void AMKOICharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
    {
        for (TSubclassOf<UGameplayEffect> GameplayEffect : EffectClasses)
        {
			FGameplayEffectSpecHandle StaminaRegenSpecHandle = ASC->MakeOutgoingSpec(GameplayEffect, 1, ASC->MakeEffectContext());
			if (StaminaRegenSpecHandle.IsValid())
			{
				ASC->ApplyGameplayEffectSpecToSelf(*StaminaRegenSpecHandle.Data.Get());
			}
        }


        for (TSubclassOf<UGameplayAbility> Ability : Abilities)
        {
            if (Ability)
            {
                AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
            }
        }

    }

     for (TSubclassOf<UUserWidget> WidgetClass : DisplayWidgetClasses)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
        }
    }

    InitializeWeapon();

    GetAttributeSet()->OnHealthChanged.AddDynamic(this, &AMKOICharacter::OnHealthChanged);
}

void AMKOICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetAttributeSet()->OnHealthChanged.RemoveDynamic(this, &AMKOICharacter::OnHealthChanged);
    Super::EndPlay(EndPlayReason);
}

void AMKOICharacter::InitializeWeapon()
{
     if (!WeaponDataAsset) return;

    if (WeaponDataAsset->WeaponClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        EquippedWeapon = GetWorld()->SpawnActor<AMKOIWeapon>(WeaponDataAsset->WeaponClass, SpawnParams);

        if (EquippedWeapon)
        {
            EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, EquippedWeapon->GetAttackSocketName());
        }
    }

    if (WeaponDataAsset->AnimationBlueprint)
    {
        if (GetMesh())
        {
            GetMesh()->LinkAnimClassLayers(WeaponDataAsset->AnimationBlueprint);
        }
    }

    if (WeaponDataAsset->ComboListDataAsset)
    {
        ComboListDataAsset = WeaponDataAsset->ComboListDataAsset;
    }

    
    for (TSubclassOf<UGameplayAbility> Ability : WeaponDataAsset->ComboListDataAsset->GetAllAbilities())
    {
        if (Ability)
        {
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
        }
    }
}

void AMKOICharacter::PerformLightAttack()
{
    if (!TryExecuteComboAttack())
    {
        ExecuteAttack(ComboListDataAsset->LightAttackAbility);
    }
}

void AMKOICharacter::PerformHeavyAttack()
{
    if (!TryExecuteComboAttack())
    {
        ExecuteAttack(ComboListDataAsset->HeavyAttackAbility);
    }
}

void AMKOICharacter::ChangeWeaponDataAsset(UMKOIWeaponDataAsset* NewWeaponDataAsset)
{
	if (NewWeaponDataAsset == WeaponDataAsset) return;

    if (EquippedWeapon)
    {
        EquippedWeapon->Destroy();
        EquippedWeapon = nullptr;
    }
    
    TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove;

    if (WeaponDataAsset && WeaponDataAsset->ComboListDataAsset)
    {
        for (TSubclassOf<UGameplayAbility> Ability : WeaponDataAsset->ComboListDataAsset->GetAllAbilities())
        {
            if (Ability)
            {
                for (const FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
                {
                    if (AbilitySpec.Ability->GetClass() == Ability)
                    {
                        AbilityHandlesToRemove.Add(AbilitySpec.Handle);
                    }
                }
            }
        }

        for (const FGameplayAbilitySpecHandle& Handle : AbilityHandlesToRemove)
        {
            AbilitySystemComponent->ClearAbility(Handle);
        }
    }
    
    WeaponDataAsset = NewWeaponDataAsset;

    InitializeWeapon();
}

bool AMKOICharacter::TryExecuteComboAttack()
{
    if (!ComboListDataAsset) return false;

    for (UMKOIComboDataAsset* ComboData : ComboListDataAsset->Combos)
    {
        if (ComboData && ComboData->MatchesStack(PerformedAbilityStack))
        {
            ExecuteAttack(ComboData->ResultingAbility);
            return true;
        }
    }

    return false;
}

void AMKOICharacter::ExecuteAttack(TSubclassOf<UGameplayAbility> AbilityToExecute)
{
    if (AbilityToExecute && AbilitySystemComponent->TryActivateAbilityByClass(AbilityToExecute))
    {
        GetWorldTimerManager().ClearTimer(ComboResetTimerHandle);
        GetWorldTimerManager().SetTimer(ComboResetTimerHandle, this, &AMKOICharacter::ResetComboStack, 3.0f, false);

        PerformedAbilityStack.Add(AbilityToExecute);

        NotifyCombatState(true);
    }
}

void AMKOICharacter::ResetComboStack()
{
    PerformedAbilityStack.Empty();
    UE_LOG(LogTemp, Log, TEXT("Combo stack has been reset due to inactivity"));
    NotifyCombatState(false);
}

void AMKOICharacter::NotifyCombatState(bool bInCombat)
{
	bIsInCombat = bInCombat;
}

 
void AMKOICharacter::OnHealthChanged(float CurrentHealth, float MaxHealth) {
    if (CurrentHealth <= 0) {
        ApplyDeathEffect();
    }
}

void AMKOICharacter::ApplyDeathEffect() {
    if (!IsDead())
    {
        AbilitySystemComponent->AddLooseGameplayTag(GetDefault<UMKOIGameplayTagsSettings>()->DeathTag);
		ShowDeathScreen();
    }
}

void AMKOICharacter::ShowDeathScreen() {
    if (DeathScreenClass) {
        UUserWidget* DeathScreen = CreateWidget<UUserWidget>(GetWorld(), DeathScreenClass);
        if (DeathScreen) {
            DeathScreen->AddToViewport();
        }
    }
}