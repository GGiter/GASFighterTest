#include "UI/MKOIHealthDisplayWidget.h"
#include "Components/ProgressBar.h"
#include "MKOICharacter.h" 
#include "MKOICharacterAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Settings/MKOIGameplayTagsSettings.h"

void UMKOIHealthDisplayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BindToHealthChange();
    BindToGameplayTagChanges();

    UpdateInitialHealthAndColor();
}

void UMKOIHealthDisplayWidget::NativeDestruct()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());

    if (PlayerCharacter)
    {
        PlayerCharacter->GetAttributeSet()->OnHealthChanged.RemoveDynamic(this, &UMKOIHealthDisplayWidget::UpdateHealth);
    }

    Super::NativeDestruct();
}

void UMKOIHealthDisplayWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
    if (HealthProgressBar)
    {
        float HealthPercentage = MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;
        HealthProgressBar->SetPercent(HealthPercentage);

        AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());
        if (PlayerCharacter)
        {
            UpdateProgressBarColor(PlayerCharacter->HasGameplayTag(GetDefault<UMKOIGameplayTagsSettings>()->ImmortalityTag));
        }
    }
}

void UMKOIHealthDisplayWidget::BindToHealthChange()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());

    if (PlayerCharacter)
    {
        PlayerCharacter->GetAttributeSet()->OnHealthChanged.AddDynamic(this, &UMKOIHealthDisplayWidget::UpdateHealth);
    }
}

void UMKOIHealthDisplayWidget::BindToGameplayTagChanges()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());
    if (PlayerCharacter)
    {
        UAbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();
        if (ASC)
        {
            FGameplayTag ImmortalityTag = GetDefault<UMKOIGameplayTagsSettings>()->ImmortalityTag;
            ASC->RegisterGameplayTagEvent(ImmortalityTag).AddUObject(this, &UMKOIHealthDisplayWidget::OnGameplayTagChanged);
        }
    }
}

void UMKOIHealthDisplayWidget::OnGameplayTagChanged(const FGameplayTag Tag, int32 NewCount)
{
    if (Tag == GetDefault<UMKOIGameplayTagsSettings>()->ImmortalityTag)
    {
        UpdateProgressBarColor(NewCount > 0);
    }
}

void UMKOIHealthDisplayWidget::UpdateProgressBarColor(bool bIsImmortal)
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(bIsImmortal ? FLinearColor(1.0f, 1.0f, 0.0f) : FLinearColor(1.0f, 0.0f, 0.0f));
    }
}

void UMKOIHealthDisplayWidget::UpdateInitialHealthAndColor()
{
    AMKOICharacter* PlayerCharacter = Cast<AMKOICharacter>(GetOwningPlayerPawn());
    if (PlayerCharacter && PlayerCharacter->GetAttributeSet())
    {
        float CurrentHealth = PlayerCharacter->GetAttributeSet()->GetHealth();
        float MaxHealth = PlayerCharacter->GetAttributeSet()->GetMaxHealth();
        UpdateHealth(CurrentHealth, MaxHealth);

        bool bIsImmortal = PlayerCharacter->HasGameplayTag(GetDefault<UMKOIGameplayTagsSettings>()->ImmortalityTag);
        UpdateProgressBarColor(bIsImmortal);
    }
}
