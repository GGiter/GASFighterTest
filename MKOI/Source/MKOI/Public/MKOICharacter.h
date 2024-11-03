// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MKOICharacterAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MKOICharacter.generated.h"

class UMKOIWeaponDataAsset;
class AMKOIWeapon;

UCLASS()
class MKOI_API AMKOICharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()


public:
    AMKOICharacter();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual UMKOICharacterAttributeSet* GetAttributeSet() const;

    bool HasGameplayTag(const FGameplayTag& Tag) const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

    /*Abilites to apply at the begging of the game*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> Abilities;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
    UMKOICharacterAttributeSet* AttributeSet;

    /*Gameplay Effects to apply at the begging of the game*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TArray<TSubclassOf<UGameplayEffect>> EffectClasses;

    /*Widgets to create at the begging of the game*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserWidget")
    TArray<TSubclassOf<UUserWidget>> DisplayWidgetClasses;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserWidget")
    TSubclassOf<UUserWidget> DeathScreenClass;

	UPROPERTY(BlueprintReadOnly, Category = "UserWidget")
	bool bIsInCombat;

    UFUNCTION(BlueprintPure, Category = "Character")
    bool IsDead();
protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformLightAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformHeavyAttack();

     UFUNCTION(BlueprintCallable, Category = "Combat")
    void ChangeWeaponDataAsset(UMKOIWeaponDataAsset* NewWeaponDataAsset);

    bool TryExecuteComboAttack();

    void ExecuteAttack(TSubclassOf<UGameplayAbility> AbilityToExecute);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Abilities|Combo")
    class UMKOIComboListDataAsset* ComboListDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities|Combo")
    TArray<TSubclassOf<UGameplayAbility>> PerformedAbilityStack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    UMKOIWeaponDataAsset* WeaponDataAsset;

    UPROPERTY(BlueprintReadOnly, Category = "Weapon")
    AMKOIWeapon* EquippedWeapon; 

    FTimerHandle ComboResetTimerHandle;

    void InitializeWeapon();
    void ResetComboStack();
    void NotifyCombatState(bool bInCombat);
    UFUNCTION()
    void OnHealthChanged(float CurrentHealth, float MaxHealth);
    void ApplyDeathEffect();
    void ShowDeathScreen();
};
