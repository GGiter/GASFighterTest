// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "MKOIHealthDisplayWidget.generated.h"

class UProgressBar; 


UCLASS()
class MKOI_API UMKOIHealthDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    void UpdateProgressBarColor(bool bIsImmortal);
    void UpdateInitialHealthAndColor();

    UFUNCTION()
    void UpdateHealth(float CurrentHealth, float MaxHealth);

    void BindToHealthChange();

    void BindToGameplayTagChanges();

    void OnGameplayTagChanged(const FGameplayTag Tag, int32 NewCount);

};
